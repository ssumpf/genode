#line 1 "ad_x86_expand.cpp"
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

// Register masks, one for each register class.
const RegMask _NO_REG_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _ANY_REG_WITH_RBP_mask( 0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _ANY_REG_NO_RBP_mask( 0xff3fffff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_REG_WITH_RBP_mask( 0xffffcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_PTR_REG_WITH_RBP_mask( 0xffffcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _PTR_REG_NO_RBP_mask( 0xf3ffcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_PTR_REG_NO_RBP_mask( 0xf3ffcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _PTR_NO_RAX_REG_WITH_RBP_mask( 0xfcffcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_NO_RAX_REG_NO_RBP_mask( 0xf0ffcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_NO_RAX_RBX_REG_WITH_RBP_mask( 0xfcfccff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_NO_RAX_RBX_REG_NO_RBP_mask( 0xf0fccff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_RAX_REG_mask( 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_RBX_REG_mask( 0x3000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_RSI_REG_mask( 0xc0000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_RDI_REG_mask( 0xc000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_RSP_REG_mask( 0xc0000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _PTR_R15_REG_mask( 0x30000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LONG_REG_WITH_RBP_mask( 0xffffcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_LONG_REG_WITH_RBP_mask( 0xffffcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _LONG_REG_NO_RBP_mask( 0xf3ffcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_LONG_REG_NO_RBP_mask( 0xf3ffcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _LONG_NO_RAX_RDX_REG_WITH_RBP_mask( 0xfccfcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LONG_NO_RAX_RDX_REG_NO_RBP_mask( 0xf0cfcff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LONG_NO_RCX_REG_WITH_RBP_mask( 0xffff0ff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LONG_NO_RCX_REG_NO_RBP_mask( 0xf3ff0ff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LONG_RAX_REG_mask( 0x300000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LONG_RCX_REG_mask( 0xc00, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _LONG_RDX_REG_mask( 0x30000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_REG_WITH_RBP_mask( 0x5555455, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_INT_REG_WITH_RBP_mask( 0x5555455, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _INT_REG_NO_RBP_mask( 0x5155455, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_INT_REG_NO_RBP_mask( 0x5155455, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _INT_NO_RCX_REG_WITH_RBP_mask( 0x5555055, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_NO_RCX_REG_NO_RBP_mask( 0x5155055, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_NO_RAX_RDX_REG_WITH_RBP_mask( 0x5445455, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_NO_RAX_RDX_REG_NO_RBP_mask( 0x5045455, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_RAX_REG_mask( 0x100000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_RBX_REG_mask( 0x1000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_RCX_REG_mask( 0x400, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_RDX_REG_mask( 0x10000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_RDI_REG_mask( 0x4000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _INT_FLAGS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1, 0x0, 0x0, 0x0, 0x0 );
const RegMask _FLOAT_REG_LEGACY_mask( 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_FLOAT_REG_LEGACY_mask( 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _FLOAT_REG_EVEX_mask( 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_FLOAT_REG_EVEX_mask( 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _DOUBLE_REG_LEGACY_mask( 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_DOUBLE_REG_LEGACY_mask( 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _DOUBLE_REG_EVEX_mask( 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_DOUBLE_REG_EVEX_mask( 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
const RegMask _VECTORS_REG_LEGACY_mask( 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORS_REG_EVEX_mask( 0x0, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x10001, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORD_REG_LEGACY_mask( 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORD_REG_EVEX_mask( 0x0, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x30003, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORX_REG_LEGACY_mask( 0x0, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORX_REG_EVEX_mask( 0x0, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0xf000f, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORY_REG_LEGACY_mask( 0x0, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORY_REG_EVEX_mask( 0x0, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0xff00ff, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _VECTORZ_REG_mask( 0x0, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_SLOTS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 );
const RegMask _STACK_OR_STACK_SLOTS_mask( 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xffffff00, 0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff );
MachNode* loadUB2L_immINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadS2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// mem
    unsigned num2 = opnd_array(2)->num_edges(); 	// twentyfour
    unsigned num3 = opnd_array(3)->num_edges(); 	// twentyfour
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* loadUS2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// mem
    unsigned num2 = opnd_array(2)->num_edges(); 	// twentyfour
    unsigned num3 = opnd_array(3)->num_edges(); 	// twentyfour
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* loadUS2L_immINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadI2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// mem
    unsigned num2 = opnd_array(2)->num_edges(); 	// twentyfour
    unsigned num3 = opnd_array(3)->num_edges(); 	// twentyfour
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* loadI2SNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// mem
    unsigned num2 = opnd_array(2)->num_edges(); 	// sixteen
    unsigned num3 = opnd_array(3)->num_edges(); 	// sixteen
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* loadI2L_immU31Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConI0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConL0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConP0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConP31Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* loadConN0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* loadConDNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* bytes_reverse_unsigned_shortNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* bytes_reverse_shortNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosI_bsrNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countLeadingZerosL_bsrNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosI_bsfNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* countTrailingZerosL_bsfNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* popCountINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* popCountI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* popCountLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* popCountL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* membar_volatileNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encodeHeapOopNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encodeHeapOop_not_nullNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeHeapOopNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeHeapOop_not_nullNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encodeKlass_not_nullNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decodeKlass_not_nullNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* jumpXtnd_offsetNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dest
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* jumpXtnd_addrNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dest
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* jumpXtndNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dest
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* cmovI_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  cmovI_regUNode *n0 = new cmovI_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovI_memUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  if (mem == (Node*)1) {
    idx0--; // Adjust base because memory edge hasn't been inserted yet
  }
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  cmovI_memUNode *n0 = new cmovI_memUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  if (mem != (Node*)1) {
    n0->add_req(_in[1]);	// Add memory edge
  }
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovN_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  cmovN_regUNode *n0 = new cmovN_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGN));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovP_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  cmovP_regUNode *n0 = new cmovP_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGP));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovL_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  cmovL_regUNode *n0 = new cmovL_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovL_memUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  if (mem == (Node*)1) {
    idx0--; // Adjust base because memory edge hasn't been inserted yet
  }
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  cmovL_memUNode *n0 = new cmovL_memUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  if (mem != (Node*)1) {
    n0->add_req(_in[1]);	// Add memory edge
  }
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovF_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  cmovF_regUNode *n0 = new cmovF_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(REGF));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* cmovD_regUCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  cmovD_regUNode *n0 = new cmovD_regUNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(REGD));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // cop
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // cr
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  n0->set_opnd_array(3, opnd_array(3)->clone()); // dst
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  tmp3 = n0;
  n0->set_opnd_array(4, opnd_array(4)->clone()); // src
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* addI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addI_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* addI_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* addI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* incI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* incI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* decI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* addL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addL_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* addL_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* addL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* incL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* incL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* decL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* decL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* addP_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* addP_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* storeIConditionalNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);

  return this;
}

MachNode* storeLConditionalNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapPNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapP_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapL_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapI_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapB_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapS_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegN );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndSwapN_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL oldval
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegN );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangeNNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* compareAndExchangePNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddB_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddS_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddSNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddI_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddINode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddL_no_resNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xaddLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subI_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* subI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* subL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* subL_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* subL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* subP_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* negI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* negI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* negL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* negL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* mulI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulI_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulI_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulL_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulL_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mulHiL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rax
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rdx
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rdx
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RDX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divModI_rReg_divmodNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divModL_rReg_divmodNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* mul_hiNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rax
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarL_rReg_63Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarL_rReg_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* divL_10Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rax_RegLOper();
  MachOper *op1 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  MachNode *tmp4 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  loadConL_0x6666666666666667Node *n0 = new loadConL_0x6666666666666667Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  tmp3 = n0;
  result = n0->Expand( state, proj_list, mem );

  mul_hiNode *n1 = new mul_hiNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(RDX_REGL));
  tmp0 = n1;
  n1->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  n1->set_opnd_array(2, op0->clone()); // rax
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );

  sarL_rReg_63Node *n2 = new sarL_rReg_63Node();
  n2->add_req(_in[0]);
  n2->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n2->set_opnd_array(1, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n2->add_req(_in[i + idx1]);
    }
  }
  else n2->add_req(tmp1);
  tmp1 = n2;
  result = n2->Expand( state, proj_list, mem );

  sarL_rReg_2Node *n3 = new sarL_rReg_2Node();
  n3->add_req(_in[0]);
  n3->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n3->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n3->add_req(_in[i + idx0]);
    }
  }
  else n3->add_req(tmp0);
  tmp0 = n3;
  result = n3->Expand( state, proj_list, mem );

  subL_rRegNode *n4 = new subL_rRegNode();
  n4->add_req(_in[0]);
  n4->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n4->set_opnd_array(1, opnd_array(0)->clone()); // dst
  if(tmp0 == this) {
    for(unsigned i = 0; i < num0; i++) {
      n4->add_req(_in[i + idx0]);
    }
  }
  else n4->add_req(tmp0);
  tmp0 = n4;
  n4->set_opnd_array(2, opnd_array(1)->clone()); // src
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n4->add_req(_in[i + idx1]);
    }
  }
  else n4->add_req(tmp1);
  result = n4->Expand( state, proj_list, mem );


  return result;
}

MachNode* modI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rax
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* modL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rax
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salI_rReg_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salI_mem_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* salI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* salI_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salI_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* sarI_rReg_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarI_mem_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* sarI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* sarI_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarI_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* shrI_rReg_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* shrI_mem_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* shrI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* shrI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* shrI_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* shrI_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* salL_rReg_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salL_mem_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* salL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* salL_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* salL_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* sarL_rReg_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarL_mem_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* sarL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* sarL_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* sarL_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* shrL_rReg_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* shrL_mem_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* shrL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* shrL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* shrL_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* shrL_mem_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// shift
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // shift
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* i2bNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// twentyfour
    unsigned num3 = opnd_array(3)->num_edges(); 	// twentyfour
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* i2sNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// sixteen
    unsigned num3 = opnd_array(3)->num_edges(); 	// sixteen
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* rolI_rReg_imm1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rolI_rReg_imm8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rolI_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rolI_rReg_i1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rolI_rReg_imm1Node *n0 = new rolI_rReg_imm1Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolI_rReg_i1_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rolI_rReg_imm1Node *n0 = new rolI_rReg_imm1Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolI_rReg_i8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rolI_rReg_imm8Node *n0 = new rolI_rReg_imm8Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // lshift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolI_rReg_i8_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rolI_rReg_imm8Node *n0 = new rolI_rReg_imm8Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(4)->clone()); // lshift
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolI_rReg_Var_C0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rolI_rReg_CLNode *n0 = new rolI_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // shift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolI_rReg_Var_C0_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rolI_rReg_CLNode *n0 = new rolI_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(3)->clone()); // shift
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolI_rReg_Var_C32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rolI_rReg_CLNode *n0 = new rolI_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // shift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolI_rReg_Var_C32_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rolI_rReg_CLNode *n0 = new rolI_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(3)->clone()); // shift
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorI_rReg_imm1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rorI_rReg_imm8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rorI_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rorI_rReg_i1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rorI_rReg_imm1Node *n0 = new rorI_rReg_imm1Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorI_rReg_i1_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rorI_rReg_imm1Node *n0 = new rorI_rReg_imm1Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorI_rReg_i8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rorI_rReg_imm8Node *n0 = new rorI_rReg_imm8Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // rshift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorI_rReg_i8_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rorI_rReg_imm8Node *n0 = new rorI_rReg_imm8Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(4)->clone()); // rshift
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorI_rReg_Var_C0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rorI_rReg_CLNode *n0 = new rorI_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // shift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorI_rReg_Var_C0_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rorI_rReg_CLNode *n0 = new rorI_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(3)->clone()); // shift
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorI_rReg_Var_C32Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rorI_rReg_CLNode *n0 = new rorI_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // shift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorI_rReg_Var_C32_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rorI_rReg_CLNode *n0 = new rorI_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGI));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(3)->clone()); // shift
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolL_rReg_imm1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rolL_rReg_imm8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rolL_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rolL_rReg_i1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rolL_rReg_imm1Node *n0 = new rolL_rReg_imm1Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolL_rReg_i1_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rolL_rReg_imm1Node *n0 = new rolL_rReg_imm1Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolL_rReg_i8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rolL_rReg_imm8Node *n0 = new rolL_rReg_imm8Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // lshift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolL_rReg_i8_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rolL_rReg_imm8Node *n0 = new rolL_rReg_imm8Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(4)->clone()); // lshift
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolL_rReg_Var_C0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rolL_rReg_CLNode *n0 = new rolL_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // shift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolL_rReg_Var_C0_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rolL_rReg_CLNode *n0 = new rolL_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(3)->clone()); // shift
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolL_rReg_Var_C64Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rolL_rReg_CLNode *n0 = new rolL_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // shift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rolL_rReg_Var_C64_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rolL_rReg_CLNode *n0 = new rolL_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(3)->clone()); // shift
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorL_rReg_imm1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rorL_rReg_imm8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rorL_rReg_CLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rorL_rReg_i1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rorL_rReg_imm1Node *n0 = new rorL_rReg_imm1Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorL_rReg_i1_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rorL_rReg_imm1Node *n0 = new rorL_rReg_imm1Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorL_rReg_i8Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rorL_rReg_imm8Node *n0 = new rorL_rReg_imm8Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // rshift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorL_rReg_i8_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  MachNode *result = NULL;

  rorL_rReg_imm8Node *n0 = new rorL_rReg_imm8Node();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RREGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(4)->clone()); // rshift
  if(tmp4 == this) {
    for(unsigned i = 0; i < num4; i++) {
      n0->add_req(_in[i + idx4]);
    }
  }
  else n0->add_req(tmp4);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorL_rReg_Var_C0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rorL_rReg_CLNode *n0 = new rorL_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // shift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorL_rReg_Var_C0_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rorL_rReg_CLNode *n0 = new rorL_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(3)->clone()); // shift
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorL_rReg_Var_C64Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rorL_rReg_CLNode *n0 = new rorL_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(2)->clone()); // shift
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* rorL_rReg_Var_C64_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = this;
  MachNode *tmp4 = this;
  MachNode *tmp5 = this;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned num3 = opnd_array(3)->num_edges();
  unsigned num4 = opnd_array(4)->num_edges();
  unsigned num5 = opnd_array(5)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  unsigned idx4 = idx3 + num3;
  unsigned idx5 = idx4 + num4;
  unsigned idx6 = idx5 + num5;
  MachNode *result = NULL;

  rorL_rReg_CLNode *n0 = new rorL_rReg_CLNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(NO_RCX_REGL));
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  tmp1 = n0;
  n0->set_opnd_array(2, opnd_array(3)->clone()); // shift
  if(tmp3 == this) {
    for(unsigned i = 0; i < num3; i++) {
      n0->add_req(_in[i + idx3]);
    }
  }
  else n0->add_req(tmp3);
  result = n0->Expand( state, proj_list, mem );


  return result;
}

MachNode* andI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andI_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* andI_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* andI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* andnI_rReg_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnI_rReg_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnI_rReg_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnI_rReg_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* blsiI_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// imm_zero
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsiI_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// imm_zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsiI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// imm_zero
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsiI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// imm_zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsmskI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsmskI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsmskI_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsmskI_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsrI_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsrI_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsrI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsrI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* orI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orI_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* orI_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* orI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* xorI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorI_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorI_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorI_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* xorI_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* xorI_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* andL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andL_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* andL_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* andL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* andnL_rReg_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnL_rReg_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnL_rReg_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* andnL_rReg_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* blsiL_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// imm_zero
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsiL_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// imm_zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsiL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// imm_zero
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsiL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// imm_zero
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsmskL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsmskL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsmskL_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsmskL_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsrL_rReg_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsrL_rReg_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsrL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// minus_1
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* blsrL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// src
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// minus_1
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // minus_1
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* orL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_rReg_castP2XNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_rReg_castP2X_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* orL_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* orL_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* orL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* xorL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorL_rReg_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorL_rReg_mem_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* xorL_mem_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* xorL_mem_rReg_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* xorL_mem_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 4) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// dst
    unsigned num3 = opnd_array(3)->num_edges(); 	// src
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    set_opnd_array(2, opnd_array(3)->clone()); // src
    for (unsigned i = 0; i < num3; i++) {
      set_req(i + idx2, _in[i + idx3]);
    }
    num2 = num3;
    idx3 = idx2 + num2;
    for (int i = idx4 - 1; i >= (int)idx3; i--) {
      del_req(i);
    }
    _num_opnds = 3;
  } else {
    assert(_num_opnds == 3, "There should be either 3 or 4 operands.");
  }

  return this;
}

MachNode* convI2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convP2BNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpLTMaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpLTMask0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cadd_cmpLTMaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// p
    unsigned num2 = opnd_array(2)->num_edges(); 	// q
    unsigned num3 = opnd_array(3)->num_edges(); 	// y
    unsigned num4 = opnd_array(4)->num_edges(); 	// p
    unsigned num5 = opnd_array(5)->num_edges(); 	// q
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    for (int i = idx6 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 6 operands.");
  }

  return this;
}

MachNode* cadd_cmpLTMask_1Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// p
    unsigned num2 = opnd_array(2)->num_edges(); 	// q
    unsigned num3 = opnd_array(3)->num_edges(); 	// p
    unsigned num4 = opnd_array(4)->num_edges(); 	// q
    unsigned num5 = opnd_array(5)->num_edges(); 	// y
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(5)->clone()); // y
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx3, _in[i + idx5]);
    }
    num3 = num5;
    idx4 = idx3 + num3;
    for (int i = idx6 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 6 operands.");
  }

  return this;
}

MachNode* cadd_cmpLTMask_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// y
    unsigned num2 = opnd_array(2)->num_edges(); 	// p
    unsigned num3 = opnd_array(3)->num_edges(); 	// q
    unsigned num4 = opnd_array(4)->num_edges(); 	// p
    unsigned num5 = opnd_array(5)->num_edges(); 	// q
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    for (int i = idx6 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 6 operands.");
  }

  return this;
}

MachNode* cadd_cmpLTMask_2Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// p
    unsigned num2 = opnd_array(2)->num_edges(); 	// q
    unsigned num3 = opnd_array(3)->num_edges(); 	// y
    unsigned num4 = opnd_array(4)->num_edges(); 	// p
    unsigned num5 = opnd_array(5)->num_edges(); 	// q
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    for (int i = idx6 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 6 operands.");
  }

  return this;
}

MachNode* and_cmpLTMaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* and_cmpLTMask_0Node::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpF_cc_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* cmpF_cc_immCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* cmpD_cc_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* cmpD_cc_immCFNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* cmpF_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpF_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* cmpD_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpD_memNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* cmpD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* convF2I_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convF2L_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convD2I_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* convD2L_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rep_stosNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RCX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL base
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL zero
  kill = new MachProjNode( this, 3, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* rep_stos_largeNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cnt
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RCX_REG_mask()), Op_RegL );
  proj_list.push(kill);
  // DEF/KILL base
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL zero
  kill = new MachProjNode( this, 3, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareLUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compareULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexof_conLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexof_conUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexof_conULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexofLNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexofUNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexofULNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 3, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt2
  kill = new MachProjNode( this, 4, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP vec
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL tmp
  kill = new MachProjNode( this, 5, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 6, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_indexofU_charNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt1
  kill = new MachProjNode( this, 2, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL ch
  kill = new MachProjNode( this, 3, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP vec1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vec2
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP vec3
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(RCX_REGI));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_equalsNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL str1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL str2
  kill = new MachProjNode( this, 2, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL cnt
  kill = new MachProjNode( this, 3, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 4, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsBNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ary2
  kill = new MachProjNode( this, 2, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 3, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp4
  kill = new MachProjNode( this, 4, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* array_equalsCNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL ary2
  kill = new MachProjNode( this, 2, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 3, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL tmp4
  kill = new MachProjNode( this, 4, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* has_negativesNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL ary1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 2, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL tmp3
  kill = new MachProjNode( this, 3, (INT_RBX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_compressNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL tmp5
  kill = new MachProjNode( this, 4, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* string_inflateNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(RCX_REGI));
  add_req(def);
  // DEF/KILL cr
  kill = new MachProjNode( this, 4, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* encode_iso_arrayNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL src
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RSI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL dst
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // DEF/KILL len
  kill = new MachProjNode( this, 3, (INT_RDX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // TEMP tmp1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp4
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // DEF/KILL tmp5
  kill = new MachProjNode( this, 4, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 5, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* overflowAddI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);

  return this;
}

MachNode* overflowAddI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);

  return this;
}

MachNode* overflowAddL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);

  return this;
}

MachNode* overflowAddL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);

  return this;
}

MachNode* overflowNegI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op2
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);

  return this;
}

MachNode* overflowNegL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op2
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);

  return this;
}

MachNode* overflowMulI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RAX_REG_mask()), Op_RegI );
  proj_list.push(kill);

  return this;
}

MachNode* overflowMulI_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* overflowMulL_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL op1
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (LONG_RAX_REG_mask()), Op_RegL );
  proj_list.push(kill);

  return this;
}

MachNode* overflowMulL_rReg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGL));
  add_req(def);

  return this;
}

MachNode* cmpL3_reg_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL flags
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* minI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  compI_rRegNode *n0 = new compI_rRegNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_gNode *n1 = new cmovI_reg_gNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n1->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  tmp1 = n1;
  n1->set_opnd_array(2, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(3, op0->clone()); // cr
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* maxI_rRegNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  MachOper *op0 = new rFlagsRegOper();
  MachNode *tmp0 = this;
  MachNode *tmp1 = this;
  MachNode *tmp2 = this;
  MachNode *tmp3 = NULL;
  unsigned num0 = 0;
  unsigned num1 = opnd_array(1)->num_edges();
  unsigned num2 = opnd_array(2)->num_edges();
  unsigned idx0 = oper_input_base();
  unsigned idx1 = idx0 + num0;
  unsigned idx2 = idx1 + num1;
  unsigned idx3 = idx2 + num2;
  MachNode *result = NULL;

  compI_rRegNode *n0 = new compI_rRegNode();
  n0->add_req(_in[0]);
  n0->set_opnd_array(0, state->MachOperGenerator(RFLAGSREG));
  tmp3 = n0;
  n0->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n0->add_req(_in[i + idx1]);
    }
  }
  else n0->add_req(tmp1);
  n0->set_opnd_array(2, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n0->add_req(_in[i + idx2]);
    }
  }
  else n0->add_req(tmp2);
  result = n0->Expand( state, proj_list, mem );

  cmovI_reg_lNode *n1 = new cmovI_reg_lNode();
  n1->add_req(_in[0]);
  n1->set_opnd_array(0, state->MachOperGenerator(RREGI));
  n1->set_opnd_array(1, opnd_array(1)->clone()); // dst
  if(tmp1 == this) {
    for(unsigned i = 0; i < num1; i++) {
      n1->add_req(_in[i + idx1]);
    }
  }
  else n1->add_req(tmp1);
  tmp1 = n1;
  n1->set_opnd_array(2, opnd_array(2)->clone()); // src
  if(tmp2 == this) {
    for(unsigned i = 0; i < num2; i++) {
      n1->add_req(_in[i + idx2]);
    }
  }
  else n1->add_req(tmp2);
  n1->set_opnd_array(3, op0->clone()); // cr
  if(tmp3 != NULL)
    n1->add_req(tmp3);
  result = n1->Expand( state, proj_list, mem );


  return result;
}

MachNode* partialSubtypeCheckNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rcx
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL cr
  kill = new MachProjNode( this, 2, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* partialSubtypeCheck_vs_ZeroNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL rcx
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_RCX_REG_mask()), Op_RegI );
  proj_list.push(kill);
  // DEF/KILL result
  kill = new MachProjNode( this, 2, (PTR_RDI_REG_mask()), Op_RegP );
  proj_list.push(kill);

  return this;
}

MachNode* cmpFastLockRTMNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL box
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RBX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RAX_REGI));
  add_req(def);
  // TEMP scr
  def = new MachTempNode(state->MachOperGenerator(RDX_REGI));
  add_req(def);
  // TEMP cx1
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);
  // TEMP cx2
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* cmpFastLockNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL box
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RBX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RAX_REGI));
  add_req(def);
  // TEMP scr
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* cmpFastUnlockNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL box
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (PTR_RAX_REG_mask()), Op_RegP );
  proj_list.push(kill);
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGP));
  add_req(def);

  return this;
}

MachNode* safePoint_pollNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* safePoint_poll_farNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // DEF/KILL cr
  MachProjNode *kill;
  kill = new MachProjNode( this, 1, (INT_FLAGS_mask()), Op_RegFlags );
  proj_list.push(kill);

  return this;
}

MachNode* setMaskNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(RREGI));
  add_req(def);

  return this;
}

MachNode* addF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* addF_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* addD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* addD_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* subF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* subF_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* subD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* subD_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* mulF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* mulF_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* mulD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* mulD_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* divF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* divF_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* divD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* divD_reg_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* absF_reg_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src2
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* absD_reg_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src2
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);

  return this;
}

