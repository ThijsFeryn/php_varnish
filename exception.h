/*-
 * Copyright (c) 2011 Anatoliy Belsky
 * All rights reserved.
 *
 * Author: Anatoliy Belsky <ab@php.net>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *	notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *	notice, this list of conditions and the following disclaimer in the
 *	documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * $Id: exception.h 317557 2011-09-30 21:34:45Z ab $
 */

#include "varnish_lib.h"

#ifndef PHP_VARNISH_EXCEPTION_H
#define PHP_VARNISH_EXCEPTION_H

enum {
	PHP_VARNISH_COMM_EXCEPTION = PHP_VARNISH_STATUS_COMMS,
	PHP_VARNISH_UNKNOWN_EXCEPTION = PHP_VARNISH_STATUS_UNKNOWN,
	PHP_VARNISH_UNIMPL_EXCEPTION = PHP_VARNISH_STATUS_UNIMPL,
	PHP_VARNISH_TOOFEW_EXCEPTION = PHP_VARNISH_STATUS_TOOFEW,
	PHP_VARNISH_TOOMANY_EXCEPTION = PHP_VARNISH_STATUS_TOOMANY,
	PHP_VARNISH_CANT_EXCEPTION = PHP_VARNISH_STATUS_CANT,
	PHP_VARNISH_PARAM_EXCEPTION = PHP_VARNISH_STATUS_PARAM,
	PHP_VARNISH_AUTH_EXCEPTION = PHP_VARNISH_STATUS_AUTH,
	PHP_VARNISH_SOCK_EXCEPTION = 1000,
	PHP_VARNISH_CONN_EXCEPTION,
	PHP_VARNISH_HANDSHAKE_EXCEPTION,
	PHP_VARNISH_TMO_EXCEPTION,
	PHP_VARNISH_SHM_EXCEPTION,
	PHP_VARNISH_COMPAT_EXCEPTION,
};

void
php_varnish_throw_comm_exception(TSRMLS_D);

void
php_varnish_throw_ident_vs_host_exception(TSRMLS_D);

void
php_varnish_throw_auth_exception(TSRMLS_D);

void
php_varnish_throw_conn_exception(TSRMLS_D);

#endif	/* PHP_VARNISH_EXCEPTION_H */



/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
