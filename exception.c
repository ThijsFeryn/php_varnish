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
 * $Id: exception.c 316044 2011-09-02 18:08:48Z ab $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_varnish.h"

#include "exception.h"

void
php_varnish_throw_comm_exception(TSRMLS_D)
{
	zend_throw_exception_ex(
		VarnishException_ce,
		PHP_VARNISH_COMM_EXCEPTION TSRMLS_CC,
		"Varnish communication error"
	);  
}

void
php_varnish_throw_ident_vs_host_exception(TSRMLS_D)
{
	zend_throw_exception_ex(
		VarnishException_ce,
		PHP_VARNISH_PARAM_EXCEPTION TSRMLS_CC,
		"Ident vs host/port configuration are mutually exclusive"
	);
}

void
php_varnish_throw_auth_exception(TSRMLS_D)
{
	zend_throw_exception_ex(
		VarnishException_ce,
		PHP_VARNISH_AUTH_EXCEPTION TSRMLS_CC,
		"Not authenticated"
	);
}

void
php_varnish_throw_conn_exception(TSRMLS_D)
{
	zend_throw_exception_ex(
		VarnishException_ce,
		PHP_VARNISH_CONN_EXCEPTION TSRMLS_CC,
		"Not connected to any varnish instance"
	);  
}

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