MachNode* sqrtF_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* sqrtD_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl16B_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl32B_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl8S_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl16S_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl4I_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl8I_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl4L_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl4B_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl8B_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl2S_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl4S_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl2I_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl2L_immNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl16B_imm_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl32B_imm_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl64B_imm_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl8S_imm_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl16S_imm_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl32S_imm_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl4I_imm_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl8I_imm_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl16I_imm_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl4L_imm_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* Repl8L_imm_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  add_req(C->mach_constant_base_node());

  return this;
}

MachNode* rsadd2I_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvadd2I_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvadd2I_reduction_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rsadd4I_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvadd4I_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvadd4I_reduction_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvadd8I_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvadd8I_reduction_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvadd16I_reduction_reg_evexNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvadd2L_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvadd4L_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvadd8L_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rsadd2F_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rvadd2F_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rsadd4F_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rvadd4F_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* radd8F_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* radd16F_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* rsadd2D_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rvadd2D_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rvadd4D_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* rvadd8D_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* rsmul2I_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvmul2I_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rsmul4I_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvmul4I_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvmul8I_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvmul16I_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp3
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvmul2L_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvmul4L_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rvmul8L_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP tmp
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);

  return this;
}

MachNode* rsmul2F_reductionNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rvmul2F_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rsmul4F_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rvmul4F_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rvmul8F_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* rvmul16F_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGF));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* rsmul2D_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rvmul2D_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 5) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    for (int i = idx5 - 1; i >= (int)idx4; i--) {
      del_req(i);
    }
    _num_opnds = 4;
  } else {
    assert(_num_opnds == 4, "There should be either 4 or 5 operands.");
  }

  return this;
}

