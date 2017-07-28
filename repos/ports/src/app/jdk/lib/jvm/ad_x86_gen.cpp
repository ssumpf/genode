#line 1 "ad_x86_gen.cpp"
//
// Copyright (c) 2003, 2015, Oracle and/or its affiliates. All rights reserved.
// DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
//
// This code is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License version 2 only, as
// published by the Free Software Foundation.
//
// This code is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
// version 2 for more details (a copy is included in the LICENSE file that
// accompanied this code).
//
// You should have received a copy of the GNU General Public License version
// 2 along with this work; if not, write to the Free Software Foundation,
// Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
//
// Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
// or visit www.oracle.com if you need additional information or have any
// questions.
//
//

// Machine Generated File.  Do Not Edit!

#include "precompiled.hpp"
#include "adfiles/ad_x86.hpp"
#include "opto/cfgnode.hpp"
#include "opto/locknode.hpp"


//------------------------- MachOper Generator ---------------
// A switch statement on the dense-packed user-defined type system
// that invokes 'new' on the corresponding class constructor.

MachOper *State::MachOperGenerator(int opcode){

  switch(opcode) {
  case UNIVERSE:
    return new UniverseOper( );
  case LABEL:
    return new labelOper( );
  case SREGI:
    return new sRegIOper( );
  case SREGP:
    return new sRegPOper( );
  case SREGF:
    return new sRegFOper( );
  case SREGD:
    return new sRegDOper( );
  case SREGL:
    return new sRegLOper( );
  case METHOD:
    return new methodOper( );
  case IMMI:
    return new immIOper(_leaf->get_int() );
  case IMMI0:
    return new immI0Oper(_leaf->get_int() );
  case IMMI1:
    return new immI1Oper(_leaf->get_int() );
  case IMMI_M1:
    return new immI_M1Oper(_leaf->get_int() );
  case IMMI2:
    return new immI2Oper(_leaf->get_int() );
  case IMMI8:
    return new immI8Oper(_leaf->get_int() );
  case IMMI16:
    return new immI16Oper(_leaf->get_int() );
  case IMMU31:
    return new immU31Oper(_leaf->get_int() );
  case IMMI_32:
    return new immI_32Oper(_leaf->get_int() );
  case IMMI_64:
    return new immI_64Oper(_leaf->get_int() );
  case IMMP:
    return new immPOper(_leaf->bottom_type()->is_ptr() );
  case IMMP0:
    return new immP0Oper(_leaf->bottom_type()->is_ptr() );
  case IMMN:
    return new immNOper(_leaf->bottom_type()->is_narrowoop() );
  case IMMNKLASS:
    return new immNKlassOper(_leaf->bottom_type()->is_narrowklass() );
  case IMMN0:
    return new immN0Oper(_leaf->bottom_type()->is_narrowoop() );
  case IMMP31:
    return new immP31Oper(_leaf->bottom_type()->is_ptr() );
  case IMML:
    return new immLOper(_leaf->get_long() );
  case IMML8:
    return new immL8Oper(_leaf->get_long() );
  case IMMUL32:
    return new immUL32Oper(_leaf->get_long() );
  case IMML32:
    return new immL32Oper(_leaf->get_long() );
  case IMML0:
    return new immL0Oper(_leaf->get_long() );
  case IMML1:
    return new immL1Oper(_leaf->get_long() );
  case IMML_M1:
    return new immL_M1Oper(_leaf->get_long() );
  case IMML10:
    return new immL10Oper(_leaf->get_long() );
  case IMML_127:
    return new immL_127Oper(_leaf->get_long() );
  case IMML_32BITS:
    return new immL_32bitsOper(_leaf->get_long() );
  case IMMF0:
    return new immF0Oper(_leaf->getf() );
  case IMMF:
    return new immFOper(_leaf->getf() );
  case IMMD0:
    return new immD0Oper(_leaf->getd() );
  case IMMD:
    return new immDOper(_leaf->getd() );
  case IMMI_16:
    return new immI_16Oper(_leaf->get_int() );
  case IMMI_24:
    return new immI_24Oper(_leaf->get_int() );
  case IMMI_255:
    return new immI_255Oper(_leaf->get_int() );
  case IMMI_65535:
    return new immI_65535Oper(_leaf->get_int() );
  case IMML_255:
    return new immL_255Oper(_leaf->get_long() );
  case IMML_65535:
    return new immL_65535Oper(_leaf->get_long() );
  case RREGI:
    return new rRegIOper( );
  case RAX_REGI:
    return new rax_RegIOper( );
  case RBX_REGI:
    return new rbx_RegIOper( );
  case RCX_REGI:
    return new rcx_RegIOper( );
  case RDX_REGI:
    return new rdx_RegIOper( );
  case RDI_REGI:
    return new rdi_RegIOper( );
  case NO_RCX_REGI:
    return new no_rcx_RegIOper( );
  case NO_RAX_RDX_REGI:
    return new no_rax_rdx_RegIOper( );
  case ANY_REGP:
    return new any_RegPOper( );
  case RREGP:
    return new rRegPOper( );
  case RREGN:
    return new rRegNOper( );
  case NO_RAX_REGP:
    return new no_rax_RegPOper( );
  case NO_RBP_REGP:
    return new no_rbp_RegPOper( );
  case NO_RAX_RBX_REGP:
    return new no_rax_rbx_RegPOper( );
  case RAX_REGP:
    return new rax_RegPOper( );
  case RAX_REGN:
    return new rax_RegNOper( );
  case RBX_REGP:
    return new rbx_RegPOper( );
  case RSI_REGP:
    return new rsi_RegPOper( );
  case RDI_REGP:
    return new rdi_RegPOper( );
  case R15_REGP:
    return new r15_RegPOper( );
  case RREGL:
    return new rRegLOper( );
  case NO_RAX_RDX_REGL:
    return new no_rax_rdx_RegLOper( );
  case NO_RAX_REGL:
    return new no_rax_RegLOper( );
  case NO_RCX_REGL:
    return new no_rcx_RegLOper( );
  case RAX_REGL:
    return new rax_RegLOper( );
  case RCX_REGL:
    return new rcx_RegLOper( );
  case RDX_REGL:
    return new rdx_RegLOper( );
  case RFLAGSREG:
    return new rFlagsRegOper( );
  case RFLAGSREGU:
    return new rFlagsRegUOper( );
  case RFLAGSREGUCF:
    return new rFlagsRegUCFOper( );
  case REGF:
    return new regFOper( );
  case REGD:
    return new regDOper( );
  case VECS:
    return new vecSOper( );
  case VECD:
    return new vecDOper( );
  case VECX:
    return new vecXOper( );
  case VECY:
    return new vecYOper( );
  case INDIRECT:
    return new indirectOper( );
  case INDOFFSET8:
    return new indOffset8Oper(_kids[1]->_leaf->get_long() );
  case INDOFFSET32:
    return new indOffset32Oper(_kids[1]->_leaf->get_long() );
  case INDINDEXOFFSET:
    return new indIndexOffsetOper(_kids[1]->_leaf->get_long() );
  case INDINDEX:
    return new indIndexOper( );
  case INDINDEXSCALE:
    return new indIndexScaleOper(_kids[1]->_kids[1]->_leaf->get_int() );
  case INDPOSINDEXSCALE:
    return new indPosIndexScaleOper(_kids[1]->_kids[1]->_leaf->get_int() );
  case INDINDEXSCALEOFFSET:
    return new indIndexScaleOffsetOper(_kids[0]->_kids[1]->_kids[1]->_leaf->get_int(), _kids[1]->_leaf->get_long() );
  case INDPOSINDEXOFFSET:
    return new indPosIndexOffsetOper(_kids[1]->_leaf->get_long() );
  case INDPOSINDEXSCALEOFFSET:
    return new indPosIndexScaleOffsetOper(_kids[0]->_kids[1]->_kids[1]->_leaf->get_int(), _kids[1]->_leaf->get_long() );
  case INDCOMPRESSEDOOPOFFSET:
    return new indCompressedOopOffsetOper(_kids[1]->_leaf->get_long() );
  case INDIRECTNARROW:
    return new indirectNarrowOper( );
  case INDOFFSET8NARROW:
    return new indOffset8NarrowOper(_kids[1]->_leaf->get_long() );
  case INDOFFSET32NARROW:
    return new indOffset32NarrowOper(_kids[1]->_leaf->get_long() );
  case INDINDEXOFFSETNARROW:
    return new indIndexOffsetNarrowOper(_kids[1]->_leaf->get_long() );
  case INDINDEXNARROW:
    return new indIndexNarrowOper( );
  case INDINDEXSCALENARROW:
    return new indIndexScaleNarrowOper(_kids[1]->_kids[1]->_leaf->get_int() );
  case INDINDEXSCALEOFFSETNARROW:
    return new indIndexScaleOffsetNarrowOper(_kids[0]->_kids[1]->_kids[1]->_leaf->get_int(), _kids[1]->_leaf->get_long() );
  case INDPOSINDEXOFFSETNARROW:
    return new indPosIndexOffsetNarrowOper(_kids[1]->_leaf->get_long() );
  case INDPOSINDEXSCALEOFFSETNARROW:
    return new indPosIndexScaleOffsetNarrowOper(_kids[0]->_kids[1]->_kids[1]->_leaf->get_int(), _kids[1]->_leaf->get_long() );
  case STACKSLOTP:
    return new stackSlotPOper( );
  case STACKSLOTI:
    return new stackSlotIOper( );
  case STACKSLOTF:
    return new stackSlotFOper( );
  case STACKSLOTD:
    return new stackSlotDOper( );
  case STACKSLOTL:
    return new stackSlotLOper( );
  case CMPOP:
    return new cmpOpOper(_leaf->as_Bool()->_test._test );
  case CMPOPU:
    return new cmpOpUOper(_leaf->as_Bool()->_test._test );
  case CMPOPUCF:
    return new cmpOpUCFOper(_leaf->as_Bool()->_test._test );
  case CMPOPUCF2:
    return new cmpOpUCF2Oper(_leaf->as_Bool()->_test._test );
  case VECZ:
    return new vecZOper( );
  case CMPOP_VCMPPD:
    return new cmpOp_vcmppdOper(_leaf->as_Bool()->_test._test );
  case _ADDP_ANY_REGP_RREGL:    return NULL;
  case _LSHIFTL_RREGL_IMMI2:    return NULL;
  case _CONVI2L_RREGI_:    return NULL;
  case _LSHIFTL__CONVI2L_RREGI__IMMI2:    return NULL;
  case _ADDP_ANY_REGP__LSHIFTL_RREGL_IMMI2:    return NULL;
  case _ADDP_ANY_REGP__CONVI2L_RREGI_:    return NULL;
  case _ADDP_ANY_REGP__LSHIFTL__CONVI2L_RREGI__IMMI2:    return NULL;
  case _DECODEN_RREGN_:    return NULL;
  case _ADDP__DECODEN_RREGN__RREGL:    return NULL;
  case _ADDP__DECODEN_RREGN___LSHIFTL_RREGL_IMMI2:    return NULL;
  case _ADDP__DECODEN_RREGN___CONVI2L_RREGI_:    return NULL;
  case _ADDP__DECODEN_RREGN___LSHIFTL__CONVI2L_RREGI__IMMI2:    return NULL;
  case _LOADB_MEMORY_:    return NULL;
  case _LOADUB_MEMORY_:    return NULL;
  case _ANDI__LOADUB_MEMORY__IMMI:    return NULL;
  case _LOADS_MEMORY_:    return NULL;
  case _LSHIFTI__LOADS_MEMORY__IMMI_24:    return NULL;
  case _LOADUS_MEMORY_:    return NULL;
  case _LSHIFTI__LOADUS_MEMORY__IMMI_24:    return NULL;
  case _ANDI__LOADUS_MEMORY__IMMI_255:    return NULL;
  case _ANDI__LOADUS_MEMORY__IMMI:    return NULL;
  case _LOADI_MEMORY_:    return NULL;
  case _LSHIFTI__LOADI_MEMORY__IMMI_24:    return NULL;
  case _LSHIFTI__LOADI_MEMORY__IMMI_16:    return NULL;
  case _ANDI__LOADI_MEMORY__IMMI_255:    return NULL;
  case _ANDI__LOADI_MEMORY__IMMI_65535:    return NULL;
  case _ANDI__LOADI_MEMORY__IMMU31:    return NULL;
  case _CONVI2L__LOADI_MEMORY__:    return NULL;
  case _LOADL_MEMORY_:    return NULL;
  case _CASTP2X_RREGP_:    return NULL;
  case _CASTP2X__DECODEN_RREGN__:    return NULL;
  case _ADDL__LSHIFTL_RREGL_IMMI2_IMML32:    return NULL;
  case _BINARY_CMPOP_RFLAGSREG:    return NULL;
  case _BINARY_RREGI_RREGI:    return NULL;
  case _BINARY_CMPOPU_RFLAGSREGU:    return NULL;
  case _BINARY_CMPOPUCF_RFLAGSREGUCF:    return NULL;
  case _BINARY_RREGI__LOADI_MEMORY_:    return NULL;
  case _BINARY_RREGN_RREGN:    return NULL;
  case _BINARY_RREGP_RREGP:    return NULL;
  case _BINARY_RREGL_RREGL:    return NULL;
  case _BINARY_RREGL__LOADL_MEMORY_:    return NULL;
  case _BINARY_REGF_REGF:    return NULL;
  case _BINARY_REGD_REGD:    return NULL;
  case _ADDI__LOADI_MEMORY__RREGI:    return NULL;
  case _ADDI_RREGI__LOADI_MEMORY_:    return NULL;
  case _ADDI__LOADI_MEMORY__IMMI:    return NULL;
  case _ADDI__LOADI_MEMORY__IMMI1:    return NULL;
  case _ADDI__LOADI_MEMORY__IMMI_M1:    return NULL;
  case _ADDL__LOADL_MEMORY__RREGL:    return NULL;
  case _ADDL_RREGL__LOADL_MEMORY_:    return NULL;
  case _ADDL__LOADL_MEMORY__IMML32:    return NULL;
  case _ADDL__LOADL_MEMORY__IMML1:    return NULL;
  case _ADDL__LOADL_MEMORY__IMML_M1:    return NULL;
  case _BINARY_RAX_REGP_RREGP:    return NULL;
  case _BINARY_RAX_REGI_RREGI:    return NULL;
  case _BINARY_RAX_REGL_RREGL:    return NULL;
  case _BINARY_RAX_REGN_RREGN:    return NULL;
  case _SUBI__LOADI_MEMORY__RREGI:    return NULL;
  case _SUBI__LOADI_MEMORY__IMMI:    return NULL;
  case _SUBL__LOADL_MEMORY__RREGL:    return NULL;
  case _SUBL__LOADL_MEMORY__IMML32:    return NULL;
  case _SUBI_IMMI0_RREGI:    return NULL;
  case _SUBI_IMMI0__LOADI_MEMORY_:    return NULL;
  case _SUBL_IMML0__LOADL_MEMORY_:    return NULL;
  case _LSHIFTI__LOADI_MEMORY__IMMI1:    return NULL;
  case _LSHIFTI__LOADI_MEMORY__IMMI8:    return NULL;
  case _LSHIFTI__LOADI_MEMORY__RCX_REGI:    return NULL;
  case _RSHIFTI__LOADI_MEMORY__IMMI1:    return NULL;
  case _RSHIFTI__LOADI_MEMORY__IMMI8:    return NULL;
  case _RSHIFTI__LOADI_MEMORY__RCX_REGI:    return NULL;
  case _URSHIFTI__LOADI_MEMORY__IMMI1:    return NULL;
  case _URSHIFTI__LOADI_MEMORY__IMMI8:    return NULL;
  case _URSHIFTI__LOADI_MEMORY__RCX_REGI:    return NULL;
  case _LSHIFTL__LOADL_MEMORY__IMMI1:    return NULL;
  case _LSHIFTL__LOADL_MEMORY__IMMI8:    return NULL;
  case _LSHIFTL__LOADL_MEMORY__RCX_REGI:    return NULL;
  case _RSHIFTL__LOADL_MEMORY__IMMI1:    return NULL;
  case _RSHIFTL__LOADL_MEMORY__IMMI8:    return NULL;
  case _RSHIFTL__LOADL_MEMORY__RCX_REGI:    return NULL;
  case _URSHIFTL__LOADL_MEMORY__IMMI1:    return NULL;
  case _URSHIFTL__LOADL_MEMORY__IMMI8:    return NULL;
  case _URSHIFTL__LOADL_MEMORY__RCX_REGI:    return NULL;
  case _LSHIFTI_RREGI_IMMI_24:    return NULL;
  case _LSHIFTI_RREGI_IMMI_16:    return NULL;
  case _LSHIFTI_RREGI_IMMI1:    return NULL;
  case _URSHIFTI_RREGI_IMMI_M1:    return NULL;
  case _LSHIFTI_RREGI_IMMI8:    return NULL;
  case _URSHIFTI_RREGI_IMMI8:    return NULL;
  case _LSHIFTI_NO_RCX_REGI_RCX_REGI:    return NULL;
  case _SUBI_IMMI0_RCX_REGI:    return NULL;
  case _URSHIFTI_NO_RCX_REGI__SUBI_IMMI0_RCX_REGI:    return NULL;
  case _SUBI_IMMI_32_RCX_REGI:    return NULL;
  case _URSHIFTI_NO_RCX_REGI__SUBI_IMMI_32_RCX_REGI:    return NULL;
  case _URSHIFTI_RREGI_IMMI1:    return NULL;
  case _LSHIFTI_RREGI_IMMI_M1:    return NULL;
  case _URSHIFTI_NO_RCX_REGI_RCX_REGI:    return NULL;
  case _LSHIFTI_NO_RCX_REGI__SUBI_IMMI0_RCX_REGI:    return NULL;
  case _LSHIFTI_NO_RCX_REGI__SUBI_IMMI_32_RCX_REGI:    return NULL;
  case _LSHIFTL_RREGL_IMMI1:    return NULL;
  case _URSHIFTL_RREGL_IMMI_M1:    return NULL;
  case _LSHIFTL_RREGL_IMMI8:    return NULL;
  case _URSHIFTL_RREGL_IMMI8:    return NULL;
  case _LSHIFTL_NO_RCX_REGL_RCX_REGI:    return NULL;
  case _URSHIFTL_NO_RCX_REGL__SUBI_IMMI0_RCX_REGI:    return NULL;
  case _SUBI_IMMI_64_RCX_REGI:    return NULL;
  case _URSHIFTL_NO_RCX_REGL__SUBI_IMMI_64_RCX_REGI:    return NULL;
  case _URSHIFTL_RREGL_IMMI1:    return NULL;
  case _LSHIFTL_RREGL_IMMI_M1:    return NULL;
  case _URSHIFTL_NO_RCX_REGL_RCX_REGI:    return NULL;
  case _LSHIFTL_NO_RCX_REGL__SUBI_IMMI0_RCX_REGI:    return NULL;
  case _LSHIFTL_NO_RCX_REGL__SUBI_IMMI_64_RCX_REGI:    return NULL;
  case _ANDI_RREGI_IMMI_255:    return NULL;
  case _ANDI_RREGI_IMMI_65535:    return NULL;
  case _ANDI__LOADI_MEMORY__RREGI:    return NULL;
  case _ANDI_RREGI__LOADI_MEMORY_:    return NULL;
  case _ANDI__LOADI_MEMORY__IMMI:    return NULL;
  case _XORI_RREGI_IMMI_M1:    return NULL;
  case _ADDI_RREGI_IMMI_M1:    return NULL;
  case _ORI__LOADI_MEMORY__RREGI:    return NULL;
  case _ORI_RREGI__LOADI_MEMORY_:    return NULL;
  case _ORI__LOADI_MEMORY__IMMI:    return NULL;
  case _XORI__LOADI_MEMORY__RREGI:    return NULL;
  case _XORI_RREGI__LOADI_MEMORY_:    return NULL;
  case _XORI__LOADI_MEMORY__IMMI:    return NULL;
  case _ANDL__LOADL_MEMORY__RREGL:    return NULL;
  case _ANDL_RREGL__LOADL_MEMORY_:    return NULL;
  case _ANDL__LOADL_MEMORY__IMML32:    return NULL;
  case _XORL_RREGL_IMML_M1:    return NULL;
  case _SUBL_IMML0_RREGL:    return NULL;
  case _ADDL_RREGL_IMML_M1:    return NULL;
  case _CASTP2X_ANY_REGP_:    return NULL;
  case _ORL__LOADL_MEMORY__RREGL:    return NULL;
  case _ORL_RREGL__LOADL_MEMORY_:    return NULL;
  case _ORL__LOADL_MEMORY__IMML32:    return NULL;
  case _XORL__LOADL_MEMORY__RREGL:    return NULL;
  case _XORL_RREGL__LOADL_MEMORY_:    return NULL;
  case _XORL__LOADL_MEMORY__IMML32:    return NULL;
  case _CMPLTMASK_RREGI_RREGI:    return NULL;
  case _ANDI__CMPLTMASK_RREGI_RREGI_RREGI:    return NULL;
  case _SUBI_RREGI_RREGI:    return NULL;
  case _ANDI_RREGI__CMPLTMASK_RREGI_RREGI:    return NULL;
  case _LOADF_MEMORY_:    return NULL;
  case _LOADD_MEMORY_:    return NULL;
  case _BINARY_RDI_REGP_RCX_REGI:    return NULL;
  case _BINARY_RSI_REGP_RDX_REGI:    return NULL;
  case _BINARY_RDI_REGP_RDX_REGI:    return NULL;
  case _BINARY_RSI_REGP_IMMI:    return NULL;
  case _BINARY_RSI_REGP_RAX_REGI:    return NULL;
  case _BINARY_RDI_REGP_RSI_REGP:    return NULL;
  case _ANDI_RREGI_IMMI:    return NULL;
  case _LOADP_MEMORY_:    return NULL;
  case _LOADN_MEMORY_:    return NULL;
  case _LOADNKLASS_MEMORY_:    return NULL;
  case _ANDL_RREGL_IMML32:    return NULL;
  case _PARTIALSUBTYPECHECK_RSI_REGP_RAX_REGP:    return NULL;
  case _CONVF2D_REGF_:    return NULL;
  case _SQRTD__CONVF2D_REGF__:    return NULL;
  case _CONVF2D__LOADF_MEMORY__:    return NULL;
  case _SQRTD__CONVF2D__LOADF_MEMORY___:    return NULL;
  case _CONVF2D_IMMF_:    return NULL;
  case _SQRTD__CONVF2D_IMMF__:    return NULL;
  case _LOADVECTOR_MEMORY_:    return NULL;
  case _BINARY_CMPOP_VCMPPD_IMMI8:    return NULL;
  case _BINARY_VECY_VECY:    return NULL;
  
  default:
    fprintf(stderr, "Default MachOper Generator invoked for: \n");
    fprintf(stderr, "   opcode = %d\n", opcode);
    break;
  }
  return NULL;
};


