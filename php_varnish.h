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
 * $Id: php_varnish.h 317840 2011-10-06 18:08:16Z ab $
 */

#ifndef PHP_VARNISH_H
#define PHP_VARNISH_H

extern zend_module_entry varnish_module_entry;
#define phpext_varnish_ptr &varnish_module_entry

#ifdef PHP_WIN32
#	define PHP_VARNISH_API __declspec(dllexport)
#elif defined(__GNUC__) && __GNUC__ >= 4
#	define PHP_VARNISH_API __attribute__ ((visibility("default")))
#else
#	define PHP_VARNISH_API
#endif

#ifdef ZTS
#include "TSRM.h"
#endif

#include "varnishapi.h"

/*#define PHP_VARNISH_DEBUG*/

#define PHP_VARNISH_EXT_VERSION "0.9.2"

PHP_MINIT_FUNCTION(varnish);
PHP_MSHUTDOWN_FUNCTION(varnish);
PHP_RINIT_FUNCTION(varnish);
PHP_RSHUTDOWN_FUNCTION(varnish);
PHP_MINFO_FUNCTION(varnish);

PHP_METHOD(VarnishAdmin, __construct);
PHP_METHOD(VarnishAdmin, connect);
PHP_METHOD(VarnishAdmin, auth);
PHP_METHOD(VarnishAdmin, getParams);
PHP_METHOD(VarnishAdmin, setParam);
PHP_METHOD(VarnishAdmin, stop);
PHP_METHOD(VarnishAdmin, start);
PHP_METHOD(VarnishAdmin, banUrl);
PHP_METHOD(VarnishAdmin, ban);
PHP_METHOD(VarnishAdmin, isRunning);
PHP_METHOD(VarnishAdmin, getPanic);
PHP_METHOD(VarnishAdmin, clearPanic);
PHP_METHOD(VarnishAdmin, setHost);
PHP_METHOD(VarnishAdmin, setIdent);
PHP_METHOD(VarnishAdmin, setPort);
PHP_METHOD(VarnishAdmin, setTimeout);
PHP_METHOD(VarnishAdmin, setSecret);
PHP_METHOD(VarnishAdmin, setCompat);

PHP_METHOD(VarnishStat, __construct);
PHP_METHOD(VarnishStat, getSnapshot);

PHP_METHOD(VarnishLog, __construct);
PHP_METHOD(VarnishLog, getLine);
PHP_METHOD(VarnishLog, getTagName);

/*ZEND_BEGIN_MODULE_GLOBALS(varnish)
ZEND_END_MODULE_GLOBALS(varnish)*/

#ifdef ZTS
#define VARNISH_G(v) TSRMG(varnish_globals_id, zend_varnish_globals *, v)
#else
#define VARNISH_G(v) (varnish_globals.v)
#endif

/*ZEND_EXTERN_MODULE_GLOBALS(varnish)*/

extern zend_class_entry *VarnishException_ce;

extern zend_object_value php_varnish_adm_obj_init(zend_class_entry *ze TSRMLS_DC);
extern zend_object_value php_varnish_stat_obj_init(zend_class_entry *ze TSRMLS_DC);
extern zend_object_value php_varnish_log_obj_init(zend_class_entry *ze TSRMLS_DC);

struct ze_varnish_conn {
	char *host;
	long host_len;
	int port;
	char *secret;
	long secret_len;
	int timeout;
	int sock;
	char *ident;
	long ident_len;
	int authok;
};

struct ze_varnish_adm_obj {
	zend_object zo;
	struct ze_varnish_conn zvc;
	int status;
	int compat;
};

struct ze_varnish_stat_obj {
	zend_object zo;
	struct ze_varnish_conn zvc;
};

struct ze_varnish_log_obj {
	zend_object zo;
	struct ze_varnish_conn zvc;
	struct VSM_data *vd;
};

#endif	/* PHP_VARNISH_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