MachNode* rvmul4D_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* rvmul8D_reduction_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // TEMP tmp2
  def = new MachTempNode(state->MachOperGenerator(REGD));
  add_req(def);
  // Remove duplicated operands and inputs which use the same name.
  if (num_opnds() == 6) {
    unsigned num0 = 0;
    unsigned num1 = opnd_array(1)->num_edges(); 	// dst
    unsigned num2 = opnd_array(2)->num_edges(); 	// src2
    unsigned num3 = opnd_array(3)->num_edges(); 	// dst
    unsigned num4 = opnd_array(4)->num_edges(); 	// tmp
    unsigned num5 = opnd_array(5)->num_edges(); 	// tmp2
    unsigned idx0 = oper_input_base();
    unsigned idx1 = idx0 + num0;
    unsigned idx2 = idx1 + num1;
    unsigned idx3 = idx2 + num2;
    unsigned idx4 = idx3 + num3;
    unsigned idx5 = idx4 + num4;
    unsigned idx6 = idx5 + num5;
    set_opnd_array(3, opnd_array(4)->clone()); // tmp
    for (unsigned i = 0; i < num4; i++) {
      set_req(i + idx3, _in[i + idx4]);
    }
    num3 = num4;
    idx4 = idx3 + num3;
    set_opnd_array(4, opnd_array(5)->clone()); // tmp2
    for (unsigned i = 0; i < num5; i++) {
      set_req(i + idx4, _in[i + idx5]);
    }
    num4 = num5;
    idx5 = idx4 + num4;
    for (int i = idx6 - 1; i >= (int)idx5; i--) {
      del_req(i);
    }
    _num_opnds = 5;
  } else {
    assert(_num_opnds == 5, "There should be either 5 or 6 operands.");
  }

  return this;
}

