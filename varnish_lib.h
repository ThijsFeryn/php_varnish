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
 * $Id: varnish_lib.h 317558 2011-09-30 22:09:35Z ab $
 */

#ifndef PHP_VARNISH_LIB_H
#define PHP_VARNISH_LIB_H

#include <varnishapi.h>
#include <vcli.h>
#include <vsl.h>

/* get socket connection */
int
php_varnish_sock(const char *addr, int port, int timeout, int *status TSRMLS_DC);
int
php_varnish_sock_ident(const char *ident, char **addr, int *addr_len, int *port, int timeout, int *status TSRMLS_DC);

void
php_varnish_default_ident(char **ident, int *ident_len);

/* authenticate with the varnish instance running under the given socket */
int
php_varnish_auth(int sock, char *secret, int secret_len, int *status, int timeout TSRMLS_DC);
int
php_varnish_auth_ident(int sock, const char *ident, int timeout, int *status TSRMLS_DC);

int
php_varnish_get_params(int sock, int *status, zval *storage, int timeout TSRMLS_DC);

int
php_varnish_set_param(int sock, int *status, char *key, int key_len, char *param, int param_len, int timeout TSRMLS_DC);

int
php_varnish_start(int sock, int *status, int timeout TSRMLS_DC);

int
php_varnish_stop(int sock, int *status, int timeout TSRMLS_DC);

int
php_varnish_ban(int sock, int *status, char *reg, int reg_len, int timeout, int type, int compat TSRMLS_DC);

int
php_varnish_snap_stats(zval *storage, const char *ident TSRMLS_DC);

int
php_varnish_is_running(int sock, int *status, int timeout TSRMLS_DC);

int
php_varnish_get_panic(int sock, int *status, char **msg, int *msg_len, int tmo TSRMLS_DC);

int
php_varnish_clear_panic(int sock, int *status, int tmo TSRMLS_DC);

int
php_varnish_get_log(const struct VSM_data *vd, zval *line TSRMLS_DC);

void
php_varnish_log_get_tag_name(int index, char **ret, int *ret_len TSRMLS_DC);

int
php_varnish_adm_can_go(struct ze_varnish_adm_obj *zvao TSRMLS_DC);

int
php_varnish_check_compat(int version TSRMLS_DC);

/* First response line length including '\0' */
#define PHP_VARNISH_LINE0_MAX_LEN CLI_LINE0_LEN

/* Challenge string length */
#define PHP_VARNISH_CHALLENGE_LEN 32

/* {{{ Status/return codes in the varnish CLI protocol
 */
#define PHP_VARNISH_STATUS_SYNTAX  CLIS_SYNTAX
#define PHP_VARNISH_STATUS_UNKNOWN CLIS_UNKNOWN 
#define PHP_VARNISH_STATUS_UNIMPL  CLIS_UNIMPL
#define PHP_VARNISH_STATUS_TOOFEW  CLIS_TOOFEW
#define PHP_VARNISH_STATUS_TOOMANY CLIS_TOOMANY
#define PHP_VARNISH_STATUS_PARAM   CLIS_PARAM
#define PHP_VARNISH_STATUS_AUTH	CLIS_AUTH
#define PHP_VARNISH_STATUS_OK	  CLIS_OK
#define PHP_VARNISH_STATUS_CANT	CLIS_CANT
#define PHP_VARNISH_STATUS_COMMS   CLIS_COMMS
#define PHP_VARNISH_STATUS_CLOSE   CLIS_CLOSE/*}}}*/

