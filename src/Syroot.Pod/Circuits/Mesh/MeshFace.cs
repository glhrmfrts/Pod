﻿using Syroot.BinaryData;
using Syroot.Maths;
using Syroot.Pod.IO;

namespace Syroot.Pod.Circuits
{
    /// <summary>
    /// Represents a single polygon of a <see cref="Mesh"/>.
    /// </summary>
    public class MeshFace : IData<Circuit>
    {
        // ---- PROPERTIES ---------------------------------------------------------------------------------------------

        public string Name { get; set; }

        public int FaceVertexCount { get; set; }

        public int[] Indices { get; set; } = new int[4];

        public Vector3F Normal { get; set; }

        public string MaterialType { get; set; }

        public uint ColorOrTexIndex { get; set; }

        public Vector2U[] TexCoords { get; set; } = new Vector2U[4];

        public uint Reserved1 { get; set; }

        public Vector3F QuadReserved { get; set; }

        public uint Reserved2 { get; set; }

        public uint Unknown { get; set; }

        public uint Properties { get; set; }

        // ---- METHODS ------------------------------------------------------------------------------------------------

        void IData<Circuit>.Load(DataLoader<Circuit> loader, object parameter)
        {
            MeshFaceParameters parameters = (MeshFaceParameters)parameter;

            if (parameters.HasNamedFaces)
                Name = loader.ReadPodString();

            if (loader.Instance.Key == 0x00005CA8)
            {
                Indices[3] = loader.ReadInt32();
                Indices[0] = loader.ReadInt32();
                FaceVertexCount = loader.ReadInt32();
                Indices[2] = loader.ReadInt32();
                Indices[1] = loader.ReadInt32();
            }
            else
            {
                FaceVertexCount = loader.ReadInt32();
                Indices = loader.ReadInt32s(4);
            }

            Normal = loader.ReadVector3F16x16();
            MaterialType = loader.ReadPodString();
            ColorOrTexIndex = loader.ReadUInt32();
            TexCoords = loader.ReadMany(4, () => loader.ReadVector2U());
            Reserved1 = loader.ReadUInt32();
            if (FaceVertexCount == 4)
                QuadReserved = loader.ReadVector3F16x16();
            if (Normal == Vector3U.Zero)
            {
                Reserved2 = loader.ReadUInt32();
            }
            else
            {
                if (parameters.HasUnkProperty)
                    Unknown = loader.ReadUInt32();
                Properties = loader.ReadUInt32();
            }
        }

        void IData<Circuit>.Save(DataSaver<Circuit> saver, object parameter)
        {
            MeshFaceParameters parameters = (MeshFaceParameters)parameter;

            if (parameters.HasNamedFaces)
                saver.WritePodString(Name);

            if (saver.Instance.Key == 0x00005CA8)
            {
                saver.WriteInt32(Indices[3]);
                saver.WriteInt32(Indices[0]);
                saver.WriteInt32(FaceVertexCount);
                saver.WriteInt32(Indices[2]);
                saver.WriteInt32(Indices[1]);
            }
            else
            {
                saver.WriteInt32(FaceVertexCount);
                saver.WriteInt32s(Indices);
            }

            saver.WriteVector3F16x16(Normal);
            saver.WritePodString(MaterialType);
            saver.WriteUInt32(ColorOrTexIndex);
            saver.WriteMany(TexCoords, x => saver.WriteVector2U(x));
            saver.Write(Reserved1);
            if (FaceVertexCount == 4)
                saver.WriteVector3F16x16(QuadReserved);
            if (Normal == Vector3U.Zero)
            {
                saver.WriteUInt32(Reserved2);
            }
            else
            {
                if (parameters.HasUnkProperty)
                    saver.WriteUInt32(Unknown);
                saver.WriteUInt32(Properties);
            }
        }
    }

    public struct MeshFaceParameters
    {
        public bool HasNamedFaces;
        public bool HasUnkProperty;
    }
}