MachNode* vadd4B_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vadd4B_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vadd8B_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vadd8B_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vadd16B_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vadd16B_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vadd32B_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vadd32B_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vadd2S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vadd2S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vadd4S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vadd4S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vadd8S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vadd8S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vadd16S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vadd16S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vsub4B_reg_exex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vsub4B_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vsub8B_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsub8B_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsub16B_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsub16B_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsub32B_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vsub32B_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vsub2S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vsub2S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vsub4S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsub4S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsub8S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsub8S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsub16S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vsub16S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vmul2S_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vmul2S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vmul4S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vmul4S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vmul8S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vmul8S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vmul16S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src1
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vmul16S_mem_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vcmov4D_regNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP dst
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vsll2S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vsll2S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vsll4S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsll4S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsll8S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsll8S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsll16S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vsll16S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vsrl2S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vsrl2S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vsrl4S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsrl4S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsrl8S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsrl8S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsrl16S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vsrl16S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vsra2S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vsra2S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECS));
  add_req(def);

  return this;
}

MachNode* vsra4S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsra4S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECD));
  add_req(def);

  return this;
}

MachNode* vsra8S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsra8S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECX));
  add_req(def);

  return this;
}

MachNode* vsra16S_reg_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
}

MachNode* vsra16S_reg_imm_evex_specialNode::Expand(State* state, Node_List& proj_list, Node* mem) {
  Compile* C = Compile::current();
  // Add projection edges for additional defs or kills
  // TEMP src
  MachTempNode *def;
  def = new MachTempNode(state->MachOperGenerator(VECY));
  add_req(def);

  return this;
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
