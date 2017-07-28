#line 1 "ad_x86_clone.cpp"
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
MachOper *UniverseOper::clone() const {
  return new UniverseOper();
}
MachOper *sRegIOper::clone() const {
  return new sRegIOper();
}
MachOper *sRegPOper::clone() const {
  return new sRegPOper();
}
MachOper *sRegFOper::clone() const {
  return new sRegFOper();
}
MachOper *sRegDOper::clone() const {
  return new sRegDOper();
}
MachOper *sRegLOper::clone() const {
  return new sRegLOper();
}
MachOper *immIOper::clone() const {
  return new immIOper(_c0);
}
MachOper *immI0Oper::clone() const {
  return new immI0Oper(_c0);
}
MachOper *immI1Oper::clone() const {
  return new immI1Oper(_c0);
}
MachOper *immI_M1Oper::clone() const {
  return new immI_M1Oper(_c0);
}
MachOper *immI2Oper::clone() const {
  return new immI2Oper(_c0);
}
MachOper *immI8Oper::clone() const {
  return new immI8Oper(_c0);
}
MachOper *immI16Oper::clone() const {
  return new immI16Oper(_c0);
}
MachOper *immU31Oper::clone() const {
  return new immU31Oper(_c0);
}
MachOper *immI_32Oper::clone() const {
  return new immI_32Oper(_c0);
}
MachOper *immI_64Oper::clone() const {
  return new immI_64Oper(_c0);
}
MachOper *immPOper::clone() const {
  return new immPOper(_c0);
}
MachOper *immP0Oper::clone() const {
  return new immP0Oper(_c0);
}
MachOper *immNOper::clone() const {
  return new immNOper(_c0);
}
MachOper *immNKlassOper::clone() const {
  return new immNKlassOper(_c0);
}
MachOper *immN0Oper::clone() const {
  return new immN0Oper(_c0);
}
MachOper *immP31Oper::clone() const {
  return new immP31Oper(_c0);
}
MachOper *immLOper::clone() const {
  return new immLOper(_c0);
}
MachOper *immL8Oper::clone() const {
  return new immL8Oper(_c0);
}
MachOper *immUL32Oper::clone() const {
  return new immUL32Oper(_c0);
}
MachOper *immL32Oper::clone() const {
  return new immL32Oper(_c0);
}
MachOper *immL0Oper::clone() const {
  return new immL0Oper(_c0);
}
MachOper *immL1Oper::clone() const {
  return new immL1Oper(_c0);
}
MachOper *immL_M1Oper::clone() const {
  return new immL_M1Oper(_c0);
}
MachOper *immL10Oper::clone() const {
  return new immL10Oper(_c0);
}
MachOper *immL_127Oper::clone() const {
  return new immL_127Oper(_c0);
}
MachOper *immL_32bitsOper::clone() const {
  return new immL_32bitsOper(_c0);
}
MachOper *immF0Oper::clone() const {
  return new immF0Oper(_c0);
}
MachOper *immFOper::clone() const {
  return new immFOper(_c0);
}
MachOper *immD0Oper::clone() const {
  return new immD0Oper(_c0);
}
MachOper *immDOper::clone() const {
  return new immDOper(_c0);
}
MachOper *immI_16Oper::clone() const {
  return new immI_16Oper(_c0);
}
MachOper *immI_24Oper::clone() const {
  return new immI_24Oper(_c0);
}
MachOper *immI_255Oper::clone() const {
  return new immI_255Oper(_c0);
}
MachOper *immI_65535Oper::clone() const {
  return new immI_65535Oper(_c0);
}
MachOper *immL_255Oper::clone() const {
  return new immL_255Oper(_c0);
}
MachOper *immL_65535Oper::clone() const {
  return new immL_65535Oper(_c0);
}
MachOper *rRegIOper::clone() const {
  return new rRegIOper();
}
MachOper *rax_RegIOper::clone() const {
  return new rax_RegIOper();
}
MachOper *rbx_RegIOper::clone() const {
  return new rbx_RegIOper();
}
MachOper *rcx_RegIOper::clone() const {
  return new rcx_RegIOper();
}
MachOper *rdx_RegIOper::clone() const {
  return new rdx_RegIOper();
}
MachOper *rdi_RegIOper::clone() const {
  return new rdi_RegIOper();
}
MachOper *no_rcx_RegIOper::clone() const {
  return new no_rcx_RegIOper();
}
MachOper *no_rax_rdx_RegIOper::clone() const {
  return new no_rax_rdx_RegIOper();
}
MachOper *any_RegPOper::clone() const {
  return new any_RegPOper();
}
MachOper *rRegPOper::clone() const {
  return new rRegPOper();
}
MachOper *rRegNOper::clone() const {
  return new rRegNOper();
}
MachOper *no_rax_RegPOper::clone() const {
  return new no_rax_RegPOper();
}
MachOper *no_rbp_RegPOper::clone() const {
  return new no_rbp_RegPOper();
}
MachOper *no_rax_rbx_RegPOper::clone() const {
  return new no_rax_rbx_RegPOper();
}
MachOper *rax_RegPOper::clone() const {
  return new rax_RegPOper();
}
MachOper *rax_RegNOper::clone() const {
  return new rax_RegNOper();
}
MachOper *rbx_RegPOper::clone() const {
  return new rbx_RegPOper();
}
MachOper *rsi_RegPOper::clone() const {
  return new rsi_RegPOper();
}
MachOper *rdi_RegPOper::clone() const {
  return new rdi_RegPOper();
}
MachOper *r15_RegPOper::clone() const {
  return new r15_RegPOper();
}
MachOper *rRegLOper::clone() const {
  return new rRegLOper();
}
MachOper *no_rax_rdx_RegLOper::clone() const {
  return new no_rax_rdx_RegLOper();
}
MachOper *no_rax_RegLOper::clone() const {
  return new no_rax_RegLOper();
}
MachOper *no_rcx_RegLOper::clone() const {
  return new no_rcx_RegLOper();
}
MachOper *rax_RegLOper::clone() const {
  return new rax_RegLOper();
}
MachOper *rcx_RegLOper::clone() const {
  return new rcx_RegLOper();
}
MachOper *rdx_RegLOper::clone() const {
  return new rdx_RegLOper();
}
MachOper *rFlagsRegOper::clone() const {
  return new rFlagsRegOper();
}
MachOper *rFlagsRegUOper::clone() const {
  return new rFlagsRegUOper();
}
MachOper *rFlagsRegUCFOper::clone() const {
  return new rFlagsRegUCFOper();
}
MachOper *regFOper::clone() const {
  return new regFOper();
}
MachOper *regDOper::clone() const {
  return new regDOper();
}
MachOper *vecSOper::clone() const {
  return new vecSOper();
}
MachOper *vecDOper::clone() const {
  return new vecDOper();
}
MachOper *vecXOper::clone() const {
  return new vecXOper();
}
MachOper *vecYOper::clone() const {
  return new vecYOper();
}
MachOper *indirectOper::clone() const {
  return new indirectOper();
}
MachOper *indOffset8Oper::clone() const {
  return new indOffset8Oper(_c0);
}
MachOper *indOffset32Oper::clone() const {
  return new indOffset32Oper(_c0);
}
MachOper *indIndexOffsetOper::clone() const {
  return new indIndexOffsetOper(_c0);
}
MachOper *indIndexOper::clone() const {
  return new indIndexOper();
}
MachOper *indIndexScaleOper::clone() const {
  return new indIndexScaleOper(_c0);
}
MachOper *indPosIndexScaleOper::clone() const {
  return new indPosIndexScaleOper(_c0);
}
MachOper *indIndexScaleOffsetOper::clone() const {
  return new indIndexScaleOffsetOper(_c0, _c1);
}
MachOper *indPosIndexOffsetOper::clone() const {
  return new indPosIndexOffsetOper(_c0);
}
MachOper *indPosIndexScaleOffsetOper::clone() const {
  return new indPosIndexScaleOffsetOper(_c0, _c1);
}
MachOper *indCompressedOopOffsetOper::clone() const {
  return new indCompressedOopOffsetOper(_c0);
}
MachOper *indirectNarrowOper::clone() const {
  return new indirectNarrowOper();
}
MachOper *indOffset8NarrowOper::clone() const {
  return new indOffset8NarrowOper(_c0);
}
MachOper *indOffset32NarrowOper::clone() const {
  return new indOffset32NarrowOper(_c0);
}
MachOper *indIndexOffsetNarrowOper::clone() const {
  return new indIndexOffsetNarrowOper(_c0);
}
MachOper *indIndexNarrowOper::clone() const {
  return new indIndexNarrowOper();
}
MachOper *indIndexScaleNarrowOper::clone() const {
  return new indIndexScaleNarrowOper(_c0);
}
MachOper *indIndexScaleOffsetNarrowOper::clone() const {
  return new indIndexScaleOffsetNarrowOper(_c0, _c1);
}
MachOper *indPosIndexOffsetNarrowOper::clone() const {
  return new indPosIndexOffsetNarrowOper(_c0);
}
MachOper *indPosIndexScaleOffsetNarrowOper::clone() const {
  return new indPosIndexScaleOffsetNarrowOper(_c0, _c1);
}
MachOper *stackSlotPOper::clone() const {
  return new stackSlotPOper();
}
MachOper *stackSlotIOper::clone() const {
  return new stackSlotIOper();
}
MachOper *stackSlotFOper::clone() const {
  return new stackSlotFOper();
}
MachOper *stackSlotDOper::clone() const {
  return new stackSlotDOper();
}
MachOper *stackSlotLOper::clone() const {
  return new stackSlotLOper();
}
MachOper *cmpOpOper::clone() const {
  return new cmpOpOper(_c0);
}
MachOper *cmpOpUOper::clone() const {
  return new cmpOpUOper(_c0);
}
MachOper *cmpOpUCFOper::clone() const {
  return new cmpOpUCFOper(_c0);
}
MachOper *cmpOpUCF2Oper::clone() const {
  return new cmpOpUCF2Oper(_c0);
}
MachOper *vecZOper::clone() const {
  return new vecZOper();
}
MachOper *cmpOp_vcmppdOper::clone() const {
  return new cmpOp_vcmppdOper(_c0);
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
