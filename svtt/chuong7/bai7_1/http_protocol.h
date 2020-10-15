/* Licensed to the Apache Software Foundation (ASF) under one or more
    2  * contributor license agreements.  See the NOTICE file distributed with
    3  * this work for additional information regarding copyright ownership.
    4  * The ASF licenses this file to You under the Apache License, Version 2.0
    5  * (the "License"); you may not use this file except in compliance with
    6  * the License.  You may obtain a copy of the License at
    7  *
    8  *     http://www.apache.org/licenses/LICENSE-2.0
    9  *
   10  * Unless required by applicable law or agreed to in writing, software
   11  * distributed under the License is distributed on an "AS IS" BASIS,
   12  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   13  * See the License for the specific language governing permissions and
   14  * limitations under the License.
   15  */
   16 
   26 #ifndef APACHE_HTTP_PROTOCOL_H
   27 #define APACHE_HTTP_PROTOCOL_H
   28 
   29 #include "httpd.h"
   30 #include "apr_portable.h"
   31 #include "apr_mmap.h"
   32 #include "apr_buckets.h"
   33 #include "util_filter.h"
   34 
   35 #ifdef __cplusplus
   36 extern "C" {
   37 #endif
   38 
   44 AP_DECLARE_HOOK(void,insert_error_filter,(request_rec *r))
   45 
   46 
   49 AP_DECLARE_DATA extern ap_filter_rec_t *ap_old_write_func;
   50 
   51 /*
   52  * Prototypes for routines which either talk directly back to the user,
   53  * or control the ones that eventually do.
   54  */
   55 
   61 AP_DECLARE(request_rec *) ap_create_request(conn_rec *c);
   62 
   68 request_rec *ap_read_request(conn_rec *c);
   69 
   75 AP_DECLARE(int) ap_parse_request_line(request_rec *r);
   76 
   82 AP_DECLARE(int) ap_check_request_header(request_rec *r);
   83 
   88 AP_DECLARE(void) ap_get_mime_headers(request_rec *r);
   89 
   96 AP_DECLARE(void) ap_get_mime_headers_core(request_rec *r,
   97                                           apr_bucket_brigade *bb);
   98 
   99 /* Finish up stuff after a request */
  100 
  106 AP_DECLARE(void) ap_finalize_request_protocol(request_rec *r);
  107 
  117 AP_DECLARE(void) ap_send_error_response(request_rec *r, int recursive_error);
  118 
  119 /* Set last modified header line from the lastmod date of the associated file.
  120  * Also, set content length.
  121  *
  122  * May return an error status, typically HTTP_NOT_MODIFIED (that when the
  123  * permit_cache argument is set to one).
  124  */
  125 
  131 AP_DECLARE(void) ap_set_content_length(request_rec *r, apr_off_t length);
  132 
  138 AP_DECLARE(int) ap_set_keepalive(request_rec *r);
  139 
  147 AP_DECLARE(apr_time_t) ap_rationalize_mtime(request_rec *r, apr_time_t mtime);
  148 
  160 AP_DECLARE(const char *) ap_make_content_type(request_rec *r,
  161                                               const char *type);
  162 
  167 AP_DECLARE(void) ap_setup_make_content_type(apr_pool_t *pool);
  168 
  170 typedef struct etag_rec etag_rec;
  171 
  175 struct etag_rec {
  177     const char *vlist_validator;
  179     apr_time_t request_time;
  181     apr_finfo_t *finfo;
  183     const char *pathname;
  185     apr_file_t *fd;
  187     int force_weak;
  188 };
  189 
  198 AP_DECLARE(char *) ap_make_etag(request_rec *r, int force_weak);
  199 
  206 AP_DECLARE(char *) ap_make_etag_ex(request_rec *r, etag_rec *er);
  207 
  212 AP_DECLARE(void) ap_set_etag(request_rec *r);
  213 
  219 AP_DECLARE(void) ap_set_etag_fd(request_rec *r, apr_file_t *fd);
  220 
  225 AP_DECLARE(void) ap_set_last_modified(request_rec *r);
  226 
  227 typedef enum {
  228     AP_CONDITION_NONE,
  229     AP_CONDITION_NOMATCH,
  230     AP_CONDITION_WEAK,
  231     AP_CONDITION_STRONG
  232 } ap_condition_e;
  233 
  242 AP_DECLARE(ap_condition_e) ap_condition_if_match(request_rec *r,
  243         apr_table_t *headers);
  244 
  254 AP_DECLARE(ap_condition_e) ap_condition_if_unmodified_since(request_rec *r,
  255         apr_table_t *headers);
  256 
  266 AP_DECLARE(ap_condition_e) ap_condition_if_none_match(request_rec *r,
  267         apr_table_t *headers);
  268 
  278 AP_DECLARE(ap_condition_e) ap_condition_if_modified_since(request_rec *r,
  279         apr_table_t *headers);
  280 
  290 AP_DECLARE(ap_condition_e) ap_condition_if_range(request_rec *r,
  291         apr_table_t *headers);
  292 
  301 AP_DECLARE(int) ap_meets_conditions(request_rec *r);
  302 
  303 /* Other ways to send stuff at the client.  All of these keep track
  304  * of bytes_sent automatically.  This indirection is intended to make
  305  * it a little more painless to slide things like HTTP-NG packetization
  306  * underneath the main body of the code later.  In the meantime, it lets
  307  * us centralize a bit of accounting (bytes_sent).
  308  *
  309  * These also return the number of bytes written by the call.
  310  * They should only be called with a timeout registered, for obvious reaasons.
  311  * (Ditto the send_header stuff).
  312  */
  313 
  323 AP_DECLARE(apr_status_t) ap_send_fd(apr_file_t *fd, request_rec *r, apr_off_t offset,
  324                                    apr_size_t length, apr_size_t *nbytes);
  325 
  326 #if APR_HAS_MMAP
  327 
  335 AP_DECLARE(apr_size_t) ap_send_mmap(apr_mmap_t *mm,
  336                                     request_rec *r,
  337                                     apr_size_t offset,
  338                                     apr_size_t length);
  339 #endif
  340 
  341 
  350 AP_DECLARE(int) ap_method_register(apr_pool_t *p, const char *methname);
  351 
  357 AP_DECLARE(void) ap_method_registry_init(apr_pool_t *p);
  358 
  363 #define AP_METHOD_CHECK_ALLOWED(mask, methname) \
  364     ((mask) & (AP_METHOD_BIT << ap_method_number_of((methname))))
  365 
  375 AP_DECLARE(ap_method_list_t *) ap_make_method_list(apr_pool_t *p, int nelts);
  376 
  377 
  384 AP_DECLARE(void) ap_copy_method_list(ap_method_list_t *dest,
  385                                      ap_method_list_t *src);
  386 
  395 AP_DECLARE(int) ap_method_in_list(ap_method_list_t *l, const char *method);
  396 
  405 AP_DECLARE(void) ap_method_list_add(ap_method_list_t *l, const char *method);
  406 
  414 AP_DECLARE(void) ap_method_list_remove(ap_method_list_t *l,
  415                                        const char *method);
  416 
  423 AP_DECLARE(void) ap_clear_method_list(ap_method_list_t *l);
  424 
  432 AP_DECLARE(void) ap_set_content_type(request_rec *r, const char *ct);
  433 
  438 AP_DECLARE(void) ap_set_accept_ranges(request_rec *r);
  439 
  440 
  441 /* Hmmm... could macrofy these for now, and maybe forever, though the
  442  * definitions of the macros would get a whole lot hairier.
  443  */
  444 
  451 AP_DECLARE(int) ap_rputc(int c, request_rec *r);
  452 
  460 AP_DECLARE(int) ap_rwrite(const void *buf, int nbyte, request_rec *r);
  461 
  469 static APR_INLINE int ap_rputs(const char *str, request_rec *r)
  470 {
  471     return ap_rwrite(str, (int)strlen(str), r);
  472 }
  473 
  480 AP_DECLARE_NONSTD(int) ap_rvputs(request_rec *r,...)
  481                        AP_FN_ATTR_SENTINEL;
  482 
  490 AP_DECLARE(int) ap_vrprintf(request_rec *r, const char *fmt, va_list vlist);
  491 
  499 AP_DECLARE_NONSTD(int) ap_rprintf(request_rec *r, const char *fmt,...)
  500                                 __attribute__((format(printf,2,3)));
  501 
  507 AP_DECLARE(int) ap_rflush(request_rec *r);
  508 
  515 AP_DECLARE(int) ap_index_of_response(int status);
  516 
  524 AP_DECLARE(const char *) ap_get_status_line(int status);
  525 
  535 AP_DECLARE(const char *) ap_get_status_line_ex(apr_pool_t *p, int status);
  536 
  537 /* Reading a block of data from the client connection (e.g., POST arg) */
  538 
  550 AP_DECLARE(int) ap_setup_client_block(request_rec *r, int read_policy);
  551 
  560 AP_DECLARE(int) ap_should_client_block(request_rec *r);
  561 
  571 AP_DECLARE(long) ap_get_client_block(request_rec *r, char *buffer, apr_size_t bufsiz);
  572 
  588 AP_DECLARE(int) ap_map_http_request_error(apr_status_t rv, int status);
  589 
  600 AP_DECLARE(int) ap_discard_request_body(request_rec *r);
  601 
  607 AP_DECLARE(void) ap_note_auth_failure(request_rec *r);
  608 
  612 AP_DECLARE(void) ap_note_basic_auth_failure(request_rec *r);
  613 
  617 AP_DECLARE(void) ap_note_digest_auth_failure(request_rec *r);
  618 
  626 AP_DECLARE_HOOK(int, note_auth_failure, (request_rec *r, const char *auth_type))
  627 
  651 AP_DECLARE(int) ap_get_basic_auth_pw(request_rec *r, const char **pw);
  652 
  653 #define AP_GET_BASIC_AUTH_PW_NOTE "AP_GET_BASIC_AUTH_PW_NOTE"
  654 
  668 AP_DECLARE(apr_status_t) ap_get_basic_auth_components(const request_rec *r,
  669                                                       const char **username,
  670                                                       const char **password);
  671 
  681 AP_CORE_DECLARE(void) ap_parse_uri(request_rec *r, const char *uri);
  682 
  683 #define AP_GETLINE_FOLD      (1 << 0) /* Whether to merge continuation lines */
  684 #define AP_GETLINE_CRLF      (1 << 1) /* Whether line ends must be CRLF */
  685 #define AP_GETLINE_NOSPC_EOL (1 << 2) /* Whether to consume up to and including
  686                                          the end of line on APR_ENOSPC */
  687 #define AP_GETLINE_NONBLOCK  (1 << 3) /* Whether to read non-blocking */
  688 
  699 AP_DECLARE(int) ap_getline(char *s, int n, request_rec *r, int flags);
  700 
  717 AP_DECLARE(apr_status_t) ap_fgetline(char **s, apr_size_t n,
  718                                      apr_size_t *read, ap_filter_t *f,
  719                                      int flags, apr_bucket_brigade *bb,
  720                                      apr_pool_t *p);
  721 
  728 AP_DECLARE(apr_status_t) ap_rgetline(char **s, apr_size_t n,
  729                                      apr_size_t *read, request_rec *r,
  730                                      int flags, apr_bucket_brigade *bb);
  731 
  738 AP_DECLARE(int) ap_method_number_of(const char *method);
  739 
  747 AP_DECLARE(const char *) ap_method_name_of(apr_pool_t *p, int methnum);
  748 
  749 
  750 /* Hooks */
  751 /*
  752  * pre_read_request --- run right before read_request_line(),
  753  *                  and not run during any subrequests.
  754  */
  762 AP_DECLARE_HOOK(void,pre_read_request,(request_rec *r, conn_rec *c))
  763 
  764 /*
  765  * post_read_request --- run right after read_request or internal_redirect,
  766  *                  and not run during any subrequests.
  767  */
  775 AP_DECLARE_HOOK(int,post_read_request,(request_rec *r))
  776 
  783 AP_DECLARE_HOOK(int,log_transaction,(request_rec *r))
  784 
  791 AP_DECLARE_HOOK(const char *,http_scheme,(const request_rec *r))
  792 
  798 AP_DECLARE_HOOK(apr_port_t,default_port,(const request_rec *r))
  799 
  800 
  801 #define AP_PROTOCOL_HTTP1        "http/1.1"
  802 
  837 AP_DECLARE_HOOK(int,protocol_propose,(conn_rec *c, request_rec *r,
  838                                       server_rec *s,
  839                                       const apr_array_header_t *offers,
  840                                       apr_array_header_t *proposals))
  841 
  842 
  865 AP_DECLARE_HOOK(int,protocol_switch,(conn_rec *c, request_rec *r,
  866                                      server_rec *s,
  867                                      const char *protocol))
  868 
  869 
  880 AP_DECLARE_HOOK(const char *,protocol_get,(const conn_rec *c))
  881 
  882 
  898 AP_DECLARE(apr_status_t) ap_get_protocol_upgrades(conn_rec *c, request_rec *r, 
  899                                                   server_rec *s, int report_all, 
  900                                                   const apr_array_header_t **pupgrades);
  901                                                   
  917 AP_DECLARE(const char *) ap_select_protocol(conn_rec *c, request_rec *r, 
  918                                             server_rec *s,
  919                                             const apr_array_header_t *choices);
  920 
  935 AP_DECLARE(apr_status_t) ap_switch_protocol(conn_rec *c, request_rec *r, 
  936                                             server_rec *s,
  937                                             const char *protocol);
  938 
  950 AP_DECLARE(const char *) ap_get_protocol(conn_rec *c);
  951 
  966 AP_DECLARE(int) ap_is_allowed_protocol(conn_rec *c, request_rec *r,
  967                                        server_rec *s, const char *protocol);
  968 
  970 typedef struct ap_bucket_error ap_bucket_error;
  971 
  981 struct ap_bucket_error {
  983     apr_bucket_refcount refcount;
  985     int status;
  987     const char    *data;
  988 };
  989 
  991 AP_DECLARE_DATA extern const apr_bucket_type_t ap_bucket_type_error;
  992 
  998 #define AP_BUCKET_IS_ERROR(e)         (e->type == &ap_bucket_type_error)
  999 
 1008 AP_DECLARE(apr_bucket *) ap_bucket_error_make(apr_bucket *b, int error,
 1009                 const char *buf, apr_pool_t *p);
 1010 
 1019 AP_DECLARE(apr_bucket *) ap_bucket_error_create(int error, const char *buf,
 1020                                                 apr_pool_t *p,
 1021                                                 apr_bucket_alloc_t *list);
 1022 
 1023 AP_DECLARE_NONSTD(apr_status_t) ap_byterange_filter(ap_filter_t *f, apr_bucket_brigade *b);
 1024 AP_DECLARE_NONSTD(apr_status_t) ap_http_header_filter(ap_filter_t *f, apr_bucket_brigade *b);
 1025 AP_DECLARE_NONSTD(apr_status_t) ap_content_length_filter(ap_filter_t *,
 1026                                                               apr_bucket_brigade *);
 1027 AP_DECLARE_NONSTD(apr_status_t) ap_old_write_filter(ap_filter_t *f, apr_bucket_brigade *b);
 1028 
 1034 AP_DECLARE(void) ap_set_sub_req_protocol(request_rec *rnew, const request_rec *r);
 1035 
 1041 AP_DECLARE(void) ap_finalize_sub_req_protocol(request_rec *sub_r);
 1042 
 1048 AP_DECLARE(void) ap_send_interim_response(request_rec *r, int send_headers);
 1049 
 1050 
 1051 #ifdef __cplusplus
 1052 }
 1053 #endif
 1054 
 1055 #endif  /* !APACHE_HTTP_PROTOCOL_H */
 1056 

