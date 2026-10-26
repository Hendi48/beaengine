/* Copyright 2006-2020, BeatriX
 * File coded by BeatriX
 *
 * This file is part of BeaEngine.
 *
 *    BeaEngine is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as published by
 *    the Free Software Foundation, either version 3 of the License, or
 *    (at your option) any later version.
 *
 *    BeaEngine is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public License
 *    along with BeaEngine.  If not, see <http://www.gnu.org/licenses/>. */

/* ====================================================================
 *      Legacy Prefix F0h-Group 1
 * ==================================================================== */
void __bea_callspec__ PrefLock(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    if (GV.VEX.state == InUsePrefix) {
      GV.ERROR_OPCODE = UD_;
    }
    ResetREX(pMyDisasm);
    (*pMyDisasm).Prefix.LockPrefix = InvalidPrefix;
    GV.EIP_++;
    (*pMyDisasm).Prefix.Number++;
    GV.NB_PREFIX++;
    (*pMyDisasm).Instruction.Opcode =  *((UInt8*) (UIntPtr)GV.EIP_);
    (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    GV.OperandSize = 32;
}

/* ====================================================================
 *      Legacy Prefix F2h-Group 1
 * ==================================================================== */
void __bea_callspec__ PrefREPNE(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    if (GV.VEX.state == InUsePrefix) {
      GV.ERROR_OPCODE = UD_;
    }
    ResetREX(pMyDisasm);
    (*pMyDisasm).Prefix.RepnePrefix = SuperfluousPrefix;
    GV.EIP_++;
    (*pMyDisasm).Prefix.Number++;
    GV.NB_PREFIX++;
    GV.PrefRepe = 0;
    GV.PrefRepne = 1;
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_);
    if (GV.VEX.state != InUsePrefix) {
        (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else if (GV.VEX.mmmmm == 0x1) {
        (void) opcode_map2[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else if (GV.VEX.mmmmm == 0x2) {
        (void) opcode_map3[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else if (GV.VEX.mmmmm == 0x3) {
        (void) opcode_map4[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else {
        (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    GV.PrefRepne = 0;
}

/* ====================================================================
 *      Legacy Prefix F3h-Group 1
 * ==================================================================== */
void __bea_callspec__ PrefREPE(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    (*pMyDisasm).Prefix.RepPrefix = SuperfluousPrefix;
    if (GV.VEX.state == InUsePrefix) {
      GV.ERROR_OPCODE = UD_;
    }
    ResetREX(pMyDisasm);
    GV.EIP_++;
    (*pMyDisasm).Prefix.Number++;
    GV.NB_PREFIX++;
    GV.PrefRepe = 1;
    GV.PrefRepne = 0;
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_);
    if (GV.VEX.state != InUsePrefix) {
        (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else if (GV.VEX.mmmmm == 0x1) {
        (void) opcode_map2[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else if (GV.VEX.mmmmm == 0x2) {
        (void) opcode_map3[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else if (GV.VEX.mmmmm == 0x3) {
        (void) opcode_map4[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else {
        (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    GV.PrefRepe = 0;
}

/* ====================================================================
 *      Only the last segment override counts : previous ones become
 *      superfluous. In 64-bit mode es/cs/ss/ds overrides are ignored and
 *      do not cancel fs/gs.
 * ==================================================================== */
void __bea_callspec__ DemoteSegmentPrefixes(PDISASM pMyDisasm)
{
    if ((*pMyDisasm).Prefix.CSPrefix == InUsePrefix) (*pMyDisasm).Prefix.CSPrefix = SuperfluousPrefix;
    if ((*pMyDisasm).Prefix.DSPrefix == InUsePrefix) (*pMyDisasm).Prefix.DSPrefix = SuperfluousPrefix;
    if ((*pMyDisasm).Prefix.ESPrefix == InUsePrefix) (*pMyDisasm).Prefix.ESPrefix = SuperfluousPrefix;
    if ((*pMyDisasm).Prefix.SSPrefix == InUsePrefix) (*pMyDisasm).Prefix.SSPrefix = SuperfluousPrefix;
    if ((*pMyDisasm).Prefix.FSPrefix == InUsePrefix) (*pMyDisasm).Prefix.FSPrefix = SuperfluousPrefix;
    if ((*pMyDisasm).Prefix.GSPrefix == InUsePrefix) (*pMyDisasm).Prefix.GSPrefix = SuperfluousPrefix;
    GV.SEGMENTFS = 0;
}

/* ====================================================================
 *      Legacy Prefix 2Eh-Group 2
 * ==================================================================== */
void __bea_callspec__ PrefSEGCS(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    if (GV.VEX.state == InUsePrefix) {
      GV.ERROR_OPCODE = UD_;
    }
    ResetREX(pMyDisasm);
    if (GV.Architecture != 64) DemoteSegmentPrefixes(pMyDisasm);
    (*pMyDisasm).Prefix.CSPrefix = InUsePrefix;
    GV.EIP_++;
    (*pMyDisasm).Prefix.Number++;
    GV.NB_PREFIX++;
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_);
    (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
}

/* ====================================================================
 *      Legacy Prefix 3Eh-Group 2
 * ==================================================================== */
void __bea_callspec__ PrefSEGDS(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    if (GV.VEX.state == InUsePrefix) {
      GV.ERROR_OPCODE = UD_;
    }
    ResetREX(pMyDisasm);
    if (GV.Architecture != 64) DemoteSegmentPrefixes(pMyDisasm);
    (*pMyDisasm).Prefix.DSPrefix = InUsePrefix;
    GV.EIP_++;
    (*pMyDisasm).Prefix.Number++;
    GV.NB_PREFIX++;
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_);
    (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
}

/* ====================================================================
 *      Legacy Prefix 26h-Group 2
 * ==================================================================== */
void __bea_callspec__ PrefSEGES(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    if (GV.VEX.state == InUsePrefix) {
      GV.ERROR_OPCODE = UD_;
    }
    ResetREX(pMyDisasm);
    if (GV.Architecture != 64) DemoteSegmentPrefixes(pMyDisasm);
    (*pMyDisasm).Prefix.ESPrefix = InUsePrefix;
    GV.EIP_++;
    (*pMyDisasm).Prefix.Number++;
    GV.NB_PREFIX++;
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_);
    (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
}

/* ====================================================================
 *      Legacy Prefix 64h-Group 2
 * ==================================================================== */
void __bea_callspec__ PrefSEGFS(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    if (GV.VEX.state == InUsePrefix) {
      GV.ERROR_OPCODE = UD_;
    }
    ResetREX(pMyDisasm);
    DemoteSegmentPrefixes(pMyDisasm);
    (*pMyDisasm).Prefix.FSPrefix = InUsePrefix;
    GV.EIP_++;
    (*pMyDisasm).Prefix.Number++;
    GV.NB_PREFIX++;
    GV.SEGMENTFS = 1;
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_);
    (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
}

/* ====================================================================
 *      Legacy Prefix 65h-Group 2
 * ==================================================================== */
void __bea_callspec__ PrefSEGGS(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    if (GV.VEX.state == InUsePrefix) {
      GV.ERROR_OPCODE = UD_;
    }
    ResetREX(pMyDisasm);
    DemoteSegmentPrefixes(pMyDisasm);
    (*pMyDisasm).Prefix.GSPrefix = InUsePrefix;
    GV.EIP_++;
    (*pMyDisasm).Prefix.Number++;
    GV.NB_PREFIX++;
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_);
    (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
}


/* ====================================================================
 *      Legacy Prefix 36h-Group 2
 * ==================================================================== */
void __bea_callspec__ PrefSEGSS(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    if (GV.VEX.state == InUsePrefix) {
      GV.ERROR_OPCODE = UD_;
    }
    ResetREX(pMyDisasm);
    if (GV.Architecture != 64) DemoteSegmentPrefixes(pMyDisasm);
    (*pMyDisasm).Prefix.SSPrefix = InUsePrefix;
    GV.EIP_++;
    (*pMyDisasm).Prefix.Number++;
    GV.NB_PREFIX++;
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_);
    (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
}

/* ====================================================================
 *      Legacy Prefix 66h-Group 3
 * ==================================================================== */
void __bea_callspec__ PrefOpSize(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    (*pMyDisasm).Prefix.OperandSize = InUsePrefix;
    if (GV.VEX.state == InUsePrefix) {
      GV.ERROR_OPCODE = UD_;
    }
    ResetREX(pMyDisasm);
    GV.EIP_++;
    (*pMyDisasm).Prefix.Number++;
    GV.NB_PREFIX++;
    /* OperandSize / OriginalOperandSize were set by ResetREX */
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_);
    if (GV.VEX.state != InUsePrefix) {
        (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else if (GV.VEX.mmmmm == 0x1) {
        (void) opcode_map2[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else if (GV.VEX.mmmmm == 0x2) {
        (void) opcode_map3[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else if (GV.VEX.mmmmm == 0x3) {
        (void) opcode_map4[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    }
    else {
        FailDecode(pMyDisasm);
    }
    if (GV.Architecture == 16) {
        GV.OperandSize = 16;
    }
    else {
        GV.OperandSize = 32;
    }
}

/* ====================================================================
 *      Legacy Prefix 67h-Group 4
 * ==================================================================== */
void __bea_callspec__ PrefAdSize(PDISASM pMyDisasm)
{
    /* a repeated 67h does not toggle the address size again */
    int toggle;
    if (!Security(2, pMyDisasm)) return;
    toggle = ((*pMyDisasm).Prefix.AddressSize != InUsePrefix);
    (*pMyDisasm).Prefix.AddressSize = InUsePrefix;
    if (GV.VEX.state == InUsePrefix) {
      GV.ERROR_OPCODE = UD_;
    }
    ResetREX(pMyDisasm);
    GV.EIP_++;
    (*pMyDisasm).Prefix.Number++;
    GV.NB_PREFIX++;
    if (toggle) {
        if (GV.Architecture == 16) {
            GV.AddressSize = GV.AddressSize << 1;
        }
        else {
            GV.AddressSize = GV.AddressSize >> 1;
        }
    }

    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_);
    (void) opcode_map1[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
    if (toggle) {
        if (GV.Architecture == 16) {
            GV.AddressSize = GV.AddressSize >> 1;
        }
        else {
            GV.AddressSize = GV.AddressSize << 1;
        }
    }
}

/* ====================================================================
 *      Escape Prefix 0Fh-two bytes opcodes
 * ==================================================================== */
void __bea_callspec__ Esc_2byte(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    GV.EIP_++;
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_)+0x0F00;
    (void) opcode_map2[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
}

/* ====================================================================
 *      Escape Prefix 0F38h-three bytes opcodes
 * ==================================================================== */
void __bea_callspec__ Esc_tableA4(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    GV.EIP_++;
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_)+0x0F3800;
    (void) opcode_map3[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
}
/* ====================================================================
 *      Escape Prefix 0F3Ah-three bytes opcodes
 * ==================================================================== */
void __bea_callspec__ Esc_tableA5(PDISASM pMyDisasm)
{
    if (!Security(2, pMyDisasm)) return;
    GV.EIP_++;
    (*pMyDisasm).Instruction.Opcode = *((UInt8*) (UIntPtr)GV.EIP_)+0x0F3A00;
    (void) opcode_map4[*((UInt8*) (UIntPtr)GV.EIP_)](pMyDisasm);
}
