import importlib
import bpy
from . import binary
from . import bl4
from . import editing
from . import importing
from . import pbdf

# Reload modules when reloading add-ons in Blender with F8.
importlib.reload(binary)
importlib.reload(bl4)
importlib.reload(editing)
importlib.reload(importing)
importlib.reload(pbdf)

bl_info = {
    "name": "UbiSoft BL4 format",
    "description": "Import-Export BL4 mesh, UV's, materials and textures",
    "author": "Syroot",
    "version": (0, 1, 0),
    "blender": (2, 79, 0),
    "location": "File > Import-Export",
    "warning": "This add-on is under development.",
    "wiki_url": "https://github.com/Syroot/Pod/wiki",
    "tracker_url": "https://github.com/Syroot/Pod/issues",
    "support": 'COMMUNITY',
    "category": "Import-Export"
}


def register():
    bpy.utils.register_module(__name__)
    editing.register()
    importing.register()


def unregister():
    bpy.utils.unregister_module(__name__)
    editing.unregister()
    importing.unregister()
