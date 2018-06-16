﻿using System.Collections.Generic;
using System.Linq;
using Syroot.BinaryData;
using Syroot.Pod.IO;

namespace Syroot.Pod.Circuits
{
    public class Designation : IData<Circuit>
    {
        // ---- PROPERTIES ---------------------------------------------------------------------------------------------

        public int Unknown1 { get; set; }

        public int Reserved2 { get; set; }

        public int Unknown3 { get; set; }

        public int Unknown4 { get; set; }

        public int Reserved5 { get; set; }

        public int Reserved6 { get; set; }

        public int Reserved7 { get; set; }

        public int Reserved8 { get; set; }

        public int Reserved9 { get; set; }

        public int[] Unknown10 { get; set; }

        public DesignationMacroSection MacroSection { get; set; }

        public IList<Macro> PhaseMacros { get; set; }

        public IList<DesignationPhase> Phases { get; set; }

        public IList<DesignationStart> Starts { get; set; }

        // ---- METHODS ------------------------------------------------------------------------------------------------

        void IData<Circuit>.Load(DataLoader<Circuit> loader, object parameter)
        {
            Unknown1 = loader.ReadInt32();
            Reserved2 = loader.ReadInt32();
            Unknown3 = loader.ReadInt32();
            Unknown4 = loader.ReadInt32();
            Reserved5 = loader.ReadInt32();
            Reserved6 = loader.ReadInt32();
            Reserved7 = loader.ReadInt32();
            Reserved8 = loader.ReadInt32();
            Reserved9 = loader.ReadInt32();
            Unknown10 = loader.ReadInt32s(5);
            MacroSection = loader.LoadSection<DesignationMacroSection>();
            PhaseMacros = loader.LoadMany<Macro>(loader.ReadInt32(), 3).ToList();
            Phases = loader.LoadMany<DesignationPhase>(loader.ReadInt32()).ToList();
            Starts = loader.LoadMany<DesignationStart>(loader.ReadInt32()).ToList();
        }
    }
}
