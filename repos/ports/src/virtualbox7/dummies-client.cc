/*
 * \brief  Dummy implementations of symbols needed by virtualbox-client
 * \author Sebastian Sumpf
 * \date   2025-06-20
 */

/*
 * Copyright (C) 2025 Genode Labs GmbH
 *
 * This file is distributed under the terms of the GNU General Public License
 * version 2.
 */

#include "stub_macros.h"

/* NvramStoreImpl.cpp */
#include "NvramStoreImpl.h"

static bool const debug = true;

ClientNvramStore::ClientNvramStore() STOP
ClientNvramStore::~ClientNvramStore() STOP

void ClientNvramStore::FinalRelease() STOP
HRESULT ClientNvramStore::FinalConstruct() STOP

HRESULT ClientNvramStore::init(Console *, const com::Utf8Str &) STOP
void ClientNvramStore::uninit() STOP;

HRESULT ClientNvramStore::initUefiVariableStore(ULONG) STOP
HRESULT ClientNvramStore::getNonVolatileStorageFile(com::Utf8Str &) STOP
HRESULT ClientNvramStore::getUefiVariableStore(ComPtr<IUefiVariableStore> &) STOP
HRESULT ClientNvramStore::getKeyId(com::Utf8Str &) STOP
HRESULT ClientNvramStore::getKeyStore(com::Utf8Str &) STOP