/*{{{ varnish param names */
#define PHP_VARNISH_PARAM_ACCEPTOR_SLEEP_DECAY "acceptor_sleep_decay"
#define PHP_VARNISH_PARAM_ACCEPTOR_SLEEP_INCR "acceptor_sleep_incr"
#define PHP_VARNISH_PARAM_ACCEPTOR_SLEEP_MAX "acceptor_sleep_max"
#define PHP_VARNISH_PARAM_AUTO_RESTART "auto_restart"
#define PHP_VARNISH_PARAM_BAN_DUPS "ban_dups"
#define PHP_VARNISH_PARAM_BAN_LURKER_SLEEP "ban_lurker_sleep"
#define PHP_VARNISH_PARAM_BETWEEN_BYTES_TIMEOUT "between_bytes_timeout"
#define PHP_VARNISH_PARAM_CC_COMMAND "cc_command"
#define PHP_VARNISH_PARAM_CLI_BUFFER "cli_buffer"
#define PHP_VARNISH_PARAM_CLI_TIMEOUT "cli_timeout"
#define PHP_VARNISH_PARAM_CLOCK_SKEW "clock_skew"
#define PHP_VARNISH_PARAM_CONNECT_TIMEOUT "connect_timeout"
#define PHP_VARNISH_PARAM_CRITBIT_COOLOFF "critbit_cooloff"
#define PHP_VARNISH_PARAM_DEFAULT_GRACE "default_grace"
#define PHP_VARNISH_PARAM_DEFAULT_KEEP "default_keep"
#define PHP_VARNISH_PARAM_DEFAULT_TTL "default_ttl"
#define PHP_VARNISH_PARAM_DIAG_BITMAP "diag_bitmap"
#define PHP_VARNISH_PARAM_ESI_SYNTAX "esi_syntax"
#define PHP_VARNISH_PARAM_EXPIRY_SLEEP "expiry_sleep"
#define PHP_VARNISH_PARAM_FETCH_CHUNKSIZE "fetch_chunksize"
#define PHP_VARNISH_PARAM_FETCH_MAXCHUNKSIZE "fetch_maxchunksize"
#define PHP_VARNISH_PARAM_FIRST_BYTE_TIMEOUT "first_byte_timeout"
#define PHP_VARNISH_PARAM_GROUP "group"
#define PHP_VARNISH_PARAM_GZIP_LEVEL "gzip_level"
#define PHP_VARNISH_PARAM_GZIP_STACK_BUFFER "gzip_stack_buffer"
#define PHP_VARNISH_PARAM_GZIP_TMP_SPACE "gzip_tmp_space"
#define PHP_VARNISH_PARAM_HTTP_GZIP_SUPPORT "http_gzip_support"
#define PHP_VARNISH_PARAM_HTTP_MAX_HDR "http_max_hdr"
#define PHP_VARNISH_PARAM_HTTP_RANGE_SUPPORT "http_range_support"
#define PHP_VARNISH_PARAM_HTTP_REQ_HDR_LEN "http_req_hdr_len"
#define PHP_VARNISH_PARAM_HTTP_REQ_SIZE "http_req_size"
#define PHP_VARNISH_PARAM_HTTP_RESP_HDR_LEN "http_resp_hdr_len"
#define PHP_VARNISH_PARAM_HTTP_RESP_SIZE "http_resp_size"
#define PHP_VARNISH_PARAM_LISTEN_ADDRESS "listen_address"
#define PHP_VARNISH_PARAM_LISTEN_DEPTH "listen_depth"
#define PHP_VARNISH_PARAM_LOG_HASHSTRING "log_hashstring"
#define PHP_VARNISH_PARAM_LOG_LOCAL_ADDRESS "log_local_address"
#define PHP_VARNISH_PARAM_LRU_INTERVAL "lru_interval"
#define PHP_VARNISH_PARAM_MAX_ESI_DEPTH "max_esi_depth"
#define PHP_VARNISH_PARAM_MAX_RESTARTS "max_restarts"
#define PHP_VARNISH_PARAM_PING_INTERVAL "ping_interval"
#define PHP_VARNISH_PARAM_PIPE_TIMEOUT "pipe_timeout"
#define PHP_VARNISH_PARAM_PREFER_IPV6 "prefer_ipv6"
#define PHP_VARNISH_PARAM_QUEUE_MAX "queue_max"
#define PHP_VARNISH_PARAM_RUSH_EXPONENT "rush_exponent"
#define PHP_VARNISH_PARAM_SAINTMODE_THRESHOLD "saintmode_threshold"
#define PHP_VARNISH_PARAM_SEND_TIMEOUT "send_timeout"
#define PHP_VARNISH_PARAM_SESS_TIMEOUT "sess_timeout"
#define PHP_VARNISH_PARAM_SESS_WORKSPACE "sess_workspace"
#define PHP_VARNISH_PARAM_SESSION_LINGER "session_linger"
#define PHP_VARNISH_PARAM_SESSION_MAX "session_max"
#define PHP_VARNISH_PARAM_SHM_RECLEN "shm_reclen"
#define PHP_VARNISH_PARAM_SHM_WORKSPACE "shm_workspace"
#define PHP_VARNISH_PARAM_SHORTLIVED "shortlived"
#define PHP_VARNISH_PARAM_SYSLOG_CLI_TRAFFIC "syslog_cli_traffic"
#define PHP_VARNISH_PARAM_THREAD_POOL_ADD_DELAY "thread_pool_add_delay"
#define PHP_VARNISH_PARAM_THREAD_POOL_ADD_THRESHOLD "thread_pool_add_threshold"
#define PHP_VARNISH_PARAM_THREAD_POOL_FAIL_DELAY "thread_pool_fail_delay"
#define PHP_VARNISH_PARAM_THREAD_POOL_MAX "thread_pool_max"
#define PHP_VARNISH_PARAM_THREAD_POOL_MIN "thread_pool_min"
#define PHP_VARNISH_PARAM_THREAD_POOL_PURGE_DELAY "thread_pool_purge_delay"
#define PHP_VARNISH_PARAM_THREAD_POOL_STACK "thread_pool_stack"
#define PHP_VARNISH_PARAM_THREAD_POOL_TIMEOUT "thread_pool_timeout"
#define PHP_VARNISH_PARAM_THREAD_POOL_WORKSPACE "thread_pool_workspace"
#define PHP_VARNISH_PARAM_THREAD_POOLS "thread_pools"
#define PHP_VARNISH_PARAM_THREAD_STATS_RATE "thread_stats_rate"
#define PHP_VARNISH_PARAM_USER "user"
#define PHP_VARNISH_PARAM_VCC_ERR_UNREF "vcc_err_unref"
#define PHP_VARNISH_PARAM_VCL_DIR "vcl_dir"
#define PHP_VARNISH_PARAM_VCL_TRACE "vcl_trace"
#define PHP_VARNISH_PARAM_VMOD_DIR "vmod_dir"
#define PHP_VARNISH_PARAM_WAITER "waiter"/*}}}*/

enum {
	PHP_VARNISH_PARAM_STRING,
	PHP_VARNISH_PARAM_DOUBLE,
	PHP_VARNISH_PARAM_INT,
	PHP_VARNISH_PARAM_BOOL,
	PHP_VARNISH_PARAM_QUOTED_STRING,
};

struct php_varnish_param {
	char *param_name;
	int param_type;
};

enum {
	PHP_VARNISH_BAN_COMMAND,
	PHP_VARNISH_BAN_URL_COMMAND,
};

enum {
	PHP_VARNISH_COMPAT_2 = 2,
	PHP_VARNISH_COMPAT_3 = 3,
};

#endif	/* PHP_VARNISH_LIB_H */

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
