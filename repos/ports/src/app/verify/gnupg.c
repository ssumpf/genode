/*
 * \brief  Wrapper for safely calling into GnuPG from C++ code
 * \author Norman Feske
 * \date   2018-01-06
 *
 * We cannot directly include GnuPG's 'main.h' from C++ code. E.g., because
 * the header uses C++ keywords as variable names. By using this wrapper,
 * we keep C++ and C nicely separated.
 */

/*
 * Copyright (C) 2018 Genode Labs GmbH
 *
 * This file is part of the Genode OS framework, which is distributed
 * under the terms of the GNU Affero General Public License version 3.
 */

/* local includes */
#include "gnupg.h"

/* libc includes */
#include <ctype.h>  /* isascii, needed by gnupg headers */

/* GnuPG headers */
#include <gpg.h>
#include <main.h>
#include <options.h>


/*
 * Global variable that is incremented by GnuPG whenever a signature check
 * failed.
 */
int g10_errors_seen = 0;


/*
 * Emulation of a key ring with only one keyblock.
 */
static kbnode_t _keyblock;



/********************************************
 ** Implementation of the public interface **
 ********************************************/

enum Gnupg_verify_result gnupg_verify_detached_signature(char const *pubkey_path,
                                                         char const *data_path,
                                                         char const *sig_path)
{

	/*
	 * Set up the GnuPG control context, which is normally the job of
	 * 'gpg_init_default_ctrl'.
	 */
	struct server_control_s control;
	memset(&control, 0, sizeof(control));
	ctrl_t ctrl = &control;
	ctrl->magic = SERVER_CONTROL_MAGIC;

	/*
	 * Parse pubkey file and store in global _keyblock.
	 */
	gpg_error_t err = read_key_from_file(ctrl, pubkey_path, &_keyblock);
	if (err) {
		if (gpg_err_code(err) == GPG_ERR_NO_PUBKEY)
			return GNUPG_VERIFY_PUBKEY_UNAVAILABLE;

		return GNUPG_VERIFY_PUBKEY_INVALID;
	}

	opt.quiet = 1; /* prevent disclaimer about key compliance */

	/*
	 * Remember 'g10_errors_seen' before calling into GnuPG to obtain the
	 * feedback about the success of the signature verification.
	 */
	int const orig_errors_seen = g10_errors_seen;


	/*
	 * Call into GnuPG to verify the data with a detached signature. The
	 * 'verify_signatures' function indirectly calls 'keydb_*' functions
	 * implemented below.
	 */
	char *file_names[2] = { strdup(sig_path), strdup(data_path) };
	err = verify_signatures(ctrl, 2, file_names);
	for (unsigned i = 0; i < 2; i++)
		free(file_names[i]);

	log_debug(err, orig_errors_seen, g10_errors_seen);

	return !err && (orig_errors_seen == g10_errors_seen) ? GNUPG_VERIFY_OK
	                                                     : GNUPG_VERIFY_SIGNATURE_INVALID;
}

KEYDB_HANDLE keydb_new (void) { return (KEYDB_HANDLE)42; }

gpg_error_t keydb_search (KEYDB_HANDLE hd, KEYDB_SEARCH_DESC *desc, size_t ndesc, size_t *descindex)
{
	/* 
	 * As we only store a global _keyblock, we also use a global handle.
	 * This means, we also search perform the search in the global _keyblock.
	 */

	/* sanity check: check handle */
	if (hd != (KEYDB_HANDLE)42) {
		return -1;
	}

	/* check search modes */
	unsigned n;
	int need_kid = 0;
	for (n=0; n < ndesc; n++)
	{
		if (desc[n].mode == KEYDB_SEARCH_MODE_SHORT_KID
		 || desc[n].mode == KEYDB_SEARCH_MODE_LONG_KID) {
			need_kid = 1;
			break;
		}
	}

	/* we expect to be called with a paritcular key id */
	if (!need_kid) {
		g10_errors_seen += 1;
		return -1;
	}

	/* search for key id in keyblock */
	kbnode_t k;
	for (k = _keyblock; k; k = k->next) {

		u32 aki[2]; /* key id buffer */
		PKT_public_key *pk;

		k->flag &= ~1;

		if (   k->pkt->pkttype == PKT_PUBLIC_KEY
		    || k->pkt->pkttype == PKT_PUBLIC_SUBKEY )
		{
			pk = k->pkt->pkt.public_key;
			keyid_from_pk (pk, aki);
		}
		else {
			continue;
		}

		for (n=0; n < ndesc; n++)
		{
			switch (desc[n].mode)
			{
				case KEYDB_SEARCH_MODE_SHORT_KID:
					if (pk && desc[n].u.kid[1] == aki[1]) {
						k->flag |= 1; /* mark this node (checked by 'finish_lookup') */
						return 0;
					}
					break;
				case KEYDB_SEARCH_MODE_LONG_KID:
					if (pk && desc[n].u.kid[0] == aki[0]
					       && desc[n].u.kid[1] == aki[1]) {
						k->flag |= 1; /* mark this node (checked by 'finish_lookup') */
						return 0;
					}
					break;
				default:
					break;
			}
		}
	}

	g10_errors_seen += 1;
	return gpg_error(GPG_ERR_NO_PUBKEY);
}


gpg_error_t
keydb_get_keyblock (KEYDB_HANDLE hd, KBNODE *ret_kb)
{
	/* sanity check: check handle */
	if (hd != (KEYDB_HANDLE)42) {
		return -1;
	}

	/* 
	 * Copy all nodes in _keyblock as the caller will release these knodes.
	 * It is important to copy the 'flag' attribute as well because this
	 * stores the search result from 'keydb_search'.
	 */

	kbnode_t k;
	*ret_kb = clone_kbnode(_keyblock);
	(*ret_kb)->flag = _keyblock->flag;

	if (_keyblock->next) {
		for (k = _keyblock->next; k; k= k->next) {
			kbnode_t copy = clone_kbnode(k);
			copy->flag = k->flag;
			add_kbnode(*ret_kb, copy);
		}
	}

	return 0;
}
