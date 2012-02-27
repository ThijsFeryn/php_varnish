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
 * $Id: stat.c 317245 2011-09-24 08:59:52Z ab $
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_varnish.h"

#include <varnishapi.h>

#include "varnish_lib.h"
#include "exception.h"


void
php_varnish_stat_obj_destroy(void *obj TSRMLS_DC)
{/*{{{*/
	struct ze_varnish_stat_obj *zvso = (struct ze_varnish_stat_obj *)obj;

	zend_object_std_dtor(&zvso->zo TSRMLS_CC);

	if (zvso->zvc.ident_len > 0) {
		efree(zvso->zvc.ident);
	}

	efree(zvso);
}/*}}}*/

zend_object_value
php_varnish_stat_obj_init(zend_class_entry *ze TSRMLS_DC)
{   /*{{{*/
		zend_object_value ret;
		struct ze_varnish_stat_obj *zvso;
		zval *tmp;

		zvso = (struct ze_varnish_stat_obj*)emalloc(sizeof(struct ze_varnish_stat_obj));
		memset(&zvso->zo, 0, sizeof(zend_object));

		zend_object_std_init(&zvso->zo, ze TSRMLS_CC);
		zend_hash_copy(zvso->zo.properties, &ze->default_properties, (copy_ctor_func_t) zval_add_ref,
						(void *) &tmp, sizeof(zval *));

		zvso->zvc.ident	 = NULL;
		zvso->zvc.ident_len = 0;

		ret.handle = zend_objects_store_put(zvso, NULL,
											(zend_objects_free_object_storage_t) php_varnish_stat_obj_destroy,
											NULL TSRMLS_CC);
		ret.handlers = zend_get_std_object_handlers();
		ret.handlers->clone_obj = NULL;

		return ret;
}/*}}}*/

/* {{{ proto void VarnishStat::__construct(array options)
 *  Varnish admin constructor */
PHP_METHOD(VarnishStat, __construct)
{
	struct ze_varnish_stat_obj *zvso;
	zval *opts = NULL, **ident;

	if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "|a", &opts) == FAILURE) {
		return;
	}

	zvso = (struct ze_varnish_stat_obj *) zend_object_store_get_object(getThis() TSRMLS_CC);

	if (NULL == opts) {
		php_varnish_default_ident(&zvso->zvc.ident, (int*)&zvso->zvc.ident_len);
		return;
	}

	if(zend_hash_find(Z_ARRVAL_P(opts), "ident", sizeof("ident"), (void**)&ident) != FAILURE) {
		convert_to_string(*ident);
		zvso->zvc.ident = estrdup(Z_STRVAL_PP(ident));
		zvso->zvc.ident_len = Z_STRLEN_PP(ident);
	} else {
		php_varnish_default_ident(&zvso->zvc.ident, (int*)&zvso->zvc.ident_len);
	}
}
/* }}} */

/* {{{ proto array VarnishStat::getSnapshot(void)
  Get a statistics snapshot */
PHP_METHOD(VarnishStat, getSnapshot)
{
	struct ze_varnish_stat_obj *zvso;

	if (zend_parse_parameters_none() == FAILURE) {
		return;
	}

	zvso = (struct ze_varnish_stat_obj *) zend_object_store_get_object(getThis() TSRMLS_CC);

	/* Ensure the ctor was called properly and we have an ident to connect to */
	if (!zvso->zvc.ident) {
		zend_throw_exception_ex(
			VarnishException_ce,
			PHP_VARNISH_COMM_EXCEPTION TSRMLS_CC,
			"Missing ident to connect to"
		);
		return;
	}

	array_init(return_value);
	(void)php_varnish_snap_stats(return_value, zvso->zvc.ident TSRMLS_CC);
}
/* }}} */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
