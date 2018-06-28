import os
import io
import bmesh
import bpy
import bpy_extras
from typing import *
from . import bl4
from . import btools
from . import pbdf


def register():
    bpy.utils.register_class(ImportOperator)
    bpy.types.INFO_MT_file_import.append(menu_func_import)
    bpy.types.INFO_MT_window.append(menu_func_import)  # DEBUG


def unregister():
    bpy.utils.unregister_class(ImportOperator)
    bpy.types.INFO_MT_file_import.remove(menu_func_import)
    bpy.types.INFO_MT_window.remove(menu_func_import)  # DEBUG


def menu_func_import(self, context):
    self.layout.operator(ImportOperator.bl_idname, text="UbiSoft BL4 (.bl4)")


class ImportOperator(bpy.types.Operator, bpy_extras.io_utils.ImportHelper):
    """Load a BL4 model file"""
    bl_idname = "import_scene.bl4"
    bl_label = "Import BL4"
    bl_options = {'UNDO'}
    filename_ext = ".bl4"
    filter_glob = bpy.props.StringProperty(default="*.bl4", options={'HIDDEN'})

    def __init__(self):
        self.circuit = None  # type: bl4.Circuit
        self.mats = []  # type: List[bpy.types.Material] # stores textures first, then color materials
        self.color_mat_indices = {}  # type: Dict[int, int] # maps color to self.materials index

    def execute(self, context):
        file_name = self.properties.filepath
        file_size = os.path.getsize(file_name)
        with io.BytesIO() as dec_file:
            with open(file_name, "rb") as f:
                key = pbdf.retrieve_key(f, file_size)
                f.seek(0)
                block_size = pbdf.retrieve_block_size(f, file_size, key)
                f.seek(0)
                pbdf.decrypt(f, dec_file, key, block_size)
                dec_file.seek(0)
                self.circuit = bl4.Circuit.load(dec_file, key, block_size)
        self.convert()
        return {'FINISHED'}

    def convert(self):
        for i, texture in enumerate(self.circuit.textures):
            self._convert_texture(texture, "Image{0:03d}".format(i), self.circuit.textures.size)
        for i, sector in enumerate(self.circuit.sectors):
            self._convert_sector(sector, "Sector{0:03d}".format(i))

    def _convert_texture(self, texture: bl4.Texture, name: str, size: int):
        b_image = bpy.data.images.new(name, width=size, height=size)
        # Convert upside-down RGB565 pixel data.
        pixels = [0.0] * size * size * 4
        data = memoryview(texture.data).cast("H")
        for y in range(size):
            for x in range(size):
                pixel = data[y * size + x]
                idx = ((size + ~y) * size + x) * 4
                pixels[idx] = (pixel >> 11) / 0b11111
                pixels[idx + 1] = (pixel >> 5 & 0b111111) / 0b111111
                pixels[idx + 2] = (pixel & 0b11111) / 0b11111
                pixels[idx + 3] = 1
        b_image.pixels = pixels
        b_image.pack(as_png=True)
        self.mats.append(btools.create_texture_material(name, b_image))

    def _convert_sector(self, sector: bl4.Sector, name: str):
        # Create mesh and BMesh, adding all texture materials and custom data layers.
        b_mesh = bpy.data.meshes.new(name)
        [b_mesh.materials.append(m) for m in self.mats]
        b_bmesh = bmesh.new()
        b_face_layer_name = b_bmesh.faces.layers.string.new("bl4_name")
        b_face_layer_props = b_bmesh.faces.layers.int.new("bl4_props")
        # Add vertex positions (TODO: use normals with normals_split_custom_set()?).
        for position in sector.mesh.positions:
            b_bmesh.verts.new(position)
        b_bmesh.verts.ensure_lookup_table()
        b_bmesh.verts.index_update()
        # Create faces provided as triangle / quad list.
        b_uv = b_bmesh.loops.layers.uv.new()
        for face in sector.mesh.faces:
            try:
                b_face = b_bmesh.faces.new((b_bmesh.verts[face.indices[i]] for i in range(face.vertex_count)))
            except ValueError as e:
                print(e)  # Ignore duplicate faces for now.
                continue
            b_face[b_face_layer_name] = face.name.encode()
            b_face[b_face_layer_props] = face.properties
            # TODO: Optimize setting materials, only append those needed by the sector.
            if face.material_type in ('FLAT', 'GOURAUD'):
                # Get an already appended color material or create and append it to the mesh.
                material_index = self.color_mat_indices.get(face.color)
                if material_index:
                    b_face.material_index = material_index
                else:
                    r = face.color >> 16 & 0xFF
                    g = face.color >> 8 & 0xFF
                    b = face.color & 0xFF
                    mat_name = "Color_{}_{}_{}".format(r, g, b)
                    b_mat = btools.create_color_material(mat_name, (r / 0xFF, g / 0xFF, b / 0xFF, 1))
                    index = len(self.mats)
                    b_mesh.materials.append(b_mat)
                    b_face.material_index = index
                    self.mats.append(b_mat)
                    self.color_mat_indices[face.color] = index
            else:
                b_face.material_index = face.texture_index
            # Map UV from 0-255 range (Y is inverted).
            for i in range(face.vertex_count):
                b_face.loops[i][b_uv].uv = (face.texture_uvs[i][0] / 0xFF, 0xFF - face.texture_uvs[i][1] / 0xFF)
        # Write the BMesh data to the mesh, add it to an object and link it to the scene.
        b_bmesh.to_mesh(b_mesh)
        b_mesh.uv_textures.active.name = "BaseMaterial"
        b_mesh.uv_textures.new(name="Lightmap")
        b_bmesh.free()
        b_obj = bpy.data.objects.new(name, b_mesh)
        bpy.context.scene.objects.link(b_obj)