//------------------------- MachNode Generator ---------------
// A switch statement on the dense-packed user-defined type system
// that invokes 'new' on the corresponding class constructor.

MachNode *State::MachNodeGenerator(int opcode){
  switch(opcode) {
  case loadB_rule: {
      loadBNode *node = new loadBNode();
      return node;
    }
  case loadB2L_rule: {
      loadB2LNode *node = new loadB2LNode();
      return node;
    }
  case loadUB_rule: {
      loadUBNode *node = new loadUBNode();
      return node;
    }
  case loadUB2L_rule: {
      loadUB2LNode *node = new loadUB2LNode();
      return node;
    }
  case loadUB2L_immI_rule: {
      loadUB2L_immINode *node = new loadUB2L_immINode();
      return node;
    }
  case loadS_rule: {
      loadSNode *node = new loadSNode();
      return node;
    }
  case loadS2B_rule: {
      loadS2BNode *node = new loadS2BNode();
      return node;
    }
  case loadS2L_rule: {
      loadS2LNode *node = new loadS2LNode();
      return node;
    }
  case loadUS_rule: {
      loadUSNode *node = new loadUSNode();
      return node;
    }
  case loadUS2B_rule: {
      loadUS2BNode *node = new loadUS2BNode();
      return node;
    }
  case loadUS2L_rule: {
      loadUS2LNode *node = new loadUS2LNode();
      return node;
    }
  case loadUS2L_immI_255_rule: {
      loadUS2L_immI_255Node *node = new loadUS2L_immI_255Node();
      return node;
    }
  case loadUS2L_immI_rule: {
      loadUS2L_immINode *node = new loadUS2L_immINode();
      return node;
    }
  case loadI_rule: {
      loadINode *node = new loadINode();
      return node;
    }
  case loadI2B_rule: {
      loadI2BNode *node = new loadI2BNode();
      return node;
    }
  case loadI2UB_rule: {
      loadI2UBNode *node = new loadI2UBNode();
      return node;
    }
  case loadI2S_rule: {
      loadI2SNode *node = new loadI2SNode();
      return node;
    }
  case loadI2US_rule: {
      loadI2USNode *node = new loadI2USNode();
      return node;
    }
  case loadI2L_rule: {
      loadI2LNode *node = new loadI2LNode();
      return node;
    }
  case loadI2L_immI_255_rule: {
      loadI2L_immI_255Node *node = new loadI2L_immI_255Node();
      return node;
    }
  case loadI2L_immI_65535_rule: {
      loadI2L_immI_65535Node *node = new loadI2L_immI_65535Node();
      return node;
    }
  case loadI2L_immU31_rule: {
      loadI2L_immU31Node *node = new loadI2L_immU31Node();
      return node;
    }
  case loadUI2L_rule: {
      loadUI2LNode *node = new loadUI2LNode();
      return node;
    }
  case loadL_rule: {
      loadLNode *node = new loadLNode();
      return node;
    }
  case loadRange_rule: {
      loadRangeNode *node = new loadRangeNode();
      return node;
    }
  case loadP_rule: {
      loadPNode *node = new loadPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadN_rule: {
      loadNNode *node = new loadNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadKlass_rule: {
      loadKlassNode *node = new loadKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadNKlass_rule: {
      loadNKlassNode *node = new loadNKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadF_rule: {
      loadFNode *node = new loadFNode();
      return node;
    }
  case loadD_partial_rule: {
      loadD_partialNode *node = new loadD_partialNode();
      return node;
    }
  case loadD_rule: {
      loadDNode *node = new loadDNode();
      return node;
    }
  case leaP8_rule: {
      leaP8Node *node = new leaP8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaP32_rule: {
      leaP32Node *node = new leaP32Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxOff_rule: {
      leaPIdxOffNode *node = new leaPIdxOffNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxScale_rule: {
      leaPIdxScaleNode *node = new leaPIdxScaleNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPPosIdxScale_rule: {
      leaPPosIdxScaleNode *node = new leaPPosIdxScaleNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxScaleOff_rule: {
      leaPIdxScaleOffNode *node = new leaPIdxScaleOffNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPPosIdxOff_rule: {
      leaPPosIdxOffNode *node = new leaPPosIdxOffNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPPosIdxScaleOff_rule: {
      leaPPosIdxScaleOffNode *node = new leaPPosIdxScaleOffNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPCompressedOopOffset_rule: {
      leaPCompressedOopOffsetNode *node = new leaPCompressedOopOffsetNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaP8Narrow_rule: {
      leaP8NarrowNode *node = new leaP8NarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaP32Narrow_rule: {
      leaP32NarrowNode *node = new leaP32NarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxOffNarrow_rule: {
      leaPIdxOffNarrowNode *node = new leaPIdxOffNarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxScaleNarrow_rule: {
      leaPIdxScaleNarrowNode *node = new leaPIdxScaleNarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPIdxScaleOffNarrow_rule: {
      leaPIdxScaleOffNarrowNode *node = new leaPIdxScaleOffNarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPPosIdxOffNarrow_rule: {
      leaPPosIdxOffNarrowNode *node = new leaPPosIdxOffNarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaPPosIdxScaleOffNarrow_rule: {
      leaPPosIdxScaleOffNarrowNode *node = new leaPPosIdxScaleOffNarrowNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConI_rule: {
      loadConINode *node = new loadConINode();
      node->_opnd_array[1] = new immIOper(_leaf->get_int() );
      return node;
    }
  case loadConI0_rule: {
      loadConI0Node *node = new loadConI0Node();
      return node;
    }
  case loadConL_rule: {
      loadConLNode *node = new loadConLNode();
      node->_opnd_array[1] = new immLOper(_leaf->get_long() );
      return node;
    }
  case loadConL0_rule: {
      loadConL0Node *node = new loadConL0Node();
      return node;
    }
  case loadConUL32_rule: {
      loadConUL32Node *node = new loadConUL32Node();
      node->_opnd_array[1] = new immUL32Oper(_leaf->get_long() );
      return node;
    }
  case loadConL32_rule: {
      loadConL32Node *node = new loadConL32Node();
      node->_opnd_array[1] = new immL32Oper(_leaf->get_long() );
      return node;
    }
  case loadConP_rule: {
      loadConPNode *node = new loadConPNode();
      node->_opnd_array[1] = new immPOper(_leaf->bottom_type()->is_ptr() );
      return node;
    }
  case loadConP0_rule: {
      loadConP0Node *node = new loadConP0Node();
      return node;
    }
  case loadConP31_rule: {
      loadConP31Node *node = new loadConP31Node();
      return node;
    }
  case loadConF_rule: {
      loadConFNode *node = new loadConFNode();
      node->_opnd_array[1] = new immFOper(_leaf->getf() );
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConN0_rule: {
      loadConN0Node *node = new loadConN0Node();
      return node;
    }
  case loadConN_rule: {
      loadConNNode *node = new loadConNNode();
      node->_opnd_array[1] = new immNOper(_leaf->bottom_type()->is_narrowoop() );
      return node;
    }
  case loadConNKlass_rule: {
      loadConNKlassNode *node = new loadConNKlassNode();
      node->_opnd_array[1] = new immNKlassOper(_leaf->bottom_type()->is_narrowklass() );
      return node;
    }
  case loadConF0_rule: {
      loadConF0Node *node = new loadConF0Node();
      node->_opnd_array[1] = new immF0Oper(_leaf->getf() );
      return node;
    }
  case loadConD_rule: {
      loadConDNode *node = new loadConDNode();
      node->_opnd_array[1] = new immDOper(_leaf->getd() );
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadConD0_rule: {
      loadConD0Node *node = new loadConD0Node();
      node->_opnd_array[1] = new immD0Oper(_leaf->getd() );
      return node;
    }
  case loadSSI_rule: {
      loadSSINode *node = new loadSSINode();
      return node;
    }
  case loadSSL_rule: {
      loadSSLNode *node = new loadSSLNode();
      return node;
    }
  case loadSSP_rule: {
      loadSSPNode *node = new loadSSPNode();
      return node;
    }
  case loadSSF_rule: {
      loadSSFNode *node = new loadSSFNode();
      return node;
    }
  case loadSSD_rule: {
      loadSSDNode *node = new loadSSDNode();
      return node;
    }
  case prefetchAlloc_rule: {
      prefetchAllocNode *node = new prefetchAllocNode();
      return node;
    }
  case prefetchAllocNTA_rule: {
      prefetchAllocNTANode *node = new prefetchAllocNTANode();
      return node;
    }
  case prefetchAllocT0_rule: {
      prefetchAllocT0Node *node = new prefetchAllocT0Node();
      return node;
    }
  case prefetchAllocT2_rule: {
      prefetchAllocT2Node *node = new prefetchAllocT2Node();
      return node;
    }
  case storeB_rule: {
      storeBNode *node = new storeBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeC_rule: {
      storeCNode *node = new storeCNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeI_rule: {
      storeINode *node = new storeINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeL_rule: {
      storeLNode *node = new storeLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeP_rule: {
      storePNode *node = new storePNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmP0_rule: {
      storeImmP0Node *node = new storeImmP0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmP_rule: {
      storeImmPNode *node = new storeImmPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeN_rule: {
      storeNNode *node = new storeNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeNKlass_rule: {
      storeNKlassNode *node = new storeNKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmN0_rule: {
      storeImmN0Node *node = new storeImmN0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmN_rule: {
      storeImmNNode *node = new storeImmNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmNKlass_rule: {
      storeImmNKlassNode *node = new storeImmNKlassNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmI0_rule: {
      storeImmI0Node *node = new storeImmI0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmI_rule: {
      storeImmINode *node = new storeImmINode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmL0_rule: {
      storeImmL0Node *node = new storeImmL0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmL_rule: {
      storeImmLNode *node = new storeImmLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmC0_rule: {
      storeImmC0Node *node = new storeImmC0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmI16_rule: {
      storeImmI16Node *node = new storeImmI16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmB0_rule: {
      storeImmB0Node *node = new storeImmB0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmB_rule: {
      storeImmBNode *node = new storeImmBNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmCM0_reg_rule: {
      storeImmCM0_regNode *node = new storeImmCM0_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeImmCM0_rule: {
      storeImmCM0Node *node = new storeImmCM0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeF_rule: {
      storeFNode *node = new storeFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeF0_rule: {
      storeF0Node *node = new storeF0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeF_imm_rule: {
      storeF_immNode *node = new storeF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeD_rule: {
      storeDNode *node = new storeDNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeD0_imm_rule: {
      storeD0_immNode *node = new storeD0_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeD0_rule: {
      storeD0Node *node = new storeD0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeSSI_rule: {
      storeSSINode *node = new storeSSINode();
      return node;
    }
  case storeSSL_rule: {
      storeSSLNode *node = new storeSSLNode();
      return node;
    }
  case storeSSP_rule: {
      storeSSPNode *node = new storeSSPNode();
      return node;
    }
  case storeSSF_rule: {
      storeSSFNode *node = new storeSSFNode();
      return node;
    }
  case storeSSD_rule: {
      storeSSDNode *node = new storeSSDNode();
      return node;
    }
  case bytes_reverse_int_rule: {
      bytes_reverse_intNode *node = new bytes_reverse_intNode();
      return node;
    }
  case bytes_reverse_long_rule: {
      bytes_reverse_longNode *node = new bytes_reverse_longNode();
      return node;
    }
  case bytes_reverse_unsigned_short_rule: {
      bytes_reverse_unsigned_shortNode *node = new bytes_reverse_unsigned_shortNode();
      return node;
    }
  case bytes_reverse_short_rule: {
      bytes_reverse_shortNode *node = new bytes_reverse_shortNode();
      return node;
    }
  case countLeadingZerosI_rule: {
      countLeadingZerosINode *node = new countLeadingZerosINode();
      return node;
    }
  case countLeadingZerosI_bsr_rule: {
      countLeadingZerosI_bsrNode *node = new countLeadingZerosI_bsrNode();
      return node;
    }
  case countLeadingZerosL_rule: {
      countLeadingZerosLNode *node = new countLeadingZerosLNode();
      return node;
    }
  case countLeadingZerosL_bsr_rule: {
      countLeadingZerosL_bsrNode *node = new countLeadingZerosL_bsrNode();
      return node;
    }
  case countTrailingZerosI_rule: {
      countTrailingZerosINode *node = new countTrailingZerosINode();
      return node;
    }
  case countTrailingZerosI_bsf_rule: {
      countTrailingZerosI_bsfNode *node = new countTrailingZerosI_bsfNode();
      return node;
    }
  case countTrailingZerosL_rule: {
      countTrailingZerosLNode *node = new countTrailingZerosLNode();
      return node;
    }
  case countTrailingZerosL_bsf_rule: {
      countTrailingZerosL_bsfNode *node = new countTrailingZerosL_bsfNode();
      return node;
    }
  case popCountI_rule: {
      popCountINode *node = new popCountINode();
      return node;
    }
  case popCountI_mem_rule: {
      popCountI_memNode *node = new popCountI_memNode();
      return node;
    }
  case popCountL_rule: {
      popCountLNode *node = new popCountLNode();
      return node;
    }
  case popCountL_mem_rule: {
      popCountL_memNode *node = new popCountL_memNode();
      return node;
    }
  case membar_acquire_rule: {
      membar_acquireNode *node = new membar_acquireNode();
      return node;
    }
  case membar_acquire_0_rule: {
      membar_acquire_0Node *node = new membar_acquire_0Node();
      return node;
    }
  case membar_acquire_lock_rule: {
      membar_acquire_lockNode *node = new membar_acquire_lockNode();
      return node;
    }
  case membar_release_rule: {
      membar_releaseNode *node = new membar_releaseNode();
      return node;
    }
  case membar_release_0_rule: {
      membar_release_0Node *node = new membar_release_0Node();
      return node;
    }
  case membar_release_lock_rule: {
      membar_release_lockNode *node = new membar_release_lockNode();
      return node;
    }
  case membar_volatile_rule: {
      membar_volatileNode *node = new membar_volatileNode();
      node->set_opnd_array(1, MachOperGenerator(RFLAGSREG));
      return node;
    }
  case unnecessary_membar_volatile_rule: {
      unnecessary_membar_volatileNode *node = new unnecessary_membar_volatileNode();
      return node;
    }
  case membar_storestore_rule: {
      membar_storestoreNode *node = new membar_storestoreNode();
      return node;
    }
  case castX2P_rule: {
      castX2PNode *node = new castX2PNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castP2X_rule: {
      castP2XNode *node = new castP2XNode();
      return node;
    }
  case convP2I_rule: {
      convP2INode *node = new convP2INode();
      return node;
    }
  case convN2I_rule: {
      convN2INode *node = new convN2INode();
      return node;
    }
  case encodeHeapOop_rule: {
      encodeHeapOopNode *node = new encodeHeapOopNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeHeapOop_not_null_rule: {
      encodeHeapOop_not_nullNode *node = new encodeHeapOop_not_nullNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeHeapOop_rule: {
      decodeHeapOopNode *node = new decodeHeapOopNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeHeapOop_not_null_rule: {
      decodeHeapOop_not_nullNode *node = new decodeHeapOop_not_nullNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case encodeKlass_not_null_rule: {
      encodeKlass_not_nullNode *node = new encodeKlass_not_nullNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decodeKlass_not_null_rule: {
      decodeKlass_not_nullNode *node = new decodeKlass_not_nullNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case jumpXtnd_offset_rule: {
      jumpXtnd_offsetNode *node = new jumpXtnd_offsetNode();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case jumpXtnd_addr_rule: {
      jumpXtnd_addrNode *node = new jumpXtnd_addrNode();
      node->set_opnd_array(4, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case jumpXtnd_rule: {
      jumpXtndNode *node = new jumpXtndNode();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cmovI_reg_rule: {
      cmovI_regNode *node = new cmovI_regNode();
      return node;
    }
  case cmovI_regU_rule: {
      cmovI_regUNode *node = new cmovI_regUNode();
      return node;
    }
  case cmovI_regUCF_rule: {
      cmovI_regUCFNode *node = new cmovI_regUCFNode();
      return node;
    }
  case cmovI_mem_rule: {
      cmovI_memNode *node = new cmovI_memNode();
      return node;
    }
  case cmovI_memU_rule: {
      cmovI_memUNode *node = new cmovI_memUNode();
      return node;
    }
  case cmovI_memUCF_rule: {
      cmovI_memUCFNode *node = new cmovI_memUCFNode();
      return node;
    }
  case cmovN_reg_rule: {
      cmovN_regNode *node = new cmovN_regNode();
      return node;
    }
  case cmovN_regU_rule: {
      cmovN_regUNode *node = new cmovN_regUNode();
      return node;
    }
  case cmovN_regUCF_rule: {
      cmovN_regUCFNode *node = new cmovN_regUCFNode();
      return node;
    }
  case cmovP_reg_rule: {
      cmovP_regNode *node = new cmovP_regNode();
      return node;
    }
  case cmovP_regU_rule: {
      cmovP_regUNode *node = new cmovP_regUNode();
      return node;
    }
  case cmovP_regUCF_rule: {
      cmovP_regUCFNode *node = new cmovP_regUCFNode();
      return node;
    }
  case cmovL_reg_rule: {
      cmovL_regNode *node = new cmovL_regNode();
      return node;
    }
  case cmovL_mem_rule: {
      cmovL_memNode *node = new cmovL_memNode();
      return node;
    }
  case cmovL_regU_rule: {
      cmovL_regUNode *node = new cmovL_regUNode();
      return node;
    }
  case cmovL_regUCF_rule: {
      cmovL_regUCFNode *node = new cmovL_regUCFNode();
      return node;
    }
  case cmovL_memU_rule: {
      cmovL_memUNode *node = new cmovL_memUNode();
      return node;
    }
  case cmovL_memUCF_rule: {
      cmovL_memUCFNode *node = new cmovL_memUCFNode();
      return node;
    }
  case cmovF_reg_rule: {
      cmovF_regNode *node = new cmovF_regNode();
      return node;
    }
  case cmovF_regU_rule: {
      cmovF_regUNode *node = new cmovF_regUNode();
      return node;
    }
  case cmovF_regUCF_rule: {
      cmovF_regUCFNode *node = new cmovF_regUCFNode();
      return node;
    }
  case cmovD_reg_rule: {
      cmovD_regNode *node = new cmovD_regNode();
      return node;
    }
  case cmovD_regU_rule: {
      cmovD_regUNode *node = new cmovD_regUNode();
      return node;
    }
  case cmovD_regUCF_rule: {
      cmovD_regUCFNode *node = new cmovD_regUCFNode();
      return node;
    }
  case addI_rReg_rule: {
      addI_rRegNode *node = new addI_rRegNode();
      return node;
    }
  case addI_rReg_imm_rule: {
      addI_rReg_immNode *node = new addI_rReg_immNode();
      return node;
    }
  case addI_rReg_mem_rule: {
      addI_rReg_memNode *node = new addI_rReg_memNode();
      return node;
    }
  case addI_rReg_mem_0_rule: {
      addI_rReg_mem_0Node *node = new addI_rReg_mem_0Node();
      return node;
    }
  case addI_mem_rReg_rule: {
      addI_mem_rRegNode *node = new addI_mem_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addI_mem_rReg_0_rule: {
      addI_mem_rReg_0Node *node = new addI_mem_rReg_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addI_mem_imm_rule: {
      addI_mem_immNode *node = new addI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case incI_rReg_rule: {
      incI_rRegNode *node = new incI_rRegNode();
      return node;
    }
  case incI_mem_rule: {
      incI_memNode *node = new incI_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decI_rReg_rule: {
      decI_rRegNode *node = new decI_rRegNode();
      return node;
    }
  case decI_mem_rule: {
      decI_memNode *node = new decI_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaI_rReg_immI_rule: {
      leaI_rReg_immINode *node = new leaI_rReg_immINode();
      return node;
    }
  case addL_rReg_rule: {
      addL_rRegNode *node = new addL_rRegNode();
      return node;
    }
  case addL_rReg_imm_rule: {
      addL_rReg_immNode *node = new addL_rReg_immNode();
      return node;
    }
  case addL_rReg_mem_rule: {
      addL_rReg_memNode *node = new addL_rReg_memNode();
      return node;
    }
  case addL_rReg_mem_0_rule: {
      addL_rReg_mem_0Node *node = new addL_rReg_mem_0Node();
      return node;
    }
  case addL_mem_rReg_rule: {
      addL_mem_rRegNode *node = new addL_mem_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addL_mem_rReg_0_rule: {
      addL_mem_rReg_0Node *node = new addL_mem_rReg_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addL_mem_imm_rule: {
      addL_mem_immNode *node = new addL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case incL_rReg_rule: {
      incL_rRegNode *node = new incL_rRegNode();
      return node;
    }
  case incL_mem_rule: {
      incL_memNode *node = new incL_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case decL_rReg_rule: {
      decL_rRegNode *node = new decL_rRegNode();
      return node;
    }
  case decL_mem_rule: {
      decL_memNode *node = new decL_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaL_rReg_immL_rule: {
      leaL_rReg_immLNode *node = new leaL_rReg_immLNode();
      return node;
    }
  case addP_rReg_rule: {
      addP_rRegNode *node = new addP_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addP_rReg_imm_rule: {
      addP_rReg_immNode *node = new addP_rReg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case leaP_rReg_imm_rule: {
      leaP_rReg_immNode *node = new leaP_rReg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case checkCastPP_rule: {
      checkCastPPNode *node = new checkCastPPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castPP_rule: {
      castPPNode *node = new castPPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case castII_rule: {
      castIINode *node = new castIINode();
      return node;
    }
  case loadPLocked_rule: {
      loadPLockedNode *node = new loadPLockedNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storePConditional_rule: {
      storePConditionalNode *node = new storePConditionalNode();
      return node;
    }
  case storeIConditional_rule: {
      storeIConditionalNode *node = new storeIConditionalNode();
      return node;
    }
  case storeLConditional_rule: {
      storeLConditionalNode *node = new storeLConditionalNode();
      return node;
    }
  case compareAndSwapP_rule: {
      compareAndSwapPNode *node = new compareAndSwapPNode();
      return node;
    }
  case compareAndSwapP_0_rule: {
      compareAndSwapP_0Node *node = new compareAndSwapP_0Node();
      return node;
    }
  case compareAndSwapL_rule: {
      compareAndSwapLNode *node = new compareAndSwapLNode();
      return node;
    }
  case compareAndSwapL_0_rule: {
      compareAndSwapL_0Node *node = new compareAndSwapL_0Node();
      return node;
    }
  case compareAndSwapI_rule: {
      compareAndSwapINode *node = new compareAndSwapINode();
      return node;
    }
  case compareAndSwapI_0_rule: {
      compareAndSwapI_0Node *node = new compareAndSwapI_0Node();
      return node;
    }
  case compareAndSwapB_rule: {
      compareAndSwapBNode *node = new compareAndSwapBNode();
      return node;
    }
  case compareAndSwapB_0_rule: {
      compareAndSwapB_0Node *node = new compareAndSwapB_0Node();
      return node;
    }
  case compareAndSwapS_rule: {
      compareAndSwapSNode *node = new compareAndSwapSNode();
      return node;
    }
  case compareAndSwapS_0_rule: {
      compareAndSwapS_0Node *node = new compareAndSwapS_0Node();
      return node;
    }
  case compareAndSwapN_rule: {
      compareAndSwapNNode *node = new compareAndSwapNNode();
      return node;
    }
  case compareAndSwapN_0_rule: {
      compareAndSwapN_0Node *node = new compareAndSwapN_0Node();
      return node;
    }
  case compareAndExchangeB_rule: {
      compareAndExchangeBNode *node = new compareAndExchangeBNode();
      return node;
    }
  case compareAndExchangeS_rule: {
      compareAndExchangeSNode *node = new compareAndExchangeSNode();
      return node;
    }
  case compareAndExchangeI_rule: {
      compareAndExchangeINode *node = new compareAndExchangeINode();
      return node;
    }
  case compareAndExchangeL_rule: {
      compareAndExchangeLNode *node = new compareAndExchangeLNode();
      return node;
    }
  case compareAndExchangeN_rule: {
      compareAndExchangeNNode *node = new compareAndExchangeNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case compareAndExchangeP_rule: {
      compareAndExchangePNode *node = new compareAndExchangePNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xaddB_no_res_rule: {
      xaddB_no_resNode *node = new xaddB_no_resNode();
      return node;
    }
  case xaddB_rule: {
      xaddBNode *node = new xaddBNode();
      return node;
    }
  case xaddS_no_res_rule: {
      xaddS_no_resNode *node = new xaddS_no_resNode();
      return node;
    }
  case xaddS_rule: {
      xaddSNode *node = new xaddSNode();
      return node;
    }
  case xaddI_no_res_rule: {
      xaddI_no_resNode *node = new xaddI_no_resNode();
      return node;
    }
  case xaddI_rule: {
      xaddINode *node = new xaddINode();
      return node;
    }
  case xaddL_no_res_rule: {
      xaddL_no_resNode *node = new xaddL_no_resNode();
      return node;
    }
  case xaddL_rule: {
      xaddLNode *node = new xaddLNode();
      return node;
    }
  case xchgB_rule: {
      xchgBNode *node = new xchgBNode();
      return node;
    }
  case xchgS_rule: {
      xchgSNode *node = new xchgSNode();
      return node;
    }
  case xchgI_rule: {
      xchgINode *node = new xchgINode();
      return node;
    }
  case xchgL_rule: {
      xchgLNode *node = new xchgLNode();
      return node;
    }
  case xchgP_rule: {
      xchgPNode *node = new xchgPNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xchgN_rule: {
      xchgNNode *node = new xchgNNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subI_rReg_rule: {
      subI_rRegNode *node = new subI_rRegNode();
      return node;
    }
  case subI_rReg_imm_rule: {
      subI_rReg_immNode *node = new subI_rReg_immNode();
      return node;
    }
  case subI_rReg_mem_rule: {
      subI_rReg_memNode *node = new subI_rReg_memNode();
      return node;
    }
  case subI_mem_rReg_rule: {
      subI_mem_rRegNode *node = new subI_mem_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subI_mem_imm_rule: {
      subI_mem_immNode *node = new subI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subL_rReg_rule: {
      subL_rRegNode *node = new subL_rRegNode();
      return node;
    }
  case subL_rReg_imm_rule: {
      subL_rReg_immNode *node = new subL_rReg_immNode();
      return node;
    }
  case subL_rReg_mem_rule: {
      subL_rReg_memNode *node = new subL_rReg_memNode();
      return node;
    }
  case subL_mem_rReg_rule: {
      subL_mem_rRegNode *node = new subL_mem_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subL_mem_imm_rule: {
      subL_mem_immNode *node = new subL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subP_rReg_rule: {
      subP_rRegNode *node = new subP_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case negI_rReg_rule: {
      negI_rRegNode *node = new negI_rRegNode();
      return node;
    }
  case negI_mem_rule: {
      negI_memNode *node = new negI_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case negL_rReg_rule: {
      negL_rRegNode *node = new negL_rRegNode();
      return node;
    }
  case negL_mem_rule: {
      negL_memNode *node = new negL_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mulI_rReg_rule: {
      mulI_rRegNode *node = new mulI_rRegNode();
      return node;
    }
  case mulI_rReg_imm_rule: {
      mulI_rReg_immNode *node = new mulI_rReg_immNode();
      return node;
    }
  case mulI_mem_rule: {
      mulI_memNode *node = new mulI_memNode();
      return node;
    }
  case mulI_mem_0_rule: {
      mulI_mem_0Node *node = new mulI_mem_0Node();
      return node;
    }
  case mulI_mem_imm_rule: {
      mulI_mem_immNode *node = new mulI_mem_immNode();
      return node;
    }
  case mulL_rReg_rule: {
      mulL_rRegNode *node = new mulL_rRegNode();
      return node;
    }
  case mulL_rReg_imm_rule: {
      mulL_rReg_immNode *node = new mulL_rReg_immNode();
      return node;
    }
  case mulL_mem_rule: {
      mulL_memNode *node = new mulL_memNode();
      return node;
    }
  case mulL_mem_0_rule: {
      mulL_mem_0Node *node = new mulL_mem_0Node();
      return node;
    }
  case mulL_mem_imm_rule: {
      mulL_mem_immNode *node = new mulL_mem_immNode();
      return node;
    }
  case mulHiL_rReg_rule: {
      mulHiL_rRegNode *node = new mulHiL_rRegNode();
      return node;
    }
  case divI_rReg_rule: {
      divI_rRegNode *node = new divI_rRegNode();
      return node;
    }
  case divL_rReg_rule: {
      divL_rRegNode *node = new divL_rRegNode();
      return node;
    }
  case divModI_rReg_divmod_rule: {
      divModI_rReg_divmodNode *node = new divModI_rReg_divmodNode();
      return node;
    }
  case divModL_rReg_divmod_rule: {
      divModL_rReg_divmodNode *node = new divModL_rReg_divmodNode();
      return node;
    }
  case divL_10_rule: {
      divL_10Node *node = new divL_10Node();
      return node;
    }
  case modI_rReg_rule: {
      modI_rRegNode *node = new modI_rRegNode();
      return node;
    }
  case modL_rReg_rule: {
      modL_rRegNode *node = new modL_rRegNode();
      return node;
    }
  case salI_rReg_1_rule: {
      salI_rReg_1Node *node = new salI_rReg_1Node();
      return node;
    }
  case salI_mem_1_rule: {
      salI_mem_1Node *node = new salI_mem_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case salI_rReg_imm_rule: {
      salI_rReg_immNode *node = new salI_rReg_immNode();
      return node;
    }
  case salI_mem_imm_rule: {
      salI_mem_immNode *node = new salI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case salI_rReg_CL_rule: {
      salI_rReg_CLNode *node = new salI_rReg_CLNode();
      return node;
    }
  case salI_mem_CL_rule: {
      salI_mem_CLNode *node = new salI_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case sarI_rReg_1_rule: {
      sarI_rReg_1Node *node = new sarI_rReg_1Node();
      return node;
    }
  case sarI_mem_1_rule: {
      sarI_mem_1Node *node = new sarI_mem_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case sarI_rReg_imm_rule: {
      sarI_rReg_immNode *node = new sarI_rReg_immNode();
      return node;
    }
  case sarI_mem_imm_rule: {
      sarI_mem_immNode *node = new sarI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case sarI_rReg_CL_rule: {
      sarI_rReg_CLNode *node = new sarI_rReg_CLNode();
      return node;
    }
  case sarI_mem_CL_rule: {
      sarI_mem_CLNode *node = new sarI_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case shrI_rReg_1_rule: {
      shrI_rReg_1Node *node = new shrI_rReg_1Node();
      return node;
    }
  case shrI_mem_1_rule: {
      shrI_mem_1Node *node = new shrI_mem_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case shrI_rReg_imm_rule: {
      shrI_rReg_immNode *node = new shrI_rReg_immNode();
      return node;
    }
  case shrI_mem_imm_rule: {
      shrI_mem_immNode *node = new shrI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case shrI_rReg_CL_rule: {
      shrI_rReg_CLNode *node = new shrI_rReg_CLNode();
      return node;
    }
  case shrI_mem_CL_rule: {
      shrI_mem_CLNode *node = new shrI_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case salL_rReg_1_rule: {
      salL_rReg_1Node *node = new salL_rReg_1Node();
      return node;
    }
  case salL_mem_1_rule: {
      salL_mem_1Node *node = new salL_mem_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case salL_rReg_imm_rule: {
      salL_rReg_immNode *node = new salL_rReg_immNode();
      return node;
    }
  case salL_mem_imm_rule: {
      salL_mem_immNode *node = new salL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case salL_rReg_CL_rule: {
      salL_rReg_CLNode *node = new salL_rReg_CLNode();
      return node;
    }
  case salL_mem_CL_rule: {
      salL_mem_CLNode *node = new salL_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case sarL_rReg_1_rule: {
      sarL_rReg_1Node *node = new sarL_rReg_1Node();
      return node;
    }
  case sarL_mem_1_rule: {
      sarL_mem_1Node *node = new sarL_mem_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case sarL_rReg_imm_rule: {
      sarL_rReg_immNode *node = new sarL_rReg_immNode();
      return node;
    }
  case sarL_mem_imm_rule: {
      sarL_mem_immNode *node = new sarL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case sarL_rReg_CL_rule: {
      sarL_rReg_CLNode *node = new sarL_rReg_CLNode();
      return node;
    }
  case sarL_mem_CL_rule: {
      sarL_mem_CLNode *node = new sarL_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case shrL_rReg_1_rule: {
      shrL_rReg_1Node *node = new shrL_rReg_1Node();
      return node;
    }
  case shrL_mem_1_rule: {
      shrL_mem_1Node *node = new shrL_mem_1Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case shrL_rReg_imm_rule: {
      shrL_rReg_immNode *node = new shrL_rReg_immNode();
      return node;
    }
  case shrL_mem_imm_rule: {
      shrL_mem_immNode *node = new shrL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case shrL_rReg_CL_rule: {
      shrL_rReg_CLNode *node = new shrL_rReg_CLNode();
      return node;
    }
  case shrL_mem_CL_rule: {
      shrL_mem_CLNode *node = new shrL_mem_CLNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case i2b_rule: {
      i2bNode *node = new i2bNode();
      return node;
    }
  case i2s_rule: {
      i2sNode *node = new i2sNode();
      return node;
    }
  case rolI_rReg_i1_rule: {
      rolI_rReg_i1Node *node = new rolI_rReg_i1Node();
      return node;
    }
  case rolI_rReg_i1_0_rule: {
      rolI_rReg_i1_0Node *node = new rolI_rReg_i1_0Node();
      return node;
    }
  case rolI_rReg_i8_rule: {
      rolI_rReg_i8Node *node = new rolI_rReg_i8Node();
      return node;
    }
  case rolI_rReg_i8_0_rule: {
      rolI_rReg_i8_0Node *node = new rolI_rReg_i8_0Node();
      return node;
    }
  case rolI_rReg_Var_C0_rule: {
      rolI_rReg_Var_C0Node *node = new rolI_rReg_Var_C0Node();
      return node;
    }
  case rolI_rReg_Var_C0_0_rule: {
      rolI_rReg_Var_C0_0Node *node = new rolI_rReg_Var_C0_0Node();
      return node;
    }
  case rolI_rReg_Var_C32_rule: {
      rolI_rReg_Var_C32Node *node = new rolI_rReg_Var_C32Node();
      return node;
    }
  case rolI_rReg_Var_C32_0_rule: {
      rolI_rReg_Var_C32_0Node *node = new rolI_rReg_Var_C32_0Node();
      return node;
    }
  case rorI_rReg_i1_rule: {
      rorI_rReg_i1Node *node = new rorI_rReg_i1Node();
      return node;
    }
  case rorI_rReg_i1_0_rule: {
      rorI_rReg_i1_0Node *node = new rorI_rReg_i1_0Node();
      return node;
    }
  case rorI_rReg_i8_rule: {
      rorI_rReg_i8Node *node = new rorI_rReg_i8Node();
      return node;
    }
  case rorI_rReg_i8_0_rule: {
      rorI_rReg_i8_0Node *node = new rorI_rReg_i8_0Node();
      return node;
    }
  case rorI_rReg_Var_C0_rule: {
      rorI_rReg_Var_C0Node *node = new rorI_rReg_Var_C0Node();
      return node;
    }
  case rorI_rReg_Var_C0_0_rule: {
      rorI_rReg_Var_C0_0Node *node = new rorI_rReg_Var_C0_0Node();
      return node;
    }
  case rorI_rReg_Var_C32_rule: {
      rorI_rReg_Var_C32Node *node = new rorI_rReg_Var_C32Node();
      return node;
    }
  case rorI_rReg_Var_C32_0_rule: {
      rorI_rReg_Var_C32_0Node *node = new rorI_rReg_Var_C32_0Node();
      return node;
    }
  case rolL_rReg_i1_rule: {
      rolL_rReg_i1Node *node = new rolL_rReg_i1Node();
      return node;
    }
  case rolL_rReg_i1_0_rule: {
      rolL_rReg_i1_0Node *node = new rolL_rReg_i1_0Node();
      return node;
    }
  case rolL_rReg_i8_rule: {
      rolL_rReg_i8Node *node = new rolL_rReg_i8Node();
      return node;
    }
  case rolL_rReg_i8_0_rule: {
      rolL_rReg_i8_0Node *node = new rolL_rReg_i8_0Node();
      return node;
    }
  case rolL_rReg_Var_C0_rule: {
      rolL_rReg_Var_C0Node *node = new rolL_rReg_Var_C0Node();
      return node;
    }
  case rolL_rReg_Var_C0_0_rule: {
      rolL_rReg_Var_C0_0Node *node = new rolL_rReg_Var_C0_0Node();
      return node;
    }
  case rolL_rReg_Var_C64_rule: {
      rolL_rReg_Var_C64Node *node = new rolL_rReg_Var_C64Node();
      return node;
    }
  case rolL_rReg_Var_C64_0_rule: {
      rolL_rReg_Var_C64_0Node *node = new rolL_rReg_Var_C64_0Node();
      return node;
    }
  case rorL_rReg_i1_rule: {
      rorL_rReg_i1Node *node = new rorL_rReg_i1Node();
      return node;
    }
  case rorL_rReg_i1_0_rule: {
      rorL_rReg_i1_0Node *node = new rorL_rReg_i1_0Node();
      return node;
    }
  case rorL_rReg_i8_rule: {
      rorL_rReg_i8Node *node = new rorL_rReg_i8Node();
      return node;
    }
  case rorL_rReg_i8_0_rule: {
      rorL_rReg_i8_0Node *node = new rorL_rReg_i8_0Node();
      return node;
    }
  case rorL_rReg_Var_C0_rule: {
      rorL_rReg_Var_C0Node *node = new rorL_rReg_Var_C0Node();
      return node;
    }
  case rorL_rReg_Var_C0_0_rule: {
      rorL_rReg_Var_C0_0Node *node = new rorL_rReg_Var_C0_0Node();
      return node;
    }
  case rorL_rReg_Var_C64_rule: {
      rorL_rReg_Var_C64Node *node = new rorL_rReg_Var_C64Node();
      return node;
    }
  case rorL_rReg_Var_C64_0_rule: {
      rorL_rReg_Var_C64_0Node *node = new rorL_rReg_Var_C64_0Node();
      return node;
    }
  case andI_rReg_rule: {
      andI_rRegNode *node = new andI_rRegNode();
      return node;
    }
  case andI_rReg_imm255_rule: {
      andI_rReg_imm255Node *node = new andI_rReg_imm255Node();
      return node;
    }
  case andI2L_rReg_imm255_rule: {
      andI2L_rReg_imm255Node *node = new andI2L_rReg_imm255Node();
      return node;
    }
  case andI_rReg_imm65535_rule: {
      andI_rReg_imm65535Node *node = new andI_rReg_imm65535Node();
      return node;
    }
  case andI2L_rReg_imm65535_rule: {
      andI2L_rReg_imm65535Node *node = new andI2L_rReg_imm65535Node();
      return node;
    }
  case andI_rReg_imm_rule: {
      andI_rReg_immNode *node = new andI_rReg_immNode();
      return node;
    }
  case andI_rReg_mem_rule: {
      andI_rReg_memNode *node = new andI_rReg_memNode();
      return node;
    }
  case andI_rReg_mem_0_rule: {
      andI_rReg_mem_0Node *node = new andI_rReg_mem_0Node();
      return node;
    }
  case andI_mem_rReg_rule: {
      andI_mem_rRegNode *node = new andI_mem_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andI_mem_rReg_0_rule: {
      andI_mem_rReg_0Node *node = new andI_mem_rReg_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andI_mem_imm_rule: {
      andI_mem_immNode *node = new andI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andnI_rReg_rReg_mem_rule: {
      andnI_rReg_rReg_memNode *node = new andnI_rReg_rReg_memNode();
      return node;
    }
  case andnI_rReg_rReg_mem_0_rule: {
      andnI_rReg_rReg_mem_0Node *node = new andnI_rReg_rReg_mem_0Node();
      return node;
    }
  case andnI_rReg_rReg_rReg_rule: {
      andnI_rReg_rReg_rRegNode *node = new andnI_rReg_rReg_rRegNode();
      return node;
    }
  case andnI_rReg_rReg_rReg_0_rule: {
      andnI_rReg_rReg_rReg_0Node *node = new andnI_rReg_rReg_rReg_0Node();
      return node;
    }
  case blsiI_rReg_rReg_rule: {
      blsiI_rReg_rRegNode *node = new blsiI_rReg_rRegNode();
      return node;
    }
  case blsiI_rReg_rReg_0_rule: {
      blsiI_rReg_rReg_0Node *node = new blsiI_rReg_rReg_0Node();
      return node;
    }
  case blsiI_rReg_mem_rule: {
      blsiI_rReg_memNode *node = new blsiI_rReg_memNode();
      return node;
    }
  case blsiI_rReg_mem_0_rule: {
      blsiI_rReg_mem_0Node *node = new blsiI_rReg_mem_0Node();
      return node;
    }
  case blsmskI_rReg_mem_rule: {
      blsmskI_rReg_memNode *node = new blsmskI_rReg_memNode();
      return node;
    }
  case blsmskI_rReg_mem_0_rule: {
      blsmskI_rReg_mem_0Node *node = new blsmskI_rReg_mem_0Node();
      return node;
    }
  case blsmskI_rReg_rReg_rule: {
      blsmskI_rReg_rRegNode *node = new blsmskI_rReg_rRegNode();
      return node;
    }
  case blsmskI_rReg_rReg_0_rule: {
      blsmskI_rReg_rReg_0Node *node = new blsmskI_rReg_rReg_0Node();
      return node;
    }
  case blsrI_rReg_rReg_rule: {
      blsrI_rReg_rRegNode *node = new blsrI_rReg_rRegNode();
      return node;
    }
  case blsrI_rReg_rReg_0_rule: {
      blsrI_rReg_rReg_0Node *node = new blsrI_rReg_rReg_0Node();
      return node;
    }
  case blsrI_rReg_mem_rule: {
      blsrI_rReg_memNode *node = new blsrI_rReg_memNode();
      return node;
    }
  case blsrI_rReg_mem_0_rule: {
      blsrI_rReg_mem_0Node *node = new blsrI_rReg_mem_0Node();
      return node;
    }
  case orI_rReg_rule: {
      orI_rRegNode *node = new orI_rRegNode();
      return node;
    }
  case orI_rReg_imm_rule: {
      orI_rReg_immNode *node = new orI_rReg_immNode();
      return node;
    }
  case orI_rReg_mem_rule: {
      orI_rReg_memNode *node = new orI_rReg_memNode();
      return node;
    }
  case orI_rReg_mem_0_rule: {
      orI_rReg_mem_0Node *node = new orI_rReg_mem_0Node();
      return node;
    }
  case orI_mem_rReg_rule: {
      orI_mem_rRegNode *node = new orI_mem_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case orI_mem_rReg_0_rule: {
      orI_mem_rReg_0Node *node = new orI_mem_rReg_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case orI_mem_imm_rule: {
      orI_mem_immNode *node = new orI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorI_rReg_rule: {
      xorI_rRegNode *node = new xorI_rRegNode();
      return node;
    }
  case xorI_rReg_im1_rule: {
      xorI_rReg_im1Node *node = new xorI_rReg_im1Node();
      return node;
    }
  case xorI_rReg_imm_rule: {
      xorI_rReg_immNode *node = new xorI_rReg_immNode();
      return node;
    }
  case xorI_rReg_mem_rule: {
      xorI_rReg_memNode *node = new xorI_rReg_memNode();
      return node;
    }
  case xorI_rReg_mem_0_rule: {
      xorI_rReg_mem_0Node *node = new xorI_rReg_mem_0Node();
      return node;
    }
  case xorI_mem_rReg_rule: {
      xorI_mem_rRegNode *node = new xorI_mem_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorI_mem_rReg_0_rule: {
      xorI_mem_rReg_0Node *node = new xorI_mem_rReg_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorI_mem_imm_rule: {
      xorI_mem_immNode *node = new xorI_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andL_rReg_rule: {
      andL_rRegNode *node = new andL_rRegNode();
      return node;
    }
  case andL_rReg_imm255_rule: {
      andL_rReg_imm255Node *node = new andL_rReg_imm255Node();
      return node;
    }
  case andL_rReg_imm65535_rule: {
      andL_rReg_imm65535Node *node = new andL_rReg_imm65535Node();
      return node;
    }
  case andL_rReg_imm_rule: {
      andL_rReg_immNode *node = new andL_rReg_immNode();
      return node;
    }
  case andL_rReg_mem_rule: {
      andL_rReg_memNode *node = new andL_rReg_memNode();
      return node;
    }
  case andL_rReg_mem_0_rule: {
      andL_rReg_mem_0Node *node = new andL_rReg_mem_0Node();
      return node;
    }
  case andL_mem_rReg_rule: {
      andL_mem_rRegNode *node = new andL_mem_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andL_mem_rReg_0_rule: {
      andL_mem_rReg_0Node *node = new andL_mem_rReg_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andL_mem_imm_rule: {
      andL_mem_immNode *node = new andL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case andnL_rReg_rReg_mem_rule: {
      andnL_rReg_rReg_memNode *node = new andnL_rReg_rReg_memNode();
      return node;
    }
  case andnL_rReg_rReg_mem_0_rule: {
      andnL_rReg_rReg_mem_0Node *node = new andnL_rReg_rReg_mem_0Node();
      return node;
    }
  case andnL_rReg_rReg_rReg_rule: {
      andnL_rReg_rReg_rRegNode *node = new andnL_rReg_rReg_rRegNode();
      return node;
    }
  case andnL_rReg_rReg_rReg_0_rule: {
      andnL_rReg_rReg_rReg_0Node *node = new andnL_rReg_rReg_rReg_0Node();
      return node;
    }
  case blsiL_rReg_rReg_rule: {
      blsiL_rReg_rRegNode *node = new blsiL_rReg_rRegNode();
      return node;
    }
  case blsiL_rReg_rReg_0_rule: {
      blsiL_rReg_rReg_0Node *node = new blsiL_rReg_rReg_0Node();
      return node;
    }
  case blsiL_rReg_mem_rule: {
      blsiL_rReg_memNode *node = new blsiL_rReg_memNode();
      return node;
    }
  case blsiL_rReg_mem_0_rule: {
      blsiL_rReg_mem_0Node *node = new blsiL_rReg_mem_0Node();
      return node;
    }
  case blsmskL_rReg_mem_rule: {
      blsmskL_rReg_memNode *node = new blsmskL_rReg_memNode();
      return node;
    }
  case blsmskL_rReg_mem_0_rule: {
      blsmskL_rReg_mem_0Node *node = new blsmskL_rReg_mem_0Node();
      return node;
    }
  case blsmskL_rReg_rReg_rule: {
      blsmskL_rReg_rRegNode *node = new blsmskL_rReg_rRegNode();
      return node;
    }
  case blsmskL_rReg_rReg_0_rule: {
      blsmskL_rReg_rReg_0Node *node = new blsmskL_rReg_rReg_0Node();
      return node;
    }
  case blsrL_rReg_rReg_rule: {
      blsrL_rReg_rRegNode *node = new blsrL_rReg_rRegNode();
      return node;
    }
  case blsrL_rReg_rReg_0_rule: {
      blsrL_rReg_rReg_0Node *node = new blsrL_rReg_rReg_0Node();
      return node;
    }
  case blsrL_rReg_mem_rule: {
      blsrL_rReg_memNode *node = new blsrL_rReg_memNode();
      return node;
    }
  case blsrL_rReg_mem_0_rule: {
      blsrL_rReg_mem_0Node *node = new blsrL_rReg_mem_0Node();
      return node;
    }
  case orL_rReg_rule: {
      orL_rRegNode *node = new orL_rRegNode();
      return node;
    }
  case orL_rReg_castP2X_rule: {
      orL_rReg_castP2XNode *node = new orL_rReg_castP2XNode();
      return node;
    }
  case orL_rReg_castP2X_0_rule: {
      orL_rReg_castP2X_0Node *node = new orL_rReg_castP2X_0Node();
      return node;
    }
  case orL_rReg_imm_rule: {
      orL_rReg_immNode *node = new orL_rReg_immNode();
      return node;
    }
  case orL_rReg_mem_rule: {
      orL_rReg_memNode *node = new orL_rReg_memNode();
      return node;
    }
  case orL_rReg_mem_0_rule: {
      orL_rReg_mem_0Node *node = new orL_rReg_mem_0Node();
      return node;
    }
  case orL_mem_rReg_rule: {
      orL_mem_rRegNode *node = new orL_mem_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case orL_mem_rReg_0_rule: {
      orL_mem_rReg_0Node *node = new orL_mem_rReg_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case orL_mem_imm_rule: {
      orL_mem_immNode *node = new orL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorL_rReg_rule: {
      xorL_rRegNode *node = new xorL_rRegNode();
      return node;
    }
  case xorL_rReg_im1_rule: {
      xorL_rReg_im1Node *node = new xorL_rReg_im1Node();
      return node;
    }
  case xorL_rReg_imm_rule: {
      xorL_rReg_immNode *node = new xorL_rReg_immNode();
      return node;
    }
  case xorL_rReg_mem_rule: {
      xorL_rReg_memNode *node = new xorL_rReg_memNode();
      return node;
    }
  case xorL_rReg_mem_0_rule: {
      xorL_rReg_mem_0Node *node = new xorL_rReg_mem_0Node();
      return node;
    }
  case xorL_mem_rReg_rule: {
      xorL_mem_rRegNode *node = new xorL_mem_rRegNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorL_mem_rReg_0_rule: {
      xorL_mem_rReg_0Node *node = new xorL_mem_rReg_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case xorL_mem_imm_rule: {
      xorL_mem_immNode *node = new xorL_mem_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case convI2B_rule: {
      convI2BNode *node = new convI2BNode();
      return node;
    }
  case convP2B_rule: {
      convP2BNode *node = new convP2BNode();
      return node;
    }
  case cmpLTMask_rule: {
      cmpLTMaskNode *node = new cmpLTMaskNode();
      return node;
    }
  case cmpLTMask0_rule: {
      cmpLTMask0Node *node = new cmpLTMask0Node();
      return node;
    }
  case cadd_cmpLTMask_rule: {
      cadd_cmpLTMaskNode *node = new cadd_cmpLTMaskNode();
      return node;
    }
  case cadd_cmpLTMask_1_rule: {
      cadd_cmpLTMask_1Node *node = new cadd_cmpLTMask_1Node();
      return node;
    }
  case cadd_cmpLTMask_0_rule: {
      cadd_cmpLTMask_0Node *node = new cadd_cmpLTMask_0Node();
      return node;
    }
  case cadd_cmpLTMask_2_rule: {
      cadd_cmpLTMask_2Node *node = new cadd_cmpLTMask_2Node();
      return node;
    }
  case and_cmpLTMask_rule: {
      and_cmpLTMaskNode *node = new and_cmpLTMaskNode();
      return node;
    }
  case and_cmpLTMask_0_rule: {
      and_cmpLTMask_0Node *node = new and_cmpLTMask_0Node();
      return node;
    }
  case cmpF_cc_reg_rule: {
      cmpF_cc_regNode *node = new cmpF_cc_regNode();
      return node;
    }
  case cmpF_cc_reg_CF_rule: {
      cmpF_cc_reg_CFNode *node = new cmpF_cc_reg_CFNode();
      return node;
    }
  case cmpF_cc_mem_rule: {
      cmpF_cc_memNode *node = new cmpF_cc_memNode();
      return node;
    }
  case cmpF_cc_memCF_rule: {
      cmpF_cc_memCFNode *node = new cmpF_cc_memCFNode();
      return node;
    }
  case cmpF_cc_imm_rule: {
      cmpF_cc_immNode *node = new cmpF_cc_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cmpF_cc_immCF_rule: {
      cmpF_cc_immCFNode *node = new cmpF_cc_immCFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cmpD_cc_reg_rule: {
      cmpD_cc_regNode *node = new cmpD_cc_regNode();
      return node;
    }
  case cmpD_cc_reg_CF_rule: {
      cmpD_cc_reg_CFNode *node = new cmpD_cc_reg_CFNode();
      return node;
    }
  case cmpD_cc_mem_rule: {
      cmpD_cc_memNode *node = new cmpD_cc_memNode();
      return node;
    }
  case cmpD_cc_memCF_rule: {
      cmpD_cc_memCFNode *node = new cmpD_cc_memCFNode();
      return node;
    }
  case cmpD_cc_imm_rule: {
      cmpD_cc_immNode *node = new cmpD_cc_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cmpD_cc_immCF_rule: {
      cmpD_cc_immCFNode *node = new cmpD_cc_immCFNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cmpF_reg_rule: {
      cmpF_regNode *node = new cmpF_regNode();
      return node;
    }
  case cmpF_mem_rule: {
      cmpF_memNode *node = new cmpF_memNode();
      return node;
    }
  case cmpF_imm_rule: {
      cmpF_immNode *node = new cmpF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case cmpD_reg_rule: {
      cmpD_regNode *node = new cmpD_regNode();
      return node;
    }
  case cmpD_mem_rule: {
      cmpD_memNode *node = new cmpD_memNode();
      return node;
    }
  case cmpD_imm_rule: {
      cmpD_immNode *node = new cmpD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case roundFloat_nop_rule: {
      roundFloat_nopNode *node = new roundFloat_nopNode();
      return node;
    }
  case roundDouble_nop_rule: {
      roundDouble_nopNode *node = new roundDouble_nopNode();
      return node;
    }
  case convF2D_reg_reg_rule: {
      convF2D_reg_regNode *node = new convF2D_reg_regNode();
      return node;
    }
  case convF2D_reg_mem_rule: {
      convF2D_reg_memNode *node = new convF2D_reg_memNode();
      return node;
    }
  case convD2F_reg_reg_rule: {
      convD2F_reg_regNode *node = new convD2F_reg_regNode();
      return node;
    }
  case convD2F_reg_mem_rule: {
      convD2F_reg_memNode *node = new convD2F_reg_memNode();
      return node;
    }
  case convF2I_reg_reg_rule: {
      convF2I_reg_regNode *node = new convF2I_reg_regNode();
      return node;
    }
  case convF2L_reg_reg_rule: {
      convF2L_reg_regNode *node = new convF2L_reg_regNode();
      return node;
    }
  case convD2I_reg_reg_rule: {
      convD2I_reg_regNode *node = new convD2I_reg_regNode();
      return node;
    }
  case convD2L_reg_reg_rule: {
      convD2L_reg_regNode *node = new convD2L_reg_regNode();
      return node;
    }
  case convI2F_reg_reg_rule: {
      convI2F_reg_regNode *node = new convI2F_reg_regNode();
      return node;
    }
  case convI2F_reg_mem_rule: {
      convI2F_reg_memNode *node = new convI2F_reg_memNode();
      return node;
    }
  case convI2D_reg_reg_rule: {
      convI2D_reg_regNode *node = new convI2D_reg_regNode();
      return node;
    }
  case convI2D_reg_mem_rule: {
      convI2D_reg_memNode *node = new convI2D_reg_memNode();
      return node;
    }
  case convXI2F_reg_rule: {
      convXI2F_regNode *node = new convXI2F_regNode();
      return node;
    }
  case convXI2D_reg_rule: {
      convXI2D_regNode *node = new convXI2D_regNode();
      return node;
    }
  case convL2F_reg_reg_rule: {
      convL2F_reg_regNode *node = new convL2F_reg_regNode();
      return node;
    }
  case convL2F_reg_mem_rule: {
      convL2F_reg_memNode *node = new convL2F_reg_memNode();
      return node;
    }
  case convL2D_reg_reg_rule: {
      convL2D_reg_regNode *node = new convL2D_reg_regNode();
      return node;
    }
  case convL2D_reg_mem_rule: {
      convL2D_reg_memNode *node = new convL2D_reg_memNode();
      return node;
    }
  case convI2L_reg_reg_rule: {
      convI2L_reg_regNode *node = new convI2L_reg_regNode();
      return node;
    }
  case convI2L_reg_reg_zex_rule: {
      convI2L_reg_reg_zexNode *node = new convI2L_reg_reg_zexNode();
      return node;
    }
  case convI2L_reg_mem_zex_rule: {
      convI2L_reg_mem_zexNode *node = new convI2L_reg_mem_zexNode();
      return node;
    }
  case zerox_long_reg_reg_rule: {
      zerox_long_reg_regNode *node = new zerox_long_reg_regNode();
      return node;
    }
  case convL2I_reg_reg_rule: {
      convL2I_reg_regNode *node = new convL2I_reg_regNode();
      return node;
    }
  case MoveF2I_stack_reg_rule: {
      MoveF2I_stack_regNode *node = new MoveF2I_stack_regNode();
      return node;
    }
  case MoveI2F_stack_reg_rule: {
      MoveI2F_stack_regNode *node = new MoveI2F_stack_regNode();
      return node;
    }
  case MoveD2L_stack_reg_rule: {
      MoveD2L_stack_regNode *node = new MoveD2L_stack_regNode();
      return node;
    }
  case MoveL2D_stack_reg_partial_rule: {
      MoveL2D_stack_reg_partialNode *node = new MoveL2D_stack_reg_partialNode();
      return node;
    }
  case MoveL2D_stack_reg_rule: {
      MoveL2D_stack_regNode *node = new MoveL2D_stack_regNode();
      return node;
    }
  case MoveF2I_reg_stack_rule: {
      MoveF2I_reg_stackNode *node = new MoveF2I_reg_stackNode();
      return node;
    }
  case MoveI2F_reg_stack_rule: {
      MoveI2F_reg_stackNode *node = new MoveI2F_reg_stackNode();
      return node;
    }
  case MoveD2L_reg_stack_rule: {
      MoveD2L_reg_stackNode *node = new MoveD2L_reg_stackNode();
      return node;
    }
  case MoveL2D_reg_stack_rule: {
      MoveL2D_reg_stackNode *node = new MoveL2D_reg_stackNode();
      return node;
    }
  case MoveF2I_reg_reg_rule: {
      MoveF2I_reg_regNode *node = new MoveF2I_reg_regNode();
      return node;
    }
  case MoveD2L_reg_reg_rule: {
      MoveD2L_reg_regNode *node = new MoveD2L_reg_regNode();
      return node;
    }
  case MoveI2F_reg_reg_rule: {
      MoveI2F_reg_regNode *node = new MoveI2F_reg_regNode();
      return node;
    }
  case MoveL2D_reg_reg_rule: {
      MoveL2D_reg_regNode *node = new MoveL2D_reg_regNode();
      return node;
    }
  case rep_stos_rule: {
      rep_stosNode *node = new rep_stosNode();
      return node;
    }
  case rep_stos_large_rule: {
      rep_stos_largeNode *node = new rep_stos_largeNode();
      return node;
    }
  case string_compareL_rule: {
      string_compareLNode *node = new string_compareLNode();
      node->set_opnd_array(5, MachOperGenerator(REGD));
      return node;
    }
  case string_compareU_rule: {
      string_compareUNode *node = new string_compareUNode();
      node->set_opnd_array(5, MachOperGenerator(REGD));
      return node;
    }
  case string_compareLU_rule: {
      string_compareLUNode *node = new string_compareLUNode();
      node->set_opnd_array(5, MachOperGenerator(REGD));
      return node;
    }
  case string_compareUL_rule: {
      string_compareULNode *node = new string_compareULNode();
      node->set_opnd_array(5, MachOperGenerator(REGD));
      return node;
    }
  case string_indexof_conL_rule: {
      string_indexof_conLNode *node = new string_indexof_conLNode();
      node->set_opnd_array(5, MachOperGenerator(REGD));
      return node;
    }
  case string_indexof_conU_rule: {
      string_indexof_conUNode *node = new string_indexof_conUNode();
      node->set_opnd_array(5, MachOperGenerator(REGD));
      return node;
    }
  case string_indexof_conUL_rule: {
      string_indexof_conULNode *node = new string_indexof_conULNode();
      node->set_opnd_array(5, MachOperGenerator(REGD));
      return node;
    }
  case string_indexofL_rule: {
      string_indexofLNode *node = new string_indexofLNode();
      node->set_opnd_array(5, MachOperGenerator(REGD));
      return node;
    }
  case string_indexofU_rule: {
      string_indexofUNode *node = new string_indexofUNode();
      node->set_opnd_array(5, MachOperGenerator(REGD));
      return node;
    }
  case string_indexofUL_rule: {
      string_indexofULNode *node = new string_indexofULNode();
      node->set_opnd_array(5, MachOperGenerator(REGD));
      return node;
    }
  case string_indexofU_char_rule: {
      string_indexofU_charNode *node = new string_indexofU_charNode();
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->set_opnd_array(5, MachOperGenerator(REGD));
      node->set_opnd_array(6, MachOperGenerator(REGD));
      node->set_opnd_array(7, MachOperGenerator(RCX_REGI));
      return node;
    }
  case string_equals_rule: {
      string_equalsNode *node = new string_equalsNode();
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->set_opnd_array(5, MachOperGenerator(REGD));
      return node;
    }
  case array_equalsB_rule: {
      array_equalsBNode *node = new array_equalsBNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      return node;
    }
  case array_equalsC_rule: {
      array_equalsCNode *node = new array_equalsCNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      return node;
    }
  case has_negatives_rule: {
      has_negativesNode *node = new has_negativesNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      return node;
    }
  case string_compress_rule: {
      string_compressNode *node = new string_compressNode();
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->set_opnd_array(5, MachOperGenerator(REGD));
      node->set_opnd_array(6, MachOperGenerator(REGD));
      node->set_opnd_array(7, MachOperGenerator(REGD));
      return node;
    }
  case string_inflate_rule: {
      string_inflateNode *node = new string_inflateNode();
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->set_opnd_array(5, MachOperGenerator(RCX_REGI));
      return node;
    }
  case encode_iso_array_rule: {
      encode_iso_arrayNode *node = new encode_iso_arrayNode();
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->set_opnd_array(5, MachOperGenerator(REGD));
      node->set_opnd_array(6, MachOperGenerator(REGD));
      node->set_opnd_array(7, MachOperGenerator(REGD));
      return node;
    }
  case overflowAddI_rReg_rule: {
      overflowAddI_rRegNode *node = new overflowAddI_rRegNode();
      return node;
    }
  case overflowAddI_rReg_imm_rule: {
      overflowAddI_rReg_immNode *node = new overflowAddI_rReg_immNode();
      return node;
    }
  case overflowAddL_rReg_rule: {
      overflowAddL_rRegNode *node = new overflowAddL_rRegNode();
      return node;
    }
  case overflowAddL_rReg_imm_rule: {
      overflowAddL_rReg_immNode *node = new overflowAddL_rReg_immNode();
      return node;
    }
  case overflowSubI_rReg_rule: {
      overflowSubI_rRegNode *node = new overflowSubI_rRegNode();
      return node;
    }
  case overflowSubI_rReg_imm_rule: {
      overflowSubI_rReg_immNode *node = new overflowSubI_rReg_immNode();
      return node;
    }
  case overflowSubL_rReg_rule: {
      overflowSubL_rRegNode *node = new overflowSubL_rRegNode();
      return node;
    }
  case overflowSubL_rReg_imm_rule: {
      overflowSubL_rReg_immNode *node = new overflowSubL_rReg_immNode();
      return node;
    }
  case overflowNegI_rReg_rule: {
      overflowNegI_rRegNode *node = new overflowNegI_rRegNode();
      return node;
    }
  case overflowNegL_rReg_rule: {
      overflowNegL_rRegNode *node = new overflowNegL_rRegNode();
      return node;
    }
  case overflowMulI_rReg_rule: {
      overflowMulI_rRegNode *node = new overflowMulI_rRegNode();
      return node;
    }
  case overflowMulI_rReg_imm_rule: {
      overflowMulI_rReg_immNode *node = new overflowMulI_rReg_immNode();
      node->set_opnd_array(3, MachOperGenerator(RREGI));
      return node;
    }
  case overflowMulL_rReg_rule: {
      overflowMulL_rRegNode *node = new overflowMulL_rRegNode();
      return node;
    }
  case overflowMulL_rReg_imm_rule: {
      overflowMulL_rReg_immNode *node = new overflowMulL_rReg_immNode();
      node->set_opnd_array(3, MachOperGenerator(RREGL));
      return node;
    }
  case compI_rReg_rule: {
      compI_rRegNode *node = new compI_rRegNode();
      return node;
    }
  case compI_rReg_imm_rule: {
      compI_rReg_immNode *node = new compI_rReg_immNode();
      return node;
    }
  case compI_rReg_mem_rule: {
      compI_rReg_memNode *node = new compI_rReg_memNode();
      return node;
    }
  case testI_reg_rule: {
      testI_regNode *node = new testI_regNode();
      return node;
    }
  case testI_reg_imm_rule: {
      testI_reg_immNode *node = new testI_reg_immNode();
      return node;
    }
  case testI_reg_mem_rule: {
      testI_reg_memNode *node = new testI_reg_memNode();
      return node;
    }
  case testI_reg_mem_0_rule: {
      testI_reg_mem_0Node *node = new testI_reg_mem_0Node();
      return node;
    }
  case compU_rReg_rule: {
      compU_rRegNode *node = new compU_rRegNode();
      return node;
    }
  case compU_rReg_imm_rule: {
      compU_rReg_immNode *node = new compU_rReg_immNode();
      return node;
    }
  case compU_rReg_mem_rule: {
      compU_rReg_memNode *node = new compU_rReg_memNode();
      return node;
    }
  case testU_reg_rule: {
      testU_regNode *node = new testU_regNode();
      return node;
    }
  case compP_rReg_rule: {
      compP_rRegNode *node = new compP_rRegNode();
      return node;
    }
  case compP_rReg_mem_rule: {
      compP_rReg_memNode *node = new compP_rReg_memNode();
      return node;
    }
  case compP_mem_rReg_rule: {
      compP_mem_rRegNode *node = new compP_mem_rRegNode();
      return node;
    }
  case testP_reg_rule: {
      testP_regNode *node = new testP_regNode();
      return node;
    }
  case testP_mem_rule: {
      testP_memNode *node = new testP_memNode();
      return node;
    }
  case testP_mem_reg0_rule: {
      testP_mem_reg0Node *node = new testP_mem_reg0Node();
      return node;
    }
  case compN_rReg_rule: {
      compN_rRegNode *node = new compN_rRegNode();
      return node;
    }
  case compN_rReg_mem_rule: {
      compN_rReg_memNode *node = new compN_rReg_memNode();
      return node;
    }
  case compN_rReg_imm_rule: {
      compN_rReg_immNode *node = new compN_rReg_immNode();
      return node;
    }
  case compN_mem_imm_rule: {
      compN_mem_immNode *node = new compN_mem_immNode();
      return node;
    }
  case compN_rReg_imm_klass_rule: {
      compN_rReg_imm_klassNode *node = new compN_rReg_imm_klassNode();
      return node;
    }
  case compN_mem_imm_klass_rule: {
      compN_mem_imm_klassNode *node = new compN_mem_imm_klassNode();
      return node;
    }
  case testN_reg_rule: {
      testN_regNode *node = new testN_regNode();
      return node;
    }
  case testN_mem_rule: {
      testN_memNode *node = new testN_memNode();
      return node;
    }
  case testN_mem_reg0_rule: {
      testN_mem_reg0Node *node = new testN_mem_reg0Node();
      return node;
    }
  case compL_rReg_rule: {
      compL_rRegNode *node = new compL_rRegNode();
      return node;
    }
  case compL_rReg_imm_rule: {
      compL_rReg_immNode *node = new compL_rReg_immNode();
      return node;
    }
  case compL_rReg_mem_rule: {
      compL_rReg_memNode *node = new compL_rReg_memNode();
      return node;
    }
  case testL_reg_rule: {
      testL_regNode *node = new testL_regNode();
      return node;
    }
  case testL_reg_imm_rule: {
      testL_reg_immNode *node = new testL_reg_immNode();
      return node;
    }
  case testL_reg_mem_rule: {
      testL_reg_memNode *node = new testL_reg_memNode();
      return node;
    }
  case testL_reg_mem_0_rule: {
      testL_reg_mem_0Node *node = new testL_reg_mem_0Node();
      return node;
    }
  case cmpL3_reg_reg_rule: {
      cmpL3_reg_regNode *node = new cmpL3_reg_regNode();
      return node;
    }
  case minI_rReg_rule: {
      minI_rRegNode *node = new minI_rRegNode();
      return node;
    }
  case maxI_rReg_rule: {
      maxI_rRegNode *node = new maxI_rRegNode();
      return node;
    }
  case jmpDir_rule: {
      jmpDirNode *node = new jmpDirNode();
      node->set_opnd_array(1, MachOperGenerator(LABEL));
      return node;
    }
  case jmpCon_rule: {
      jmpConNode *node = new jmpConNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpLoopEnd_rule: {
      jmpLoopEndNode *node = new jmpLoopEndNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpLoopEndU_rule: {
      jmpLoopEndUNode *node = new jmpLoopEndUNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpLoopEndUCF_rule: {
      jmpLoopEndUCFNode *node = new jmpLoopEndUCFNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpLoopEnd_and_restoreMask_rule: {
      jmpLoopEnd_and_restoreMaskNode *node = new jmpLoopEnd_and_restoreMaskNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpLoopEndU_and_restoreMask_rule: {
      jmpLoopEndU_and_restoreMaskNode *node = new jmpLoopEndU_and_restoreMaskNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpLoopEndUCF_and_restoreMask_rule: {
      jmpLoopEndUCF_and_restoreMaskNode *node = new jmpLoopEndUCF_and_restoreMaskNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConU_rule: {
      jmpConUNode *node = new jmpConUNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConUCF_rule: {
      jmpConUCFNode *node = new jmpConUCFNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConUCF2_rule: {
      jmpConUCF2Node *node = new jmpConUCF2Node();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case partialSubtypeCheck_rule: {
      partialSubtypeCheckNode *node = new partialSubtypeCheckNode();
      return node;
    }
  case partialSubtypeCheck_vs_Zero_rule: {
      partialSubtypeCheck_vs_ZeroNode *node = new partialSubtypeCheck_vs_ZeroNode();
      return node;
    }
  case jmpDir_short_rule: {
      jmpDir_shortNode *node = new jmpDir_shortNode();
      node->set_opnd_array(1, MachOperGenerator(LABEL));
      return node;
    }
  case jmpCon_short_rule: {
      jmpCon_shortNode *node = new jmpCon_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpLoopEnd_short_rule: {
      jmpLoopEnd_shortNode *node = new jmpLoopEnd_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpLoopEndU_short_rule: {
      jmpLoopEndU_shortNode *node = new jmpLoopEndU_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpLoopEndUCF_short_rule: {
      jmpLoopEndUCF_shortNode *node = new jmpLoopEndUCF_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConU_short_rule: {
      jmpConU_shortNode *node = new jmpConU_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConUCF_short_rule: {
      jmpConUCF_shortNode *node = new jmpConUCF_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case jmpConUCF2_short_rule: {
      jmpConUCF2_shortNode *node = new jmpConUCF2_shortNode();
      node->set_opnd_array(3, MachOperGenerator(LABEL));
      node->_prob = _leaf->as_If()->_prob;
      node->_fcnt = _leaf->as_If()->_fcnt;
      return node;
    }
  case cmpFastLockRTM_rule: {
      cmpFastLockRTMNode *node = new cmpFastLockRTMNode();
      node->set_opnd_array(3, MachOperGenerator(RAX_REGI));
      node->set_opnd_array(4, MachOperGenerator(RDX_REGI));
      node->set_opnd_array(5, MachOperGenerator(RREGI));
      node->set_opnd_array(6, MachOperGenerator(RREGI));
      node->_counters = _leaf->as_FastLock()->counters();
      node->_rtm_counters = _leaf->as_FastLock()->rtm_counters();
      node->_stack_rtm_counters = _leaf->as_FastLock()->stack_rtm_counters();
      return node;
    }
  case cmpFastLock_rule: {
      cmpFastLockNode *node = new cmpFastLockNode();
      node->set_opnd_array(3, MachOperGenerator(RAX_REGI));
      node->set_opnd_array(4, MachOperGenerator(RREGP));
      node->_counters = _leaf->as_FastLock()->counters();
      node->_rtm_counters = _leaf->as_FastLock()->rtm_counters();
      node->_stack_rtm_counters = _leaf->as_FastLock()->stack_rtm_counters();
      return node;
    }
  case cmpFastUnlock_rule: {
      cmpFastUnlockNode *node = new cmpFastUnlockNode();
      node->set_opnd_array(3, MachOperGenerator(RREGP));
      return node;
    }
  case safePoint_poll_rule: {
      safePoint_pollNode *node = new safePoint_pollNode();
      node->set_opnd_array(1, MachOperGenerator(RFLAGSREG));
      return node;
    }
  case safePoint_poll_far_rule: {
      safePoint_poll_farNode *node = new safePoint_poll_farNode();
      return node;
    }
  case CallStaticJavaDirect_rule: {
      CallStaticJavaDirectNode *node = new CallStaticJavaDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallDynamicJavaDirect_rule: {
      CallDynamicJavaDirectNode *node = new CallDynamicJavaDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallRuntimeDirect_rule: {
      CallRuntimeDirectNode *node = new CallRuntimeDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallLeafDirect_rule: {
      CallLeafDirectNode *node = new CallLeafDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case CallLeafNoFPDirect_rule: {
      CallLeafNoFPDirectNode *node = new CallLeafNoFPDirectNode();
      node->set_opnd_array(1, MachOperGenerator(METHOD));
      return node;
    }
  case Ret_rule: {
      RetNode *node = new RetNode();
      return node;
    }
  case TailCalljmpInd_rule: {
      TailCalljmpIndNode *node = new TailCalljmpIndNode();
      return node;
    }
  case tailjmpInd_rule: {
      tailjmpIndNode *node = new tailjmpIndNode();
      return node;
    }
  case CreateException_rule: {
      CreateExceptionNode *node = new CreateExceptionNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case RethrowException_rule: {
      RethrowExceptionNode *node = new RethrowExceptionNode();
      return node;
    }
  case tlsLoadP_rule: {
      tlsLoadPNode *node = new tlsLoadPNode();
      return node;
    }
  case ShouldNotReachHere_rule: {
      ShouldNotReachHereNode *node = new ShouldNotReachHereNode();
      return node;
    }
  case setMask_rule: {
      setMaskNode *node = new setMaskNode();
      node->set_opnd_array(2, MachOperGenerator(RREGI));
      return node;
    }
  case addF_reg_rule: {
      addF_regNode *node = new addF_regNode();
      return node;
    }
  case addF_mem_rule: {
      addF_memNode *node = new addF_memNode();
      return node;
    }
  case addF_mem_0_rule: {
      addF_mem_0Node *node = new addF_mem_0Node();
      return node;
    }
  case addF_imm_rule: {
      addF_immNode *node = new addF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addF_reg_reg_rule: {
      addF_reg_regNode *node = new addF_reg_regNode();
      return node;
    }
  case addF_reg_mem_rule: {
      addF_reg_memNode *node = new addF_reg_memNode();
      return node;
    }
  case addF_reg_mem_0_rule: {
      addF_reg_mem_0Node *node = new addF_reg_mem_0Node();
      return node;
    }
  case addF_reg_imm_rule: {
      addF_reg_immNode *node = new addF_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addD_reg_rule: {
      addD_regNode *node = new addD_regNode();
      return node;
    }
  case addD_mem_rule: {
      addD_memNode *node = new addD_memNode();
      return node;
    }
  case addD_mem_0_rule: {
      addD_mem_0Node *node = new addD_mem_0Node();
      return node;
    }
  case addD_imm_rule: {
      addD_immNode *node = new addD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case addD_reg_reg_rule: {
      addD_reg_regNode *node = new addD_reg_regNode();
      return node;
    }
  case addD_reg_mem_rule: {
      addD_reg_memNode *node = new addD_reg_memNode();
      return node;
    }
  case addD_reg_mem_0_rule: {
      addD_reg_mem_0Node *node = new addD_reg_mem_0Node();
      return node;
    }
  case addD_reg_imm_rule: {
      addD_reg_immNode *node = new addD_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subF_reg_rule: {
      subF_regNode *node = new subF_regNode();
      return node;
    }
  case subF_mem_rule: {
      subF_memNode *node = new subF_memNode();
      return node;
    }
  case subF_imm_rule: {
      subF_immNode *node = new subF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subF_reg_reg_rule: {
      subF_reg_regNode *node = new subF_reg_regNode();
      return node;
    }
  case subF_reg_mem_rule: {
      subF_reg_memNode *node = new subF_reg_memNode();
      return node;
    }
  case subF_reg_imm_rule: {
      subF_reg_immNode *node = new subF_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subD_reg_rule: {
      subD_regNode *node = new subD_regNode();
      return node;
    }
  case subD_mem_rule: {
      subD_memNode *node = new subD_memNode();
      return node;
    }
  case subD_imm_rule: {
      subD_immNode *node = new subD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case subD_reg_reg_rule: {
      subD_reg_regNode *node = new subD_reg_regNode();
      return node;
    }
  case subD_reg_mem_rule: {
      subD_reg_memNode *node = new subD_reg_memNode();
      return node;
    }
  case subD_reg_imm_rule: {
      subD_reg_immNode *node = new subD_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mulF_reg_rule: {
      mulF_regNode *node = new mulF_regNode();
      return node;
    }
  case mulF_mem_rule: {
      mulF_memNode *node = new mulF_memNode();
      return node;
    }
  case mulF_mem_0_rule: {
      mulF_mem_0Node *node = new mulF_mem_0Node();
      return node;
    }
  case mulF_imm_rule: {
      mulF_immNode *node = new mulF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mulF_reg_reg_rule: {
      mulF_reg_regNode *node = new mulF_reg_regNode();
      return node;
    }
  case mulF_reg_mem_rule: {
      mulF_reg_memNode *node = new mulF_reg_memNode();
      return node;
    }
  case mulF_reg_mem_0_rule: {
      mulF_reg_mem_0Node *node = new mulF_reg_mem_0Node();
      return node;
    }
  case mulF_reg_imm_rule: {
      mulF_reg_immNode *node = new mulF_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mulD_reg_rule: {
      mulD_regNode *node = new mulD_regNode();
      return node;
    }
  case mulD_mem_rule: {
      mulD_memNode *node = new mulD_memNode();
      return node;
    }
  case mulD_mem_0_rule: {
      mulD_mem_0Node *node = new mulD_mem_0Node();
      return node;
    }
  case mulD_imm_rule: {
      mulD_immNode *node = new mulD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case mulD_reg_reg_rule: {
      mulD_reg_regNode *node = new mulD_reg_regNode();
      return node;
    }
  case mulD_reg_mem_rule: {
      mulD_reg_memNode *node = new mulD_reg_memNode();
      return node;
    }
  case mulD_reg_mem_0_rule: {
      mulD_reg_mem_0Node *node = new mulD_reg_mem_0Node();
      return node;
    }
  case mulD_reg_imm_rule: {
      mulD_reg_immNode *node = new mulD_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case divF_reg_rule: {
      divF_regNode *node = new divF_regNode();
      return node;
    }
  case divF_mem_rule: {
      divF_memNode *node = new divF_memNode();
      return node;
    }
  case divF_imm_rule: {
      divF_immNode *node = new divF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case divF_reg_reg_rule: {
      divF_reg_regNode *node = new divF_reg_regNode();
      return node;
    }
  case divF_reg_mem_rule: {
      divF_reg_memNode *node = new divF_reg_memNode();
      return node;
    }
  case divF_reg_imm_rule: {
      divF_reg_immNode *node = new divF_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case divD_reg_rule: {
      divD_regNode *node = new divD_regNode();
      return node;
    }
  case divD_mem_rule: {
      divD_memNode *node = new divD_memNode();
      return node;
    }
  case divD_imm_rule: {
      divD_immNode *node = new divD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case divD_reg_reg_rule: {
      divD_reg_regNode *node = new divD_reg_regNode();
      return node;
    }
  case divD_reg_mem_rule: {
      divD_reg_memNode *node = new divD_reg_memNode();
      return node;
    }
  case divD_reg_imm_rule: {
      divD_reg_immNode *node = new divD_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case absF_reg_rule: {
      absF_regNode *node = new absF_regNode();
      return node;
    }
  case absF_reg_reg_rule: {
      absF_reg_regNode *node = new absF_reg_regNode();
      return node;
    }
  case absF_reg_reg_evex_rule: {
      absF_reg_reg_evexNode *node = new absF_reg_reg_evexNode();
      return node;
    }
  case absF_reg_reg_evex_special_rule: {
      absF_reg_reg_evex_specialNode *node = new absF_reg_reg_evex_specialNode();
      node->set_opnd_array(2, MachOperGenerator(REGF));
      return node;
    }
  case absD_reg_rule: {
      absD_regNode *node = new absD_regNode();
      return node;
    }
  case absD_reg_reg_rule: {
      absD_reg_regNode *node = new absD_reg_regNode();
      return node;
    }
  case absD_reg_reg_evex_rule: {
      absD_reg_reg_evexNode *node = new absD_reg_reg_evexNode();
      return node;
    }
  case absD_reg_reg_evex_special_rule: {
      absD_reg_reg_evex_specialNode *node = new absD_reg_reg_evex_specialNode();
      node->set_opnd_array(2, MachOperGenerator(REGD));
      return node;
    }
  case negF_reg_rule: {
      negF_regNode *node = new negF_regNode();
      return node;
    }
  case negF_reg_reg_rule: {
      negF_reg_regNode *node = new negF_reg_regNode();
      return node;
    }
  case negD_reg_rule: {
      negD_regNode *node = new negD_regNode();
      return node;
    }
  case negD_reg_reg_rule: {
      negD_reg_regNode *node = new negD_reg_regNode();
      return node;
    }
  case sqrtF_reg_rule: {
      sqrtF_regNode *node = new sqrtF_regNode();
      return node;
    }
  case sqrtF_mem_rule: {
      sqrtF_memNode *node = new sqrtF_memNode();
      return node;
    }
  case sqrtF_imm_rule: {
      sqrtF_immNode *node = new sqrtF_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case sqrtD_reg_rule: {
      sqrtD_regNode *node = new sqrtD_regNode();
      return node;
    }
  case sqrtD_mem_rule: {
      sqrtD_memNode *node = new sqrtD_memNode();
      return node;
    }
  case sqrtD_imm_rule: {
      sqrtD_immNode *node = new sqrtD_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case onspinwait_rule: {
      onspinwaitNode *node = new onspinwaitNode();
      return node;
    }
  case fmaD_reg_rule: {
      fmaD_regNode *node = new fmaD_regNode();
      return node;
    }
  case fmaF_reg_rule: {
      fmaF_regNode *node = new fmaF_regNode();
      return node;
    }
  case loadV4_rule: {
      loadV4Node *node = new loadV4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV8_rule: {
      loadV8Node *node = new loadV8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV16_rule: {
      loadV16Node *node = new loadV16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV32_rule: {
      loadV32Node *node = new loadV32Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV64_dword_rule: {
      loadV64_dwordNode *node = new loadV64_dwordNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case loadV64_qword_rule: {
      loadV64_qwordNode *node = new loadV64_qwordNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV4_rule: {
      storeV4Node *node = new storeV4Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV8_rule: {
      storeV8Node *node = new storeV8Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV16_rule: {
      storeV16Node *node = new storeV16Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV32_rule: {
      storeV32Node *node = new storeV32Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV64_dword_rule: {
      storeV64_dwordNode *node = new storeV64_dwordNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case storeV64_qword_rule: {
      storeV64_qwordNode *node = new storeV64_qwordNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4B_mem_rule: {
      Repl4B_memNode *node = new Repl4B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8B_mem_rule: {
      Repl8B_memNode *node = new Repl8B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16B_rule: {
      Repl16BNode *node = new Repl16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16B_mem_rule: {
      Repl16B_memNode *node = new Repl16B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl32B_rule: {
      Repl32BNode *node = new Repl32BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl32B_mem_rule: {
      Repl32B_memNode *node = new Repl32B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16B_imm_rule: {
      Repl16B_immNode *node = new Repl16B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl32B_imm_rule: {
      Repl32B_immNode *node = new Repl32B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4S_rule: {
      Repl4SNode *node = new Repl4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4S_mem_rule: {
      Repl4S_memNode *node = new Repl4S_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8S_rule: {
      Repl8SNode *node = new Repl8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8S_mem_rule: {
      Repl8S_memNode *node = new Repl8S_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8S_imm_rule: {
      Repl8S_immNode *node = new Repl8S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16S_rule: {
      Repl16SNode *node = new Repl16SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16S_mem_rule: {
      Repl16S_memNode *node = new Repl16S_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16S_imm_rule: {
      Repl16S_immNode *node = new Repl16S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4I_rule: {
      Repl4INode *node = new Repl4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4I_mem_rule: {
      Repl4I_memNode *node = new Repl4I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8I_rule: {
      Repl8INode *node = new Repl8INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8I_mem_rule: {
      Repl8I_memNode *node = new Repl8I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4I_imm_rule: {
      Repl4I_immNode *node = new Repl4I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8I_imm_rule: {
      Repl8I_immNode *node = new Repl8I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2L_mem_rule: {
      Repl2L_memNode *node = new Repl2L_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4L_rule: {
      Repl4LNode *node = new Repl4LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4L_imm_rule: {
      Repl4L_immNode *node = new Repl4L_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4L_mem_rule: {
      Repl4L_memNode *node = new Repl4L_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2F_mem_rule: {
      Repl2F_memNode *node = new Repl2F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4F_mem_rule: {
      Repl4F_memNode *node = new Repl4F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8F_rule: {
      Repl8FNode *node = new Repl8FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8F_mem_rule: {
      Repl8F_memNode *node = new Repl8F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2F_zero_rule: {
      Repl2F_zeroNode *node = new Repl2F_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4F_zero_rule: {
      Repl4F_zeroNode *node = new Repl4F_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8F_zero_rule: {
      Repl8F_zeroNode *node = new Repl8F_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2D_mem_rule: {
      Repl2D_memNode *node = new Repl2D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4D_rule: {
      Repl4DNode *node = new Repl4DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4D_mem_rule: {
      Repl4D_memNode *node = new Repl4D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2D_zero_rule: {
      Repl2D_zeroNode *node = new Repl2D_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4D_zero_rule: {
      Repl4D_zeroNode *node = new Repl4D_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4B_rule: {
      Repl4BNode *node = new Repl4BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8B_rule: {
      Repl8BNode *node = new Repl8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4B_imm_rule: {
      Repl4B_immNode *node = new Repl4B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8B_imm_rule: {
      Repl8B_immNode *node = new Repl8B_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4B_zero_rule: {
      Repl4B_zeroNode *node = new Repl4B_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8B_zero_rule: {
      Repl8B_zeroNode *node = new Repl8B_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16B_zero_rule: {
      Repl16B_zeroNode *node = new Repl16B_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl32B_zero_rule: {
      Repl32B_zeroNode *node = new Repl32B_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2S_rule: {
      Repl2SNode *node = new Repl2SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2S_imm_rule: {
      Repl2S_immNode *node = new Repl2S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4S_imm_rule: {
      Repl4S_immNode *node = new Repl4S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2S_zero_rule: {
      Repl2S_zeroNode *node = new Repl2S_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4S_zero_rule: {
      Repl4S_zeroNode *node = new Repl4S_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8S_zero_rule: {
      Repl8S_zeroNode *node = new Repl8S_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16S_zero_rule: {
      Repl16S_zeroNode *node = new Repl16S_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2I_rule: {
      Repl2INode *node = new Repl2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2I_mem_rule: {
      Repl2I_memNode *node = new Repl2I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2I_imm_rule: {
      Repl2I_immNode *node = new Repl2I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2I_zero_rule: {
      Repl2I_zeroNode *node = new Repl2I_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4I_zero_rule: {
      Repl4I_zeroNode *node = new Repl4I_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8I_zero_rule: {
      Repl8I_zeroNode *node = new Repl8I_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2L_rule: {
      Repl2LNode *node = new Repl2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2L_imm_rule: {
      Repl2L_immNode *node = new Repl2L_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2L_zero_rule: {
      Repl2L_zeroNode *node = new Repl2L_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4L_zero_rule: {
      Repl4L_zeroNode *node = new Repl4L_zeroNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2F_rule: {
      Repl2FNode *node = new Repl2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4F_rule: {
      Repl4FNode *node = new Repl4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2D_rule: {
      Repl2DNode *node = new Repl2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4B_mem_evex_rule: {
      Repl4B_mem_evexNode *node = new Repl4B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8B_mem_evex_rule: {
      Repl8B_mem_evexNode *node = new Repl8B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16B_evex_rule: {
      Repl16B_evexNode *node = new Repl16B_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16B_mem_evex_rule: {
      Repl16B_mem_evexNode *node = new Repl16B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl32B_evex_rule: {
      Repl32B_evexNode *node = new Repl32B_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl32B_mem_evex_rule: {
      Repl32B_mem_evexNode *node = new Repl32B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl64B_evex_rule: {
      Repl64B_evexNode *node = new Repl64B_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl64B_mem_evex_rule: {
      Repl64B_mem_evexNode *node = new Repl64B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16B_imm_evex_rule: {
      Repl16B_imm_evexNode *node = new Repl16B_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl32B_imm_evex_rule: {
      Repl32B_imm_evexNode *node = new Repl32B_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl64B_imm_evex_rule: {
      Repl64B_imm_evexNode *node = new Repl64B_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl64B_zero_evex_rule: {
      Repl64B_zero_evexNode *node = new Repl64B_zero_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4S_evex_rule: {
      Repl4S_evexNode *node = new Repl4S_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4S_mem_evex_rule: {
      Repl4S_mem_evexNode *node = new Repl4S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8S_evex_rule: {
      Repl8S_evexNode *node = new Repl8S_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8S_mem_evex_rule: {
      Repl8S_mem_evexNode *node = new Repl8S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16S_evex_rule: {
      Repl16S_evexNode *node = new Repl16S_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16S_mem_evex_rule: {
      Repl16S_mem_evexNode *node = new Repl16S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl32S_evex_rule: {
      Repl32S_evexNode *node = new Repl32S_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl32S_mem_evex_rule: {
      Repl32S_mem_evexNode *node = new Repl32S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8S_imm_evex_rule: {
      Repl8S_imm_evexNode *node = new Repl8S_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16S_imm_evex_rule: {
      Repl16S_imm_evexNode *node = new Repl16S_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl32S_imm_evex_rule: {
      Repl32S_imm_evexNode *node = new Repl32S_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl32S_zero_evex_rule: {
      Repl32S_zero_evexNode *node = new Repl32S_zero_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4I_evex_rule: {
      Repl4I_evexNode *node = new Repl4I_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4I_mem_evex_rule: {
      Repl4I_mem_evexNode *node = new Repl4I_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8I_evex_rule: {
      Repl8I_evexNode *node = new Repl8I_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8I_mem_evex_rule: {
      Repl8I_mem_evexNode *node = new Repl8I_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16I_evex_rule: {
      Repl16I_evexNode *node = new Repl16I_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16I_mem_evex_rule: {
      Repl16I_mem_evexNode *node = new Repl16I_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4I_imm_evex_rule: {
      Repl4I_imm_evexNode *node = new Repl4I_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8I_imm_evex_rule: {
      Repl8I_imm_evexNode *node = new Repl8I_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16I_imm_evex_rule: {
      Repl16I_imm_evexNode *node = new Repl16I_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16I_zero_evex_rule: {
      Repl16I_zero_evexNode *node = new Repl16I_zero_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4L_evex_rule: {
      Repl4L_evexNode *node = new Repl4L_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8L_evex_rule: {
      Repl8L_evexNode *node = new Repl8L_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4L_imm_evex_rule: {
      Repl4L_imm_evexNode *node = new Repl4L_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8L_imm_evex_rule: {
      Repl8L_imm_evexNode *node = new Repl8L_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2L_mem_evex_rule: {
      Repl2L_mem_evexNode *node = new Repl2L_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4L_mem_evex_rule: {
      Repl4L_mem_evexNode *node = new Repl4L_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8L_mem_evex_rule: {
      Repl8L_mem_evexNode *node = new Repl8L_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8L_zero_evex_rule: {
      Repl8L_zero_evexNode *node = new Repl8L_zero_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8F_evex_rule: {
      Repl8F_evexNode *node = new Repl8F_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8F_mem_evex_rule: {
      Repl8F_mem_evexNode *node = new Repl8F_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16F_evex_rule: {
      Repl16F_evexNode *node = new Repl16F_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16F_mem_evex_rule: {
      Repl16F_mem_evexNode *node = new Repl16F_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2F_zero_evex_rule: {
      Repl2F_zero_evexNode *node = new Repl2F_zero_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4F_zero_evex_rule: {
      Repl4F_zero_evexNode *node = new Repl4F_zero_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8F_zero_evex_rule: {
      Repl8F_zero_evexNode *node = new Repl8F_zero_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl16F_zero_evex_rule: {
      Repl16F_zero_evexNode *node = new Repl16F_zero_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4D_evex_rule: {
      Repl4D_evexNode *node = new Repl4D_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4D_mem_evex_rule: {
      Repl4D_mem_evexNode *node = new Repl4D_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8D_evex_rule: {
      Repl8D_evexNode *node = new Repl8D_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8D_mem_evex_rule: {
      Repl8D_mem_evexNode *node = new Repl8D_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl2D_zero_evex_rule: {
      Repl2D_zero_evexNode *node = new Repl2D_zero_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl4D_zero_evex_rule: {
      Repl4D_zero_evexNode *node = new Repl4D_zero_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case Repl8D_zero_evex_rule: {
      Repl8D_zero_evexNode *node = new Repl8D_zero_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rsadd2I_reduction_reg_rule: {
      rsadd2I_reduction_regNode *node = new rsadd2I_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd2I_reduction_reg_rule: {
      rvadd2I_reduction_regNode *node = new rvadd2I_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd2I_reduction_reg_evex_rule: {
      rvadd2I_reduction_reg_evexNode *node = new rvadd2I_reduction_reg_evexNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rsadd4I_reduction_reg_rule: {
      rsadd4I_reduction_regNode *node = new rsadd4I_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd4I_reduction_reg_rule: {
      rvadd4I_reduction_regNode *node = new rvadd4I_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd4I_reduction_reg_evex_rule: {
      rvadd4I_reduction_reg_evexNode *node = new rvadd4I_reduction_reg_evexNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd8I_reduction_reg_rule: {
      rvadd8I_reduction_regNode *node = new rvadd8I_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd8I_reduction_reg_evex_rule: {
      rvadd8I_reduction_reg_evexNode *node = new rvadd8I_reduction_reg_evexNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd16I_reduction_reg_evex_rule: {
      rvadd16I_reduction_reg_evexNode *node = new rvadd16I_reduction_reg_evexNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->set_opnd_array(5, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd2L_reduction_reg_rule: {
      rvadd2L_reduction_regNode *node = new rvadd2L_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd4L_reduction_reg_rule: {
      rvadd4L_reduction_regNode *node = new rvadd4L_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd8L_reduction_reg_rule: {
      rvadd8L_reduction_regNode *node = new rvadd8L_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rsadd2F_reduction_reg_rule: {
      rsadd2F_reduction_regNode *node = new rsadd2F_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd2F_reduction_reg_rule: {
      rvadd2F_reduction_regNode *node = new rvadd2F_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rsadd4F_reduction_reg_rule: {
      rsadd4F_reduction_regNode *node = new rsadd4F_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd4F_reduction_reg_rule: {
      rvadd4F_reduction_regNode *node = new rvadd4F_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case radd8F_reduction_reg_rule: {
      radd8F_reduction_regNode *node = new radd8F_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->set_opnd_array(5, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case radd16F_reduction_reg_rule: {
      radd16F_reduction_regNode *node = new radd16F_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->set_opnd_array(5, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rsadd2D_reduction_reg_rule: {
      rsadd2D_reduction_regNode *node = new rsadd2D_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd2D_reduction_reg_rule: {
      rvadd2D_reduction_regNode *node = new rvadd2D_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd4D_reduction_reg_rule: {
      rvadd4D_reduction_regNode *node = new rvadd4D_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->set_opnd_array(5, MachOperGenerator(REGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvadd8D_reduction_reg_rule: {
      rvadd8D_reduction_regNode *node = new rvadd8D_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->set_opnd_array(5, MachOperGenerator(REGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rsmul2I_reduction_reg_rule: {
      rsmul2I_reduction_regNode *node = new rsmul2I_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul2I_reduction_reg_rule: {
      rvmul2I_reduction_regNode *node = new rvmul2I_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rsmul4I_reduction_reg_rule: {
      rsmul4I_reduction_regNode *node = new rsmul4I_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul4I_reduction_reg_rule: {
      rvmul4I_reduction_regNode *node = new rvmul4I_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul8I_reduction_reg_rule: {
      rvmul8I_reduction_regNode *node = new rvmul8I_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul16I_reduction_reg_rule: {
      rvmul16I_reduction_regNode *node = new rvmul16I_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->set_opnd_array(5, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul2L_reduction_reg_rule: {
      rvmul2L_reduction_regNode *node = new rvmul2L_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul4L_reduction_reg_rule: {
      rvmul4L_reduction_regNode *node = new rvmul4L_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul8L_reduction_reg_rule: {
      rvmul8L_reduction_regNode *node = new rvmul8L_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rsmul2F_reduction_rule: {
      rsmul2F_reductionNode *node = new rsmul2F_reductionNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul2F_reduction_reg_rule: {
      rvmul2F_reduction_regNode *node = new rvmul2F_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rsmul4F_reduction_reg_rule: {
      rsmul4F_reduction_regNode *node = new rsmul4F_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul4F_reduction_reg_rule: {
      rvmul4F_reduction_regNode *node = new rvmul4F_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul8F_reduction_reg_rule: {
      rvmul8F_reduction_regNode *node = new rvmul8F_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->set_opnd_array(5, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul16F_reduction_reg_rule: {
      rvmul16F_reduction_regNode *node = new rvmul16F_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGF));
      node->set_opnd_array(4, MachOperGenerator(REGF));
      node->set_opnd_array(5, MachOperGenerator(REGF));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rsmul2D_reduction_reg_rule: {
      rsmul2D_reduction_regNode *node = new rsmul2D_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul2D_reduction_reg_rule: {
      rvmul2D_reduction_regNode *node = new rvmul2D_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul4D_reduction_reg_rule: {
      rvmul4D_reduction_regNode *node = new rvmul4D_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->set_opnd_array(5, MachOperGenerator(REGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case rvmul8D_reduction_reg_rule: {
      rvmul8D_reduction_regNode *node = new rvmul8D_reduction_regNode();
      node->set_opnd_array(3, MachOperGenerator(REGD));
      node->set_opnd_array(4, MachOperGenerator(REGD));
      node->set_opnd_array(5, MachOperGenerator(REGD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4B_rule: {
      vadd4BNode *node = new vadd4BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4B_reg_avx_rule: {
      vadd4B_reg_avxNode *node = new vadd4B_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4B_reg_evex_rule: {
      vadd4B_reg_evexNode *node = new vadd4B_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4B_reg_evex_special_rule: {
      vadd4B_reg_evex_specialNode *node = new vadd4B_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4B_mem_avx_rule: {
      vadd4B_mem_avxNode *node = new vadd4B_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4B_mem_evex_rule: {
      vadd4B_mem_evexNode *node = new vadd4B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4B_mem_evex_special_rule: {
      vadd4B_mem_evex_specialNode *node = new vadd4B_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8B_rule: {
      vadd8BNode *node = new vadd8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8B_reg_avx_rule: {
      vadd8B_reg_avxNode *node = new vadd8B_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8B_reg_evex_rule: {
      vadd8B_reg_evexNode *node = new vadd8B_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8B_reg_evex_special_rule: {
      vadd8B_reg_evex_specialNode *node = new vadd8B_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8B_mem_avx_rule: {
      vadd8B_mem_avxNode *node = new vadd8B_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8B_mem_evex_rule: {
      vadd8B_mem_evexNode *node = new vadd8B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8B_mem_evex_special_rule: {
      vadd8B_mem_evex_specialNode *node = new vadd8B_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16B_rule: {
      vadd16BNode *node = new vadd16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16B_reg_avx_rule: {
      vadd16B_reg_avxNode *node = new vadd16B_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16B_reg_evex_rule: {
      vadd16B_reg_evexNode *node = new vadd16B_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16B_reg_evex_special_rule: {
      vadd16B_reg_evex_specialNode *node = new vadd16B_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16B_mem_avx_rule: {
      vadd16B_mem_avxNode *node = new vadd16B_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16B_mem_evex_rule: {
      vadd16B_mem_evexNode *node = new vadd16B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16B_mem_evex_special_rule: {
      vadd16B_mem_evex_specialNode *node = new vadd16B_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd32B_reg_avx_rule: {
      vadd32B_reg_avxNode *node = new vadd32B_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd32B_reg_evex_rule: {
      vadd32B_reg_evexNode *node = new vadd32B_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd32B_reg_evex_special_rule: {
      vadd32B_reg_evex_specialNode *node = new vadd32B_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd32B_mem_avx_rule: {
      vadd32B_mem_avxNode *node = new vadd32B_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd32B_mem_evex_rule: {
      vadd32B_mem_evexNode *node = new vadd32B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd32B_mem_evex_special_rule: {
      vadd32B_mem_evex_specialNode *node = new vadd32B_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd64B_reg_rule: {
      vadd64B_regNode *node = new vadd64B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd64B_mem_rule: {
      vadd64B_memNode *node = new vadd64B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2S_rule: {
      vadd2SNode *node = new vadd2SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2S_reg_avx_rule: {
      vadd2S_reg_avxNode *node = new vadd2S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2S_reg_evex_rule: {
      vadd2S_reg_evexNode *node = new vadd2S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2S_reg_evex_special_rule: {
      vadd2S_reg_evex_specialNode *node = new vadd2S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2S_mem_avx_rule: {
      vadd2S_mem_avxNode *node = new vadd2S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2S_mem_evex_rule: {
      vadd2S_mem_evexNode *node = new vadd2S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2S_mem_evex_special_rule: {
      vadd2S_mem_evex_specialNode *node = new vadd2S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4S_rule: {
      vadd4SNode *node = new vadd4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4S_reg_avx_rule: {
      vadd4S_reg_avxNode *node = new vadd4S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4S_reg_evex_rule: {
      vadd4S_reg_evexNode *node = new vadd4S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4S_reg_evex_special_rule: {
      vadd4S_reg_evex_specialNode *node = new vadd4S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4S_mem_avx_rule: {
      vadd4S_mem_avxNode *node = new vadd4S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4S_mem_evex_rule: {
      vadd4S_mem_evexNode *node = new vadd4S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4S_mem_evex_special_rule: {
      vadd4S_mem_evex_specialNode *node = new vadd4S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8S_rule: {
      vadd8SNode *node = new vadd8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8S_reg_avx_rule: {
      vadd8S_reg_avxNode *node = new vadd8S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8S_reg_evex_rule: {
      vadd8S_reg_evexNode *node = new vadd8S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8S_reg_evex_special_rule: {
      vadd8S_reg_evex_specialNode *node = new vadd8S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8S_mem_avx_rule: {
      vadd8S_mem_avxNode *node = new vadd8S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8S_mem_evex_rule: {
      vadd8S_mem_evexNode *node = new vadd8S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8S_mem_evex_special_rule: {
      vadd8S_mem_evex_specialNode *node = new vadd8S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16S_reg_avx_rule: {
      vadd16S_reg_avxNode *node = new vadd16S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16S_reg_evex_rule: {
      vadd16S_reg_evexNode *node = new vadd16S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16S_reg_evex_special_rule: {
      vadd16S_reg_evex_specialNode *node = new vadd16S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16S_mem_avx_rule: {
      vadd16S_mem_avxNode *node = new vadd16S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16S_mem_evex_rule: {
      vadd16S_mem_evexNode *node = new vadd16S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16S_mem_evex_special_rule: {
      vadd16S_mem_evex_specialNode *node = new vadd16S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd32S_reg_rule: {
      vadd32S_regNode *node = new vadd32S_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd32S_mem_rule: {
      vadd32S_memNode *node = new vadd32S_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2I_rule: {
      vadd2INode *node = new vadd2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2I_reg_rule: {
      vadd2I_regNode *node = new vadd2I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2I_mem_rule: {
      vadd2I_memNode *node = new vadd2I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4I_rule: {
      vadd4INode *node = new vadd4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4I_reg_rule: {
      vadd4I_regNode *node = new vadd4I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4I_mem_rule: {
      vadd4I_memNode *node = new vadd4I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8I_reg_rule: {
      vadd8I_regNode *node = new vadd8I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8I_mem_rule: {
      vadd8I_memNode *node = new vadd8I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16I_reg_rule: {
      vadd16I_regNode *node = new vadd16I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16I_mem_rule: {
      vadd16I_memNode *node = new vadd16I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2L_rule: {
      vadd2LNode *node = new vadd2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2L_reg_rule: {
      vadd2L_regNode *node = new vadd2L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2L_mem_rule: {
      vadd2L_memNode *node = new vadd2L_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4L_reg_rule: {
      vadd4L_regNode *node = new vadd4L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4L_mem_rule: {
      vadd4L_memNode *node = new vadd4L_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8L_reg_rule: {
      vadd8L_regNode *node = new vadd8L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8L_mem_rule: {
      vadd8L_memNode *node = new vadd8L_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2F_rule: {
      vadd2FNode *node = new vadd2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2F_reg_rule: {
      vadd2F_regNode *node = new vadd2F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2F_mem_rule: {
      vadd2F_memNode *node = new vadd2F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4F_rule: {
      vadd4FNode *node = new vadd4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4F_reg_rule: {
      vadd4F_regNode *node = new vadd4F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4F_mem_rule: {
      vadd4F_memNode *node = new vadd4F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8F_reg_rule: {
      vadd8F_regNode *node = new vadd8F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8F_mem_rule: {
      vadd8F_memNode *node = new vadd8F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16F_reg_rule: {
      vadd16F_regNode *node = new vadd16F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd16F_mem_rule: {
      vadd16F_memNode *node = new vadd16F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2D_rule: {
      vadd2DNode *node = new vadd2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2D_reg_rule: {
      vadd2D_regNode *node = new vadd2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd2D_mem_rule: {
      vadd2D_memNode *node = new vadd2D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4D_reg_rule: {
      vadd4D_regNode *node = new vadd4D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd4D_mem_rule: {
      vadd4D_memNode *node = new vadd4D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8D_reg_rule: {
      vadd8D_regNode *node = new vadd8D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vadd8D_mem_rule: {
      vadd8D_memNode *node = new vadd8D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4B_rule: {
      vsub4BNode *node = new vsub4BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4B_reg_avx_rule: {
      vsub4B_reg_avxNode *node = new vsub4B_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4B_reg_evex_rule: {
      vsub4B_reg_evexNode *node = new vsub4B_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4B_reg_exex_special_rule: {
      vsub4B_reg_exex_specialNode *node = new vsub4B_reg_exex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4B_mem_avx_rule: {
      vsub4B_mem_avxNode *node = new vsub4B_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4B_mem_evex_rule: {
      vsub4B_mem_evexNode *node = new vsub4B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4B_mem_evex_special_rule: {
      vsub4B_mem_evex_specialNode *node = new vsub4B_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8B_rule: {
      vsub8BNode *node = new vsub8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8B_reg_avx_rule: {
      vsub8B_reg_avxNode *node = new vsub8B_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8B_reg_evex_rule: {
      vsub8B_reg_evexNode *node = new vsub8B_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8B_reg_evex_special_rule: {
      vsub8B_reg_evex_specialNode *node = new vsub8B_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8B_mem_avx_rule: {
      vsub8B_mem_avxNode *node = new vsub8B_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8B_mem_evex_rule: {
      vsub8B_mem_evexNode *node = new vsub8B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8B_mem_evex_special_rule: {
      vsub8B_mem_evex_specialNode *node = new vsub8B_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16B_rule: {
      vsub16BNode *node = new vsub16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16B_reg_avx_rule: {
      vsub16B_reg_avxNode *node = new vsub16B_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16B_reg_evex_rule: {
      vsub16B_reg_evexNode *node = new vsub16B_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16B_reg_evex_special_rule: {
      vsub16B_reg_evex_specialNode *node = new vsub16B_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16B_mem_avx_rule: {
      vsub16B_mem_avxNode *node = new vsub16B_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16B_mem_evex_rule: {
      vsub16B_mem_evexNode *node = new vsub16B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16B_mem_evex_special_rule: {
      vsub16B_mem_evex_specialNode *node = new vsub16B_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub32B_reg_avx_rule: {
      vsub32B_reg_avxNode *node = new vsub32B_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub32B_reg_evex_rule: {
      vsub32B_reg_evexNode *node = new vsub32B_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub32B_reg_evex_special_rule: {
      vsub32B_reg_evex_specialNode *node = new vsub32B_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub32B_mem_avx_rule: {
      vsub32B_mem_avxNode *node = new vsub32B_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub32B_mem_evex_rule: {
      vsub32B_mem_evexNode *node = new vsub32B_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub32B_mem_evex_special_rule: {
      vsub32B_mem_evex_specialNode *node = new vsub32B_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub64B_reg_rule: {
      vsub64B_regNode *node = new vsub64B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub64B_mem_rule: {
      vsub64B_memNode *node = new vsub64B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2S_rule: {
      vsub2SNode *node = new vsub2SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2S_reg_avx_rule: {
      vsub2S_reg_avxNode *node = new vsub2S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2S_reg_evex_rule: {
      vsub2S_reg_evexNode *node = new vsub2S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2S_reg_evex_special_rule: {
      vsub2S_reg_evex_specialNode *node = new vsub2S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2S_mem_avx_rule: {
      vsub2S_mem_avxNode *node = new vsub2S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2S_mem_evex_rule: {
      vsub2S_mem_evexNode *node = new vsub2S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2S_mem_evex_special_rule: {
      vsub2S_mem_evex_specialNode *node = new vsub2S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4S_rule: {
      vsub4SNode *node = new vsub4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4S_reg_avx_rule: {
      vsub4S_reg_avxNode *node = new vsub4S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4S_reg_evex_rule: {
      vsub4S_reg_evexNode *node = new vsub4S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4S_reg_evex_special_rule: {
      vsub4S_reg_evex_specialNode *node = new vsub4S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4S_mem_avx_rule: {
      vsub4S_mem_avxNode *node = new vsub4S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4S_mem_evex_rule: {
      vsub4S_mem_evexNode *node = new vsub4S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4S_mem_evex_special_rule: {
      vsub4S_mem_evex_specialNode *node = new vsub4S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8S_rule: {
      vsub8SNode *node = new vsub8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8S_reg_avx_rule: {
      vsub8S_reg_avxNode *node = new vsub8S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8S_reg_evex_rule: {
      vsub8S_reg_evexNode *node = new vsub8S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8S_reg_evex_special_rule: {
      vsub8S_reg_evex_specialNode *node = new vsub8S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8S_mem_avx_rule: {
      vsub8S_mem_avxNode *node = new vsub8S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8S_mem_evex_rule: {
      vsub8S_mem_evexNode *node = new vsub8S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8S_mem_evex_special_rule: {
      vsub8S_mem_evex_specialNode *node = new vsub8S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16S_reg_avx_rule: {
      vsub16S_reg_avxNode *node = new vsub16S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16S_reg_evex_rule: {
      vsub16S_reg_evexNode *node = new vsub16S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16S_reg_evex_special_rule: {
      vsub16S_reg_evex_specialNode *node = new vsub16S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16S_mem_avx_rule: {
      vsub16S_mem_avxNode *node = new vsub16S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16S_mem_evex_rule: {
      vsub16S_mem_evexNode *node = new vsub16S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16S_mem_evex_special_rule: {
      vsub16S_mem_evex_specialNode *node = new vsub16S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub32S_reg_rule: {
      vsub32S_regNode *node = new vsub32S_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub32S_mem_rule: {
      vsub32S_memNode *node = new vsub32S_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2I_rule: {
      vsub2INode *node = new vsub2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2I_reg_rule: {
      vsub2I_regNode *node = new vsub2I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2I_mem_rule: {
      vsub2I_memNode *node = new vsub2I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4I_rule: {
      vsub4INode *node = new vsub4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4I_reg_rule: {
      vsub4I_regNode *node = new vsub4I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4I_mem_rule: {
      vsub4I_memNode *node = new vsub4I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8I_reg_rule: {
      vsub8I_regNode *node = new vsub8I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8I_mem_rule: {
      vsub8I_memNode *node = new vsub8I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16I_reg_rule: {
      vsub16I_regNode *node = new vsub16I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16I_mem_rule: {
      vsub16I_memNode *node = new vsub16I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2L_rule: {
      vsub2LNode *node = new vsub2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2L_reg_rule: {
      vsub2L_regNode *node = new vsub2L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2L_mem_rule: {
      vsub2L_memNode *node = new vsub2L_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4L_reg_rule: {
      vsub4L_regNode *node = new vsub4L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4L_mem_rule: {
      vsub4L_memNode *node = new vsub4L_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8L_reg_rule: {
      vsub8L_regNode *node = new vsub8L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8L_mem_rule: {
      vsub8L_memNode *node = new vsub8L_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2F_rule: {
      vsub2FNode *node = new vsub2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2F_reg_rule: {
      vsub2F_regNode *node = new vsub2F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2F_mem_rule: {
      vsub2F_memNode *node = new vsub2F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4F_rule: {
      vsub4FNode *node = new vsub4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4F_reg_rule: {
      vsub4F_regNode *node = new vsub4F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4F_mem_rule: {
      vsub4F_memNode *node = new vsub4F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8F_reg_rule: {
      vsub8F_regNode *node = new vsub8F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8F_mem_rule: {
      vsub8F_memNode *node = new vsub8F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16F_reg_rule: {
      vsub16F_regNode *node = new vsub16F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub16F_mem_rule: {
      vsub16F_memNode *node = new vsub16F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2D_rule: {
      vsub2DNode *node = new vsub2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2D_reg_rule: {
      vsub2D_regNode *node = new vsub2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub2D_mem_rule: {
      vsub2D_memNode *node = new vsub2D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4D_reg_rule: {
      vsub4D_regNode *node = new vsub4D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub4D_mem_rule: {
      vsub4D_memNode *node = new vsub4D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8D_reg_rule: {
      vsub8D_regNode *node = new vsub8D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsub8D_mem_rule: {
      vsub8D_memNode *node = new vsub8D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2S_rule: {
      vmul2SNode *node = new vmul2SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2S_reg_avx_rule: {
      vmul2S_reg_avxNode *node = new vmul2S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2S_reg_evex_rule: {
      vmul2S_reg_evexNode *node = new vmul2S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2S_evex_special_rule: {
      vmul2S_evex_specialNode *node = new vmul2S_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2S_mem_avx_rule: {
      vmul2S_mem_avxNode *node = new vmul2S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2S_mem_evex_rule: {
      vmul2S_mem_evexNode *node = new vmul2S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2S_mem_evex_special_rule: {
      vmul2S_mem_evex_specialNode *node = new vmul2S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4S_rule: {
      vmul4SNode *node = new vmul4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4S_reg_avx_rule: {
      vmul4S_reg_avxNode *node = new vmul4S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4S_reg_evex_rule: {
      vmul4S_reg_evexNode *node = new vmul4S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4S_reg_evex_special_rule: {
      vmul4S_reg_evex_specialNode *node = new vmul4S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4S_mem_avx_rule: {
      vmul4S_mem_avxNode *node = new vmul4S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4S_mem_evex_rule: {
      vmul4S_mem_evexNode *node = new vmul4S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4S_mem_evex_special_rule: {
      vmul4S_mem_evex_specialNode *node = new vmul4S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8S_rule: {
      vmul8SNode *node = new vmul8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8S_reg_avx_rule: {
      vmul8S_reg_avxNode *node = new vmul8S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8S_reg_evex_rule: {
      vmul8S_reg_evexNode *node = new vmul8S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8S_reg_evex_special_rule: {
      vmul8S_reg_evex_specialNode *node = new vmul8S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8S_mem_avx_rule: {
      vmul8S_mem_avxNode *node = new vmul8S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8S_mem_evex_rule: {
      vmul8S_mem_evexNode *node = new vmul8S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8S_mem_evex_special_rule: {
      vmul8S_mem_evex_specialNode *node = new vmul8S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul16S_reg_avx_rule: {
      vmul16S_reg_avxNode *node = new vmul16S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul16S_reg_evex_rule: {
      vmul16S_reg_evexNode *node = new vmul16S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul16S_reg_evex_special_rule: {
      vmul16S_reg_evex_specialNode *node = new vmul16S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul16S_mem_avx_rule: {
      vmul16S_mem_avxNode *node = new vmul16S_mem_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul16S_mem_evex_rule: {
      vmul16S_mem_evexNode *node = new vmul16S_mem_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul16S_mem_evex_special_rule: {
      vmul16S_mem_evex_specialNode *node = new vmul16S_mem_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul32S_reg_rule: {
      vmul32S_regNode *node = new vmul32S_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul32S_mem_rule: {
      vmul32S_memNode *node = new vmul32S_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2I_rule: {
      vmul2INode *node = new vmul2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2I_reg_rule: {
      vmul2I_regNode *node = new vmul2I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2I_mem_rule: {
      vmul2I_memNode *node = new vmul2I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4I_rule: {
      vmul4INode *node = new vmul4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4I_reg_rule: {
      vmul4I_regNode *node = new vmul4I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4I_mem_rule: {
      vmul4I_memNode *node = new vmul4I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2L_reg_rule: {
      vmul2L_regNode *node = new vmul2L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2L_mem_rule: {
      vmul2L_memNode *node = new vmul2L_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4L_reg_rule: {
      vmul4L_regNode *node = new vmul4L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4L_mem_rule: {
      vmul4L_memNode *node = new vmul4L_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8L_reg_rule: {
      vmul8L_regNode *node = new vmul8L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8L_mem_rule: {
      vmul8L_memNode *node = new vmul8L_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8I_reg_rule: {
      vmul8I_regNode *node = new vmul8I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8I_mem_rule: {
      vmul8I_memNode *node = new vmul8I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul16I_reg_rule: {
      vmul16I_regNode *node = new vmul16I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul16I_mem_rule: {
      vmul16I_memNode *node = new vmul16I_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2F_rule: {
      vmul2FNode *node = new vmul2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2F_reg_rule: {
      vmul2F_regNode *node = new vmul2F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2F_mem_rule: {
      vmul2F_memNode *node = new vmul2F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4F_rule: {
      vmul4FNode *node = new vmul4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4F_reg_rule: {
      vmul4F_regNode *node = new vmul4F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4F_mem_rule: {
      vmul4F_memNode *node = new vmul4F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8F_reg_rule: {
      vmul8F_regNode *node = new vmul8F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8F_mem_rule: {
      vmul8F_memNode *node = new vmul8F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul16F_reg_rule: {
      vmul16F_regNode *node = new vmul16F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul16F_mem_rule: {
      vmul16F_memNode *node = new vmul16F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2D_rule: {
      vmul2DNode *node = new vmul2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2D_reg_rule: {
      vmul2D_regNode *node = new vmul2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul2D_mem_rule: {
      vmul2D_memNode *node = new vmul2D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4D_reg_rule: {
      vmul4D_regNode *node = new vmul4D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul4D_mem_rule: {
      vmul4D_memNode *node = new vmul4D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8D_reg_rule: {
      vmul8D_regNode *node = new vmul8D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vmul8D_mem_rule: {
      vmul8D_memNode *node = new vmul8D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vcmov4D_reg_rule: {
      vcmov4D_regNode *node = new vcmov4D_regNode();
      node->set_opnd_array(5, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv2F_rule: {
      vdiv2FNode *node = new vdiv2FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv2F_reg_rule: {
      vdiv2F_regNode *node = new vdiv2F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv2F_mem_rule: {
      vdiv2F_memNode *node = new vdiv2F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv4F_rule: {
      vdiv4FNode *node = new vdiv4FNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv4F_reg_rule: {
      vdiv4F_regNode *node = new vdiv4F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv4F_mem_rule: {
      vdiv4F_memNode *node = new vdiv4F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv8F_reg_rule: {
      vdiv8F_regNode *node = new vdiv8F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv8F_mem_rule: {
      vdiv8F_memNode *node = new vdiv8F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv16F_reg_rule: {
      vdiv16F_regNode *node = new vdiv16F_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv16F_mem_rule: {
      vdiv16F_memNode *node = new vdiv16F_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv2D_rule: {
      vdiv2DNode *node = new vdiv2DNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv2D_reg_rule: {
      vdiv2D_regNode *node = new vdiv2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv2D_mem_rule: {
      vdiv2D_memNode *node = new vdiv2D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv4D_reg_rule: {
      vdiv4D_regNode *node = new vdiv4D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv4D_mem_rule: {
      vdiv4D_memNode *node = new vdiv4D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv8D_reg_rule: {
      vdiv8D_regNode *node = new vdiv8D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vdiv8D_mem_rule: {
      vdiv8D_memNode *node = new vdiv8D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcnt_rule: {
      vshiftcntNode *node = new vshiftcntNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vshiftcnt_0_rule: {
      vshiftcnt_0Node *node = new vshiftcnt_0Node();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt2D_reg_rule: {
      vsqrt2D_regNode *node = new vsqrt2D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt2D_mem_rule: {
      vsqrt2D_memNode *node = new vsqrt2D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt4D_reg_rule: {
      vsqrt4D_regNode *node = new vsqrt4D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt4D_mem_rule: {
      vsqrt4D_memNode *node = new vsqrt4D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt8D_reg_rule: {
      vsqrt8D_regNode *node = new vsqrt8D_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsqrt8D_mem_rule: {
      vsqrt8D_memNode *node = new vsqrt8D_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2S_rule: {
      vsll2SNode *node = new vsll2SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2S_imm_rule: {
      vsll2S_immNode *node = new vsll2S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2S_reg_avx_rule: {
      vsll2S_reg_avxNode *node = new vsll2S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2S_reg_evex_rule: {
      vsll2S_reg_evexNode *node = new vsll2S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2S_reg_evex_special_rule: {
      vsll2S_reg_evex_specialNode *node = new vsll2S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2S_reg_imm_avx_rule: {
      vsll2S_reg_imm_avxNode *node = new vsll2S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2S_reg_imm_evex_rule: {
      vsll2S_reg_imm_evexNode *node = new vsll2S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2S_reg_imm_evex_special_rule: {
      vsll2S_reg_imm_evex_specialNode *node = new vsll2S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4S_rule: {
      vsll4SNode *node = new vsll4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4S_imm_rule: {
      vsll4S_immNode *node = new vsll4S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4S_reg_avx_rule: {
      vsll4S_reg_avxNode *node = new vsll4S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4S_reg_evex_rule: {
      vsll4S_reg_evexNode *node = new vsll4S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4S_reg_evex_special_rule: {
      vsll4S_reg_evex_specialNode *node = new vsll4S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4S_reg_imm_avx_rule: {
      vsll4S_reg_imm_avxNode *node = new vsll4S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4S_reg_imm_evex_rule: {
      vsll4S_reg_imm_evexNode *node = new vsll4S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4S_reg_imm_evex_special_rule: {
      vsll4S_reg_imm_evex_specialNode *node = new vsll4S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8S_rule: {
      vsll8SNode *node = new vsll8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8S_imm_rule: {
      vsll8S_immNode *node = new vsll8S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8S_reg_avx_rule: {
      vsll8S_reg_avxNode *node = new vsll8S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8S_reg_evex_rule: {
      vsll8S_reg_evexNode *node = new vsll8S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8S_reg_evex_special_rule: {
      vsll8S_reg_evex_specialNode *node = new vsll8S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8S_reg_imm_avx_rule: {
      vsll8S_reg_imm_avxNode *node = new vsll8S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8S_reg_imm_evex_rule: {
      vsll8S_reg_imm_evexNode *node = new vsll8S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8S_reg_imm_evex_special_rule: {
      vsll8S_reg_imm_evex_specialNode *node = new vsll8S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll16S_reg_avx_rule: {
      vsll16S_reg_avxNode *node = new vsll16S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll16S_reg_evex_rule: {
      vsll16S_reg_evexNode *node = new vsll16S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll16S_reg_evex_special_rule: {
      vsll16S_reg_evex_specialNode *node = new vsll16S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll16S_reg_imm_avx_rule: {
      vsll16S_reg_imm_avxNode *node = new vsll16S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll16S_reg_imm_evex_rule: {
      vsll16S_reg_imm_evexNode *node = new vsll16S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll16S_reg_imm_evex_special_rule: {
      vsll16S_reg_imm_evex_specialNode *node = new vsll16S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll32S_reg_rule: {
      vsll32S_regNode *node = new vsll32S_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll32S_reg_imm_rule: {
      vsll32S_reg_immNode *node = new vsll32S_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2I_rule: {
      vsll2INode *node = new vsll2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2I_imm_rule: {
      vsll2I_immNode *node = new vsll2I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2I_reg_rule: {
      vsll2I_regNode *node = new vsll2I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2I_reg_imm_rule: {
      vsll2I_reg_immNode *node = new vsll2I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4I_rule: {
      vsll4INode *node = new vsll4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4I_imm_rule: {
      vsll4I_immNode *node = new vsll4I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4I_reg_rule: {
      vsll4I_regNode *node = new vsll4I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4I_reg_imm_rule: {
      vsll4I_reg_immNode *node = new vsll4I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8I_reg_rule: {
      vsll8I_regNode *node = new vsll8I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8I_reg_imm_rule: {
      vsll8I_reg_immNode *node = new vsll8I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll16I_reg_rule: {
      vsll16I_regNode *node = new vsll16I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll16I_reg_imm_rule: {
      vsll16I_reg_immNode *node = new vsll16I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2L_rule: {
      vsll2LNode *node = new vsll2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2L_imm_rule: {
      vsll2L_immNode *node = new vsll2L_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2L_reg_rule: {
      vsll2L_regNode *node = new vsll2L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll2L_reg_imm_rule: {
      vsll2L_reg_immNode *node = new vsll2L_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4L_reg_rule: {
      vsll4L_regNode *node = new vsll4L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll4L_reg_imm_rule: {
      vsll4L_reg_immNode *node = new vsll4L_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8L_reg_rule: {
      vsll8L_regNode *node = new vsll8L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsll8L_reg_imm_rule: {
      vsll8L_reg_immNode *node = new vsll8L_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2S_rule: {
      vsrl2SNode *node = new vsrl2SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2S_imm_rule: {
      vsrl2S_immNode *node = new vsrl2S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2S_reg_avx_rule: {
      vsrl2S_reg_avxNode *node = new vsrl2S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2S_reg_evex_rule: {
      vsrl2S_reg_evexNode *node = new vsrl2S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2S_reg_evex_special_rule: {
      vsrl2S_reg_evex_specialNode *node = new vsrl2S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2S_reg_imm_avx_rule: {
      vsrl2S_reg_imm_avxNode *node = new vsrl2S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2S_reg_imm_evex_rule: {
      vsrl2S_reg_imm_evexNode *node = new vsrl2S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2S_reg_imm_evex_special_rule: {
      vsrl2S_reg_imm_evex_specialNode *node = new vsrl2S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4S_rule: {
      vsrl4SNode *node = new vsrl4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4S_imm_rule: {
      vsrl4S_immNode *node = new vsrl4S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4S_reg_avx_rule: {
      vsrl4S_reg_avxNode *node = new vsrl4S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4S_reg_evex_rule: {
      vsrl4S_reg_evexNode *node = new vsrl4S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4S_reg_evex_special_rule: {
      vsrl4S_reg_evex_specialNode *node = new vsrl4S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4S_reg_imm_avx_rule: {
      vsrl4S_reg_imm_avxNode *node = new vsrl4S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4S_reg_imm_evex_rule: {
      vsrl4S_reg_imm_evexNode *node = new vsrl4S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4S_reg_imm_evex_special_rule: {
      vsrl4S_reg_imm_evex_specialNode *node = new vsrl4S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8S_rule: {
      vsrl8SNode *node = new vsrl8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8S_imm_rule: {
      vsrl8S_immNode *node = new vsrl8S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8S_reg_avx_rule: {
      vsrl8S_reg_avxNode *node = new vsrl8S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8S_reg_evex_rule: {
      vsrl8S_reg_evexNode *node = new vsrl8S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8S_reg_evex_special_rule: {
      vsrl8S_reg_evex_specialNode *node = new vsrl8S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8S_reg_imm_avx_rule: {
      vsrl8S_reg_imm_avxNode *node = new vsrl8S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8S_reg_imm_evex_rule: {
      vsrl8S_reg_imm_evexNode *node = new vsrl8S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8S_reg_imm_evex_special_rule: {
      vsrl8S_reg_imm_evex_specialNode *node = new vsrl8S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl16S_reg_avx_rule: {
      vsrl16S_reg_avxNode *node = new vsrl16S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl16S_reg_evex_rule: {
      vsrl16S_reg_evexNode *node = new vsrl16S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl16S_reg_evex_special_rule: {
      vsrl16S_reg_evex_specialNode *node = new vsrl16S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl16S_reg_imm_avx_rule: {
      vsrl16S_reg_imm_avxNode *node = new vsrl16S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl16S_reg_imm_evex_rule: {
      vsrl16S_reg_imm_evexNode *node = new vsrl16S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl16S_reg_imm_evex_special_rule: {
      vsrl16S_reg_imm_evex_specialNode *node = new vsrl16S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl32S_reg_rule: {
      vsrl32S_regNode *node = new vsrl32S_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl32S_reg_imm_rule: {
      vsrl32S_reg_immNode *node = new vsrl32S_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2I_rule: {
      vsrl2INode *node = new vsrl2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2I_imm_rule: {
      vsrl2I_immNode *node = new vsrl2I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2I_reg_rule: {
      vsrl2I_regNode *node = new vsrl2I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2I_reg_imm_rule: {
      vsrl2I_reg_immNode *node = new vsrl2I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4I_rule: {
      vsrl4INode *node = new vsrl4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4I_imm_rule: {
      vsrl4I_immNode *node = new vsrl4I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4I_reg_rule: {
      vsrl4I_regNode *node = new vsrl4I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4I_reg_imm_rule: {
      vsrl4I_reg_immNode *node = new vsrl4I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8I_reg_rule: {
      vsrl8I_regNode *node = new vsrl8I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8I_reg_imm_rule: {
      vsrl8I_reg_immNode *node = new vsrl8I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl16I_reg_rule: {
      vsrl16I_regNode *node = new vsrl16I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl16I_reg_imm_rule: {
      vsrl16I_reg_immNode *node = new vsrl16I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2L_rule: {
      vsrl2LNode *node = new vsrl2LNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2L_imm_rule: {
      vsrl2L_immNode *node = new vsrl2L_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2L_reg_rule: {
      vsrl2L_regNode *node = new vsrl2L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl2L_reg_imm_rule: {
      vsrl2L_reg_immNode *node = new vsrl2L_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4L_reg_rule: {
      vsrl4L_regNode *node = new vsrl4L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl4L_reg_imm_rule: {
      vsrl4L_reg_immNode *node = new vsrl4L_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8L_reg_rule: {
      vsrl8L_regNode *node = new vsrl8L_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsrl8L_reg_imm_rule: {
      vsrl8L_reg_immNode *node = new vsrl8L_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2S_rule: {
      vsra2SNode *node = new vsra2SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2S_imm_rule: {
      vsra2S_immNode *node = new vsra2S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2S_reg_avx_rule: {
      vsra2S_reg_avxNode *node = new vsra2S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2S_reg_evex_rule: {
      vsra2S_reg_evexNode *node = new vsra2S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2S_reg_evex_special_rule: {
      vsra2S_reg_evex_specialNode *node = new vsra2S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2S_reg_imm_avx_rule: {
      vsra2S_reg_imm_avxNode *node = new vsra2S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2S_reg_imm_evex_rule: {
      vsra2S_reg_imm_evexNode *node = new vsra2S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2S_reg_imm_evex_special_rule: {
      vsra2S_reg_imm_evex_specialNode *node = new vsra2S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECS));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4S_rule: {
      vsra4SNode *node = new vsra4SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4S_imm_rule: {
      vsra4S_immNode *node = new vsra4S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4S_reg_avx_rule: {
      vsra4S_reg_avxNode *node = new vsra4S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4S_reg_evex_rule: {
      vsra4S_reg_evexNode *node = new vsra4S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4S_reg_evex_special_rule: {
      vsra4S_reg_evex_specialNode *node = new vsra4S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4S_reg_imm_avx_rule: {
      vsra4S_reg_imm_avxNode *node = new vsra4S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4S_reg_imm_evex_rule: {
      vsra4S_reg_imm_evexNode *node = new vsra4S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4S_reg_imm_evex_special_rule: {
      vsra4S_reg_imm_evex_specialNode *node = new vsra4S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECD));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8S_rule: {
      vsra8SNode *node = new vsra8SNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8S_imm_rule: {
      vsra8S_immNode *node = new vsra8S_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8S_reg_avx_rule: {
      vsra8S_reg_avxNode *node = new vsra8S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8S_reg_evex_rule: {
      vsra8S_reg_evexNode *node = new vsra8S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8S_reg_evex_special_rule: {
      vsra8S_reg_evex_specialNode *node = new vsra8S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8S_reg_imm_avx_rule: {
      vsra8S_reg_imm_avxNode *node = new vsra8S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8S_reg_imm_evex_rule: {
      vsra8S_reg_imm_evexNode *node = new vsra8S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8S_reg_imm_evex_special_rule: {
      vsra8S_reg_imm_evex_specialNode *node = new vsra8S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECX));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra16S_reg_avx_rule: {
      vsra16S_reg_avxNode *node = new vsra16S_reg_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra16S_reg_evex_rule: {
      vsra16S_reg_evexNode *node = new vsra16S_reg_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra16S_reg_evex_special_rule: {
      vsra16S_reg_evex_specialNode *node = new vsra16S_reg_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra16S_reg_imm_avx_rule: {
      vsra16S_reg_imm_avxNode *node = new vsra16S_reg_imm_avxNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra16S_reg_imm_evex_rule: {
      vsra16S_reg_imm_evexNode *node = new vsra16S_reg_imm_evexNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra16S_reg_imm_evex_special_rule: {
      vsra16S_reg_imm_evex_specialNode *node = new vsra16S_reg_imm_evex_specialNode();
      node->set_opnd_array(3, MachOperGenerator(VECY));
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra32S_reg_rule: {
      vsra32S_regNode *node = new vsra32S_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra32S_reg_imm_rule: {
      vsra32S_reg_immNode *node = new vsra32S_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2I_rule: {
      vsra2INode *node = new vsra2INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2I_imm_rule: {
      vsra2I_immNode *node = new vsra2I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2I_reg_rule: {
      vsra2I_regNode *node = new vsra2I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra2I_reg_imm_rule: {
      vsra2I_reg_immNode *node = new vsra2I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4I_rule: {
      vsra4INode *node = new vsra4INode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4I_imm_rule: {
      vsra4I_immNode *node = new vsra4I_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4I_reg_rule: {
      vsra4I_regNode *node = new vsra4I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra4I_reg_imm_rule: {
      vsra4I_reg_immNode *node = new vsra4I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8I_reg_rule: {
      vsra8I_regNode *node = new vsra8I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra8I_reg_imm_rule: {
      vsra8I_reg_immNode *node = new vsra8I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra16I_reg_rule: {
      vsra16I_regNode *node = new vsra16I_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vsra16I_reg_imm_rule: {
      vsra16I_reg_immNode *node = new vsra16I_reg_immNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand4B_rule: {
      vand4BNode *node = new vand4BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand4B_reg_rule: {
      vand4B_regNode *node = new vand4B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand4B_mem_rule: {
      vand4B_memNode *node = new vand4B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand8B_rule: {
      vand8BNode *node = new vand8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand8B_reg_rule: {
      vand8B_regNode *node = new vand8B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand8B_mem_rule: {
      vand8B_memNode *node = new vand8B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand16B_rule: {
      vand16BNode *node = new vand16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand16B_reg_rule: {
      vand16B_regNode *node = new vand16B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand16B_mem_rule: {
      vand16B_memNode *node = new vand16B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand32B_reg_rule: {
      vand32B_regNode *node = new vand32B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand32B_mem_rule: {
      vand32B_memNode *node = new vand32B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand64B_reg_rule: {
      vand64B_regNode *node = new vand64B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vand64B_mem_rule: {
      vand64B_memNode *node = new vand64B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor4B_rule: {
      vor4BNode *node = new vor4BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor4B_reg_rule: {
      vor4B_regNode *node = new vor4B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor4B_mem_rule: {
      vor4B_memNode *node = new vor4B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor8B_rule: {
      vor8BNode *node = new vor8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor8B_reg_rule: {
      vor8B_regNode *node = new vor8B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor8B_mem_rule: {
      vor8B_memNode *node = new vor8B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor16B_rule: {
      vor16BNode *node = new vor16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor16B_reg_rule: {
      vor16B_regNode *node = new vor16B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor16B_mem_rule: {
      vor16B_memNode *node = new vor16B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor32B_reg_rule: {
      vor32B_regNode *node = new vor32B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor32B_mem_rule: {
      vor32B_memNode *node = new vor32B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor64B_reg_rule: {
      vor64B_regNode *node = new vor64B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vor64B_mem_rule: {
      vor64B_memNode *node = new vor64B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor4B_rule: {
      vxor4BNode *node = new vxor4BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor4B_reg_rule: {
      vxor4B_regNode *node = new vxor4B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor4B_mem_rule: {
      vxor4B_memNode *node = new vxor4B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor8B_rule: {
      vxor8BNode *node = new vxor8BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor8B_reg_rule: {
      vxor8B_regNode *node = new vxor8B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor8B_mem_rule: {
      vxor8B_memNode *node = new vxor8B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor16B_rule: {
      vxor16BNode *node = new vxor16BNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor16B_reg_rule: {
      vxor16B_regNode *node = new vxor16B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor16B_mem_rule: {
      vxor16B_memNode *node = new vxor16B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor32B_reg_rule: {
      vxor32B_regNode *node = new vxor32B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor32B_mem_rule: {
      vxor32B_memNode *node = new vxor32B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor64B_reg_rule: {
      vxor64B_regNode *node = new vxor64B_regNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  case vxor64B_mem_rule: {
      vxor64B_memNode *node = new vxor64B_memNode();
      node->_bottom_type = _leaf->bottom_type();
      return node;
    }
  
  default:
    fprintf(stderr, "Default MachNode Generator invoked for: \n");
    fprintf(stderr, "   opcode = %d\n", opcode);
    break;
  };
  return NULL;
}
// Check consistency of C++ compilation with ADLC options:
// Check adlc -DLINUX=1
#ifndef LINUX
#  error "LINUX must be defined"
#endif // LINUX
// Check adlc -D_GNU_SOURCE=1
#ifndef _GNU_SOURCE
#  error "_GNU_SOURCE must be defined"
#endif // _GNU_SOURCE
// Check adlc -DAMD64=1
#ifndef AMD64
#  error "AMD64 must be defined"
#endif // AMD64
// Check adlc -D_LP64=1
#ifndef _LP64
#  error "_LP64 must be defined"
#endif // _LP64
