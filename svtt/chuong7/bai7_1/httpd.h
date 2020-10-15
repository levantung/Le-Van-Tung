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
   36 #ifndef APACHE_HTTPD_H
   37 #define APACHE_HTTPD_H
   38 
   39 /* XXX - We need to push more stuff to other .h files, or even .c files, to
   40  * make this file smaller
   41  */
   42 
   43 /* Headers in which EVERYONE has an interest... */
   44 #include "ap_config.h"
   45 #include "ap_mmn.h"
   46 
   47 #include "ap_release.h"
   48 
   49 #include "apr.h"
   50 #include "apr_general.h"
   51 #include "apr_tables.h"
   52 #include "apr_pools.h"
   53 #include "apr_time.h"
   54 #include "apr_network_io.h"
   55 #include "apr_buckets.h"
   56 #include "apr_poll.h"
   57 #include "apr_thread_proc.h"
   58 #include "apr_hash.h"
   59 
   60 #include "os.h"
   61 
   62 #include "ap_regex.h"
   63 
   64 #if APR_HAVE_STDLIB_H
   65 #include <stdlib.h>
   66 #endif
   67 
   68 /* Note: apr_uri.h is also included, see below */
   69 
   70 #ifdef __cplusplus
   71 extern "C" {
   72 #endif
   73 
   74 /* ----------------------------- config dir ------------------------------ */
   75 
   79 #ifndef HTTPD_ROOT
   80 #ifdef OS2
   81 
   82 #define HTTPD_ROOT "/os2httpd"
   83 #elif defined(WIN32)
   84 
   85 #define HTTPD_ROOT "/apache"
   86 #elif defined (NETWARE)
   87 
   88 #define HTTPD_ROOT "/apache"
   89 #else
   90 
   91 #define HTTPD_ROOT "/usr/local/apache"
   92 #endif
   93 #endif /* HTTPD_ROOT */
   94 
   95 /*
   96  * --------- You shouldn't have to edit anything below this line ----------
   97  *
   98  * Any modifications to any defaults not defined above should be done in the
   99  * respective configuration file.
  100  *
  101  */
  102 
  107 #ifndef DOCUMENT_LOCATION
  108 #ifdef OS2
  109 /* Set default for OS/2 file system */
  110 #define DOCUMENT_LOCATION  HTTPD_ROOT "/docs"
  111 #else
  112 /* Set default for non OS/2 file system */
  113 #define DOCUMENT_LOCATION  HTTPD_ROOT "/htdocs"
  114 #endif
  115 #endif /* DOCUMENT_LOCATION */
  116 
  118 #ifndef DYNAMIC_MODULE_LIMIT
  119 #define DYNAMIC_MODULE_LIMIT 256
  120 #endif
  121 
  123 #define DEFAULT_ADMIN "[no address given]"
  124 
  126 #ifndef DEFAULT_ERRORLOG
  127 #if defined(OS2) || defined(WIN32)
  128 #define DEFAULT_ERRORLOG "logs/error.log"
  129 #else
  130 #define DEFAULT_ERRORLOG "logs/error_log"
  131 #endif
  132 #endif /* DEFAULT_ERRORLOG */
  133 
  135 #ifndef DEFAULT_ACCESS_FNAME
  136 #ifdef OS2
  137 /* Set default for OS/2 file system */
  138 #define DEFAULT_ACCESS_FNAME "htaccess"
  139 #else
  140 #define DEFAULT_ACCESS_FNAME ".htaccess"
  141 #endif
  142 #endif /* DEFAULT_ACCESS_FNAME */
  143 
  145 #ifndef SERVER_CONFIG_FILE
  146 #define SERVER_CONFIG_FILE "conf/httpd.conf"
  147 #endif
  148 
  150 #ifndef DEFAULT_PATH
  151 #define DEFAULT_PATH "/bin:/usr/bin:/usr/ucb:/usr/bsd:/usr/local/bin"
  152 #endif
  153 
  155 #ifndef SUEXEC_BIN
  156 #define SUEXEC_BIN  HTTPD_ROOT "/bin/suexec"
  157 #endif
  158 
  160 #ifndef DEFAULT_TIMEOUT
  161 #define DEFAULT_TIMEOUT 60
  162 #endif
  163 
  165 #ifndef DEFAULT_KEEPALIVE_TIMEOUT
  166 #define DEFAULT_KEEPALIVE_TIMEOUT 5
  167 #endif
  168 
  170 #ifndef DEFAULT_KEEPALIVE
  171 #define DEFAULT_KEEPALIVE 100
  172 #endif
  173 
  174 /*
  175  * Limits on the size of various request items.  These limits primarily
  176  * exist to prevent simple denial-of-service attacks on a server based
  177  * on misuse of the protocol.  The recommended values will depend on the
  178  * nature of the server resources -- CGI scripts and database backends
  179  * might require large values, but most servers could get by with much
  180  * smaller limits than we use below.  The request message body size can
  181  * be limited by the per-dir config directive LimitRequestBody.
  182  *
  183  * Internal buffer sizes are two bytes more than the DEFAULT_LIMIT_REQUEST_LINE
  184  * and DEFAULT_LIMIT_REQUEST_FIELDSIZE below, which explains the 8190.
  185  * These two limits can be lowered or raised by the server config
  186  * directives LimitRequestLine and LimitRequestFieldsize, respectively.
  187  *
  188  * DEFAULT_LIMIT_REQUEST_FIELDS can be modified or disabled (set = 0) by
  189  * the server config directive LimitRequestFields.
  190  */
  191 
  193 #ifndef DEFAULT_LIMIT_REQUEST_LINE
  194 #define DEFAULT_LIMIT_REQUEST_LINE 8190
  195 #endif
  196 
  197 #ifndef DEFAULT_LIMIT_REQUEST_FIELDSIZE
  198 #define DEFAULT_LIMIT_REQUEST_FIELDSIZE 8190
  199 #endif
  200 
  201 #ifndef DEFAULT_LIMIT_REQUEST_FIELDS
  202 #define DEFAULT_LIMIT_REQUEST_FIELDS 100
  203 #endif
  204 
  205 #ifndef DEFAULT_LIMIT_BLANK_LINES
  206 #define DEFAULT_LIMIT_BLANK_LINES 10
  207 #endif
  208 
  213 #define DEFAULT_ADD_DEFAULT_CHARSET_NAME "iso-8859-1"
  214 
  216 #define AP_SERVER_PROTOCOL "HTTP/1.1"
  217 
  218 
  219 /* ------------------ stuff that modules are allowed to look at ----------- */
  220 
  222 #ifndef AP_DEFAULT_INDEX
  223 #define AP_DEFAULT_INDEX "index.html"
  224 #endif
  225 
  227 #ifndef AP_TYPES_CONFIG_FILE
  228 #define AP_TYPES_CONFIG_FILE "conf/mime.types"
  229 #endif
  230 
  231 /*
  232  * Define the HTML doctype strings centrally.
  233  */
  235 #define DOCTYPE_HTML_2_0  "<!DOCTYPE HTML PUBLIC \"-//IETF//" \
  236                           "DTD HTML 2.0//EN\">\n"
  237 
  238 #define DOCTYPE_HTML_3_2  "<!DOCTYPE HTML PUBLIC \"-//W3C//" \
  239                           "DTD HTML 3.2 Final//EN\">\n"
  240 
  241 #define DOCTYPE_HTML_4_0S "<!DOCTYPE HTML PUBLIC \"-//W3C//" \
  242                           "DTD HTML 4.0//EN\"\n" \
  243                           "\"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
  244 
  245 #define DOCTYPE_HTML_4_0T "<!DOCTYPE HTML PUBLIC \"-//W3C//" \
  246                           "DTD HTML 4.0 Transitional//EN\"\n" \
  247                           "\"http://www.w3.org/TR/REC-html40/loose.dtd\">\n"
  248 
  249 #define DOCTYPE_HTML_4_0F "<!DOCTYPE HTML PUBLIC \"-//W3C//" \
  250                           "DTD HTML 4.0 Frameset//EN\"\n" \
  251                           "\"http://www.w3.org/TR/REC-html40/frameset.dtd\">\n"
  252 
  253 #define DOCTYPE_HTML_4_01 "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\" \"http://www.w3.org/TR/html4/strict.dtd\">\n"
  254 
  255 #define DOCTYPE_HTML_5 "<!DOCTYPE html>\n"
  256 
  257 #define DOCTYPE_XHTML_1_0S "<!DOCTYPE html PUBLIC \"-//W3C//" \
  258                            "DTD XHTML 1.0 Strict//EN\"\n" \
  259                            "\"http://www.w3.org/TR/xhtml1/DTD/" \
  260                            "xhtml1-strict.dtd\">\n"
  261 
  262 #define DOCTYPE_XHTML_1_0T "<!DOCTYPE html PUBLIC \"-//W3C//" \
  263                            "DTD XHTML 1.0 Transitional//EN\"\n" \
  264                            "\"http://www.w3.org/TR/xhtml1/DTD/" \
  265                            "xhtml1-transitional.dtd\">\n"
  266 
  267 #define DOCTYPE_XHTML_1_0F "<!DOCTYPE html PUBLIC \"-//W3C//" \
  268                            "DTD XHTML 1.0 Frameset//EN\"\n" \
  269                            "\"http://www.w3.org/TR/xhtml1/DTD/" \
  270                            "xhtml1-frameset.dtd\">"
  271 
  273 #define HTTP_VERSION(major,minor) (1000*(major)+(minor))
  274 
  275 #define HTTP_VERSION_MAJOR(number) ((number)/1000)
  276 
  277 #define HTTP_VERSION_MINOR(number) ((number)%1000)
  278 
  279 /* -------------- Port number for server running standalone --------------- */
  280 
  282 #define DEFAULT_HTTP_PORT       80
  283 
  284 #define DEFAULT_HTTPS_PORT      443
  285 
  291 #define ap_is_default_port(port,r)      ((port) == ap_default_port(r))
  292 
  296 #define ap_default_port(r)      ap_run_default_port(r)
  297 
  301 #define ap_http_scheme(r)       ap_run_http_scheme(r)
  302 
  304 #define MAX_STRING_LEN HUGE_STRING_LEN
  305 
  307 #define HUGE_STRING_LEN 8192
  308 
  310 #define AP_IOBUFSIZE 8192
  311 
  313 #define AP_MAX_REG_MATCH 10
  314 
  321 #define AP_MAX_SENDFILE 16777216  /* 2^24 */
  322 
  329 #define APEXIT_OK               0x0
  330 
  331 #define APEXIT_INIT             0x2
  332 
  333 #define APEXIT_CHILDINIT        0x3
  334 
  339 #define APEXIT_CHILDSICK        0x7
  340 
  345 #define APEXIT_CHILDFATAL       0xf
  346 
  347 #ifndef AP_DECLARE
  348 
  353 # define AP_DECLARE(type)    type
  354 #endif
  355 
  356 #ifndef AP_DECLARE_NONSTD
  357 
  364 # define AP_DECLARE_NONSTD(type)    type
  365 #endif
  366 #ifndef AP_DECLARE_DATA
  367 # define AP_DECLARE_DATA
  368 #endif
  369 
  370 #ifndef AP_MODULE_DECLARE
  371 # define AP_MODULE_DECLARE(type)    type
  372 #endif
  373 #ifndef AP_MODULE_DECLARE_NONSTD
  374 # define AP_MODULE_DECLARE_NONSTD(type)  type
  375 #endif
  376 #ifndef AP_MODULE_DECLARE_DATA
  377 # define AP_MODULE_DECLARE_DATA
  378 #endif
  379 
  384 #ifndef AP_CORE_DECLARE
  385 # define AP_CORE_DECLARE        AP_DECLARE
  386 #endif
  387 
  393 #ifndef AP_CORE_DECLARE_NONSTD
  394 # define AP_CORE_DECLARE_NONSTD AP_DECLARE_NONSTD
  395 #endif
  396 
  401 #define AP_START_USERERR            (APR_OS_START_USERERR + 2000)
  402 #define AP_USERERR_LEN              1000
  403 
  405 #define AP_DECLINED                 (AP_START_USERERR + 0)
  406 
  413 typedef struct {
  414     int major;              
  415     int minor;              
  416     int patch;              
  417     const char *add_string; 
  418 } ap_version_t;
  419 
  426 AP_DECLARE(void) ap_get_server_revision(ap_version_t *version);
  427 
  434 AP_DECLARE(const char *) ap_get_server_banner(void);
  435 
  443 AP_DECLARE(const char *) ap_get_server_description(void);
  444 
  450 AP_DECLARE(void) ap_add_version_component(apr_pool_t *pconf, const char *component);
  451 
  456 AP_DECLARE(const char *) ap_get_server_built(void);
  457 
  458 /* non-HTTP status codes returned by hooks */
  459 
  460 #define OK 0                    
  461 #define DECLINED -1             
  462 #define DONE -2                 
  465 #define SUSPENDED -3 
  470 #define AP_NOBODY_WROTE         -100
  471 
  473 #define AP_NOBODY_READ          -101
  474 
  477 #define AP_FILTER_ERROR         -102
  478 
  489 #define RESPONSE_CODES 103
  490 
  491 #define HTTP_CONTINUE                        100
  492 #define HTTP_SWITCHING_PROTOCOLS             101
  493 #define HTTP_PROCESSING                      102
  494 #define HTTP_OK                              200
  495 #define HTTP_CREATED                         201
  496 #define HTTP_ACCEPTED                        202
  497 #define HTTP_NON_AUTHORITATIVE               203
  498 #define HTTP_NO_CONTENT                      204
  499 #define HTTP_RESET_CONTENT                   205
  500 #define HTTP_PARTIAL_CONTENT                 206
  501 #define HTTP_MULTI_STATUS                    207
  502 #define HTTP_ALREADY_REPORTED                208
  503 #define HTTP_IM_USED                         226
  504 #define HTTP_MULTIPLE_CHOICES                300
  505 #define HTTP_MOVED_PERMANENTLY               301
  506 #define HTTP_MOVED_TEMPORARILY               302
  507 #define HTTP_SEE_OTHER                       303
  508 #define HTTP_NOT_MODIFIED                    304
  509 #define HTTP_USE_PROXY                       305
  510 #define HTTP_TEMPORARY_REDIRECT              307
  511 #define HTTP_PERMANENT_REDIRECT              308
  512 #define HTTP_BAD_REQUEST                     400
  513 #define HTTP_UNAUTHORIZED                    401
  514 #define HTTP_PAYMENT_REQUIRED                402
  515 #define HTTP_FORBIDDEN                       403
  516 #define HTTP_NOT_FOUND                       404
  517 #define HTTP_METHOD_NOT_ALLOWED              405
  518 #define HTTP_NOT_ACCEPTABLE                  406
  519 #define HTTP_PROXY_AUTHENTICATION_REQUIRED   407
  520 #define HTTP_REQUEST_TIME_OUT                408
  521 #define HTTP_CONFLICT                        409
  522 #define HTTP_GONE                            410
  523 #define HTTP_LENGTH_REQUIRED                 411
  524 #define HTTP_PRECONDITION_FAILED             412
  525 #define HTTP_REQUEST_ENTITY_TOO_LARGE        413
  526 #define HTTP_REQUEST_URI_TOO_LARGE           414
  527 #define HTTP_UNSUPPORTED_MEDIA_TYPE          415
  528 #define HTTP_RANGE_NOT_SATISFIABLE           416
  529 #define HTTP_EXPECTATION_FAILED              417
  530 #define HTTP_IM_A_TEAPOT                     418
  531 #define HTTP_MISDIRECTED_REQUEST             421
  532 #define HTTP_UNPROCESSABLE_ENTITY            422
  533 #define HTTP_LOCKED                          423
  534 #define HTTP_FAILED_DEPENDENCY               424
  535 #define HTTP_TOO_EARLY                       425
  536 #define HTTP_UPGRADE_REQUIRED                426
  537 #define HTTP_PRECONDITION_REQUIRED           428
  538 #define HTTP_TOO_MANY_REQUESTS               429
  539 #define HTTP_REQUEST_HEADER_FIELDS_TOO_LARGE 431
  540 #define HTTP_UNAVAILABLE_FOR_LEGAL_REASONS   451
  541 #define HTTP_INTERNAL_SERVER_ERROR           500
  542 #define HTTP_NOT_IMPLEMENTED                 501
  543 #define HTTP_BAD_GATEWAY                     502
  544 #define HTTP_SERVICE_UNAVAILABLE             503
  545 #define HTTP_GATEWAY_TIME_OUT                504
  546 #define HTTP_VERSION_NOT_SUPPORTED           505
  547 #define HTTP_VARIANT_ALSO_VARIES             506
  548 #define HTTP_INSUFFICIENT_STORAGE            507
  549 #define HTTP_LOOP_DETECTED                   508
  550 #define HTTP_NOT_EXTENDED                    510
  551 #define HTTP_NETWORK_AUTHENTICATION_REQUIRED 511
  552 
  554 #define ap_is_HTTP_INFO(x)         (((x) >= 100)&&((x) < 200))
  555 
  556 #define ap_is_HTTP_SUCCESS(x)      (((x) >= 200)&&((x) < 300))
  557 
  558 #define ap_is_HTTP_REDIRECT(x)     (((x) >= 300)&&((x) < 400))
  559 
  560 #define ap_is_HTTP_ERROR(x)        (((x) >= 400)&&((x) < 600))
  561 
  562 #define ap_is_HTTP_CLIENT_ERROR(x) (((x) >= 400)&&((x) < 500))
  563 
  564 #define ap_is_HTTP_SERVER_ERROR(x) (((x) >= 500)&&((x) < 600))
  565 
  566 #define ap_is_HTTP_VALID_RESPONSE(x) (((x) >= 100)&&((x) < 600))
  567 
  569 #define ap_status_drops_connection(x) \
  570                                    (((x) == HTTP_BAD_REQUEST)           || \
  571                                     ((x) == HTTP_REQUEST_TIME_OUT)      || \
  572                                     ((x) == HTTP_LENGTH_REQUIRED)       || \
  573                                     ((x) == HTTP_REQUEST_ENTITY_TOO_LARGE) || \
  574                                     ((x) == HTTP_REQUEST_URI_TOO_LARGE) || \
  575                                     ((x) == HTTP_INTERNAL_SERVER_ERROR) || \
  576                                     ((x) == HTTP_SERVICE_UNAVAILABLE) || \
  577                                     ((x) == HTTP_NOT_IMPLEMENTED))
  578 
  580 #define AP_STATUS_IS_HEADER_ONLY(x) ((x) == HTTP_NO_CONTENT || \
  581                                      (x) == HTTP_NOT_MODIFIED)
  582 
  598 #define M_GET                   0       
  599 #define M_PUT                   1       /*  :             */
  600 #define M_POST                  2
  601 #define M_DELETE                3
  602 #define M_CONNECT               4
  603 #define M_OPTIONS               5
  604 #define M_TRACE                 6       
  605 #define M_PATCH                 7       
  606 #define M_PROPFIND              8       
  607 #define M_PROPPATCH             9       /*  :               */
  608 #define M_MKCOL                 10
  609 #define M_COPY                  11
  610 #define M_MOVE                  12
  611 #define M_LOCK                  13
  612 #define M_UNLOCK                14      
  613 #define M_VERSION_CONTROL       15      
  614 #define M_CHECKOUT              16      /*  :                          */
  615 #define M_UNCHECKOUT            17
  616 #define M_CHECKIN               18
  617 #define M_UPDATE                19
  618 #define M_LABEL                 20
  619 #define M_REPORT                21
  620 #define M_MKWORKSPACE           22
  621 #define M_MKACTIVITY            23
  622 #define M_BASELINE_CONTROL      24
  623 #define M_MERGE                 25
  624 /* Additional methods must be registered by the implementor, we have only
  625  * room for 64 bit-wise methods available, so do not squander them (more of
  626  * the above methods should probably move here)
  627  */
  628 /* #define M_BREW                  nn */     
  629 /* #define M_WHEN                  nn */     
  630 #define M_INVALID               26      
  638 #define METHODS     64
  639 
  643 typedef apr_uint64_t ap_method_mask_t;
  647 #define AP_METHOD_BIT ((ap_method_mask_t)1)
  648 
  650 typedef struct ap_method_list_t ap_method_list_t;
  651 
  659 struct ap_method_list_t {
  661     ap_method_mask_t method_mask;
  663     apr_array_header_t *method_list;
  664 };
  678 typedef apr_uint64_t ap_request_bnotes_t;
  679 
  685 #define AP_REQUEST_STRONG_ETAG 1 >> 0
  686 
  691 #define AP_REQUEST_GET_BNOTE(r, mask) \
  692     ((mask) & ((r)->bnotes))
  693 
  698 #define AP_REQUEST_SET_BNOTE(r, mask, val) \
  699     (r)->bnotes = (((r)->bnotes & ~(mask)) | (val))
  700 
  704 #define AP_REQUEST_IS_STRONG_ETAG(r) \
  705         AP_REQUEST_GET_BNOTE((r), AP_REQUEST_STRONG_ETAG)
  706 
  714 #define CGI_MAGIC_TYPE "application/x-httpd-cgi"
  715 
  716 #define INCLUDES_MAGIC_TYPE "text/x-server-parsed-html"
  717 
  718 #define INCLUDES_MAGIC_TYPE3 "text/x-server-parsed-html3"
  719 
  720 #define DIR_MAGIC_TYPE "httpd/unix-directory"
  721 
  722 #define AP_DEFAULT_HANDLER_NAME ""
  723 #define AP_IS_DEFAULT_HANDLER_NAME(x) (*x == '\0')
  724 
  726 /* Just in case your linefeed isn't the one the other end is expecting. */
  727 #if !APR_CHARSET_EBCDIC
  728 
  729 #define LF 10
  730 
  731 #define CR 13
  732 
  733 #define CRLF "\015\012"
  734 #else /* APR_CHARSET_EBCDIC */
  735 /* For platforms using the EBCDIC charset, the transition ASCII->EBCDIC is done
  736  * in the buff package (bread/bputs/bwrite).  Everywhere else, we use
  737  * "native EBCDIC" CR and NL characters. These are therefore
  738  * defined as
  739  * '\r' and '\n'.
  740  */
  741 #define CR '\r'
  742 #define LF '\n'
  743 #define CRLF "\r\n"
  744 #endif /* APR_CHARSET_EBCDIC */
  745 
  746 #define CRLF_ASCII "\015\012"
  747 #define ZERO_ASCII "\060"
  748 
  756 #define REQUEST_NO_BODY          0
  757 
  758 #define REQUEST_CHUNKED_ERROR    1
  759 
  760 #define REQUEST_CHUNKED_DECHUNK  2
  761 
  771 #define AP_REQ_ACCEPT_PATH_INFO    0
  772 
  773 #define AP_REQ_REJECT_PATH_INFO    1
  774 
  775 #define AP_REQ_DEFAULT_PATH_INFO   2
  776 
  780 /*
  781  * Things which may vary per file-lookup WITHIN a request ---
  782  * e.g., state of MIME config.  Basically, the name of an object, info
  783  * about the object, and any other info we may have which may need to
  784  * change as we go poking around looking for it (e.g., overridden by
  785  * .htaccess files).
  786  *
  787  * Note how the default state of almost all these things is properly
  788  * zero, so that allocating it with pcalloc does the right thing without
  789  * a whole lot of hairy initialization... so long as we are willing to
  790  * make the (fairly) portable assumption that the bit pattern of a NULL
  791  * pointer is, in fact, zero.
  792  */
  793 
  798 struct htaccess_result {
  800     const char *dir;
  802     int override;
  804     int override_opts;
  806     apr_table_t *override_list;
  808     struct ap_conf_vector_t *htaccess;
  810     const struct htaccess_result *next;
  811 };
  812 
  813 /* The following four types define a hierarchy of activities, so that
  814  * given a request_rec r you can write r->connection->server->process
  815  * to get to the process_rec.  While this reduces substantially the
  816  * number of arguments that various hooks require beware that in
  817  * threaded versions of the server you must consider multiplexing
  818  * issues.  */
  819 
  820 
  822 typedef struct process_rec process_rec;
  824 typedef struct server_rec server_rec;
  826 typedef struct conn_rec conn_rec;
  828 typedef struct conn_slave_rec conn_slave_rec;
  830 typedef struct request_rec request_rec;
  832 typedef struct conn_state_t conn_state_t;
  833 
  834 /* ### would be nice to not include this from httpd.h ... */
  835 /* This comes after we have defined the request_rec type */
  836 #include "apr_uri.h"
  837 
  841 struct process_rec {
  843     apr_pool_t *pool;
  845     apr_pool_t *pconf;
  847     const char *short_name;
  849     const char * const *argv;
  851     int argc;
  852 };
  853 
  857 struct request_rec {
  859     apr_pool_t *pool;
  861     conn_rec *connection;
  863     server_rec *server;
  864 
  866     request_rec *next;
  868     request_rec *prev;
  869 
  872     request_rec *main;
  873 
  874     /* Info about the request itself... we begin with stuff that only
  875      * protocol.c should ever touch...
  876      */
  878     char *the_request;
  880     int assbackwards;
  885     int proxyreq;
  887     int header_only;
  889     int proto_num;
  891     const char *protocol;
  895     const char *hostname;
  896 
  898     apr_time_t request_time;
  899 
  901     const char *status_line;
  903     int status;
  904 
  905     /* Request method, two ways; also, protocol, etc..  Outside of protocol.c,
  906      * look, but don't touch.
  907      */
  908 
  910     int method_number;
  912     const char *method;
  913 
  934     ap_method_mask_t allowed;
  936     apr_array_header_t *allowed_xmethods;
  938     ap_method_list_t *allowed_methods;
  939 
  941     apr_off_t sent_bodyct;
  943     apr_off_t bytes_sent;
  945     apr_time_t mtime;
  946 
  947     /* HTTP/1.1 connection-level features */
  948 
  950     const char *range;
  952     apr_off_t clength;
  954     int chunked;
  955 
  959     int read_body;
  961     int read_chunked;
  963     unsigned expecting_100;
  965     apr_bucket_brigade *kept_body;
  967     /* XXX: ap_body_to_table has been removed. Remove body_table too or
  968      * XXX: keep it to reintroduce ap_body_to_table without major bump? */
  969     apr_table_t *body_table;
  971     apr_off_t remaining;
  973     apr_off_t read_length;
  974 
  975     /* MIME header environments, in and out.  Also, an array containing
  976      * environment variables to be passed to subprocesses, so people can
  977      * write modules to add to that environment.
  978      *
  979      * The difference between headers_out and err_headers_out is that the
  980      * latter are printed even on error, and persist across internal redirects
  981      * (so the headers printed for ErrorDocument handlers will have them).
  982      *
  983      * The 'notes' apr_table_t is for notes from one module to another, with no
  984      * other set purpose in mind...
  985      */
  986 
  988     apr_table_t *headers_in;
  990     apr_table_t *headers_out;
  993     apr_table_t *err_headers_out;
  995     apr_table_t *subprocess_env;
  997     apr_table_t *notes;
  998 
  999     /* content_type, handler, content_encoding, and all content_languages
 1000      * MUST be lowercased strings.  They may be pointers to static strings;
 1001      * they should not be modified in place.
 1002      */
 1004     const char *content_type;   /* Break these out --- we dispatch on 'em */
 1006     const char *handler;        /* What we *really* dispatch on */
 1007 
 1009     const char *content_encoding;
 1011     apr_array_header_t *content_languages;
 1012 
 1014     char *vlist_validator;
 1015 
 1017     char *user;
 1019     char *ap_auth_type;
 1020 
 1021     /* What object is being requested (either directly, or via include
 1022      * or content-negotiation mapping).
 1023      */
 1024 
 1026     char *unparsed_uri;
 1028     char *uri;
 1030     char *filename;
 1034     char *canonical_filename;
 1036     char *path_info;
 1038     char *args;
 1039 
 1048     int used_path_info;
 1049 
 1051     int eos_sent;
 1052 
 1053     /* Various other config info which may change with .htaccess files
 1054      * These are config vectors, with one void* pointer for each module
 1055      * (the thing pointed to being the module's business).
 1056      */
 1057 
 1059     struct ap_conf_vector_t *per_dir_config;
 1061     struct ap_conf_vector_t *request_config;
 1062 
 1066     const struct ap_logconf *log;
 1067 
 1071     const char *log_id;
 1072 
 1079     const struct htaccess_result *htaccess;
 1080 
 1082     struct ap_filter_t *output_filters;
 1084     struct ap_filter_t *input_filters;
 1085 
 1088     struct ap_filter_t *proto_output_filters;
 1091     struct ap_filter_t *proto_input_filters;
 1092 
 1094     int no_cache;
 1096     int no_local_copy;
 1097 
 1101 #if APR_HAS_THREADS
 1102     apr_thread_mutex_t *invoke_mtx;
 1103 #endif
 1104 
 1106     apr_uri_t parsed_uri;
 1108     apr_finfo_t finfo;
 1109 
 1114     apr_sockaddr_t *useragent_addr;
 1115     char *useragent_ip;
 1116 
 1118     apr_table_t *trailers_in;
 1120     apr_table_t *trailers_out;
 1121 
 1125     char *useragent_host;
 1130     int double_reverse;
 1135     int taint;
 1140     unsigned int flushed:1;
 1145     ap_request_bnotes_t bnotes;
 1146 };
 1147 
 1158 #define PROXYREQ_NONE     0     
 1159 #define PROXYREQ_PROXY    1     
 1160 #define PROXYREQ_REVERSE  2     
 1161 #define PROXYREQ_RESPONSE 3     
 1163 /* @} */
 1164 
 1168 typedef enum {
 1169     AP_CONN_UNKNOWN,
 1170     AP_CONN_CLOSE,
 1171     AP_CONN_KEEPALIVE
 1172 } ap_conn_keepalive_e;
 1173 
 1174 /* For struct ap_filter and ap_filter_conn_ctx */
 1175 #include "util_filter.h"
 1176 
 1180 struct conn_rec {
 1182     apr_pool_t *pool;
 1184     server_rec *base_server;
 1186     void *vhost_lookup_data;
 1187 
 1188     /* Information about the connection itself */
 1190     apr_sockaddr_t *local_addr;
 1194     apr_sockaddr_t *client_addr;
 1195 
 1199     char *client_ip;
 1203     char *remote_host;
 1206     /* TODO: Remove from request_rec, make local to mod_ident */
 1207     char *remote_logname;
 1208 
 1210     char *local_ip;
 1213     char *local_host;
 1214 
 1216     long id;
 1219     struct ap_conf_vector_t *conn_config;
 1222     apr_table_t *notes;
 1224     struct ap_filter_t *input_filters;
 1226     struct ap_filter_t *output_filters;
 1228     void *sbh;
 1230     struct apr_bucket_alloc_t *bucket_alloc;
 1232     conn_state_t *cs;
 1233 
 1237     unsigned int clogging_input_filters:1;
 1238 
 1241     signed int double_reverse:2;
 1242 
 1244     unsigned aborted;
 1245 
 1248     ap_conn_keepalive_e keepalive;
 1249 
 1251     int keepalives;
 1252 
 1255     const struct ap_logconf *log;
 1256 
 1260     const char *log_id;
 1261 
 1262 
 1268 #if APR_HAS_THREADS
 1269     apr_thread_t *current_thread;
 1270 #endif
 1271 
 1273     apr_array_header_t *slaves;
 1274 
 1276     conn_rec *master;
 1277 
 1279     void *ctx;
 1280 
 1282     void *suspended_baton;
 1283 
 1285     apr_array_header_t *requests;
 1286 
 1288     struct ap_filter_conn_ctx *filter_conn_ctx;
 1289 
 1291     int async_filter;
 1292 };
 1293 
 1294 struct conn_slave_rec {
 1295   conn_rec *c;
 1296 };
 1297 
 1303 typedef enum  {
 1304     CONN_STATE_CHECK_REQUEST_LINE_READABLE,
 1305     CONN_STATE_READ_REQUEST_LINE,
 1306     CONN_STATE_HANDLER,
 1307     CONN_STATE_WRITE_COMPLETION,
 1308     CONN_STATE_SUSPENDED,
 1309     CONN_STATE_LINGER,          /* connection may be closed with lingering */
 1310     CONN_STATE_LINGER_NORMAL,   /* MPM has started lingering close with normal timeout */
 1311     CONN_STATE_LINGER_SHORT,    /* MPM has started lingering close with short timeout */
 1312 
 1313     CONN_STATE_NUM              /* Number of states (keep/kept last) */
 1314 } conn_state_e;
 1315 
 1316 typedef enum  {
 1317     CONN_SENSE_DEFAULT,
 1318     CONN_SENSE_WANT_READ,       /* next event must be read */
 1319     CONN_SENSE_WANT_WRITE       /* next event must be write */
 1320 } conn_sense_e;
 1321 
 1325 struct conn_state_t {
 1327     conn_state_e state;
 1329     conn_sense_e sense;
 1330 };
 1331 
 1332 /* Per-vhost config... */
 1333 
 1338 #define DEFAULT_VHOST_ADDR 0xfffffffful
 1339 
 1340 
 1345 typedef struct server_addr_rec server_addr_rec;
 1346 struct server_addr_rec {
 1348     server_addr_rec *next;
 1350     char *virthost;
 1352     apr_sockaddr_t *host_addr;
 1354     apr_port_t host_port;
 1355 };
 1356 
 1357 struct ap_logconf {
 1359     signed char *module_levels;
 1360 
 1362     int level;
 1363 };
 1367 struct server_rec {
 1369     process_rec *process;
 1371     server_rec *next;
 1372 
 1373     /* Log files --- note that transfer log is now in the modules... */
 1374 
 1376     char *error_fname;
 1378     apr_file_t *error_log;
 1380     struct ap_logconf log;
 1382     struct ap_errorlog_provider *errorlog_provider;
 1384     void *errorlog_provider_handle;
 1385 
 1386     /* Module-specific configuration for server, and defaults... */
 1387 
 1390     struct ap_conf_vector_t *module_config;
 1392     struct ap_conf_vector_t *lookup_defaults;
 1393 
 1395     const char *defn_name;
 1397     unsigned defn_line_number;
 1399     char is_virtual;
 1400 
 1401 
 1402     /* Information for redirects */
 1403 
 1405     apr_port_t port;
 1407     const char *server_scheme;
 1408 
 1409     /* Contact information */
 1410 
 1412     char *server_admin;
 1414     char *server_hostname;
 1415 
 1416     /* Transaction handling */
 1417 
 1419     server_addr_rec *addrs;
 1421     apr_interval_time_t timeout;
 1423     apr_interval_time_t keep_alive_timeout;
 1425     int keep_alive_max;
 1427     int keep_alive;
 1428 
 1430     apr_array_header_t *names;
 1432     apr_array_header_t *wild_names;
 1433 
 1435     const char *path;
 1437     int pathlen;
 1438 
 1440     int limit_req_line;
 1442     int limit_req_fieldsize;
 1444     int limit_req_fields;
 1445 
 1447     void *context;
 1448 
 1452     unsigned int keep_alive_timeout_set:1;
 1453 };
 1454 
 1459 typedef struct ap_sload_t ap_sload_t;
 1460 struct ap_sload_t {
 1461     /* percentage of process/threads ready/idle (0->100)*/
 1462     int idle;
 1463     /* percentage of process/threads busy (0->100) */
 1464     int busy;
 1465     /* total bytes served */
 1466     apr_off_t bytes_served;
 1467     /* total access count */
 1468     unsigned long access_count;
 1469 };
 1470 
 1475 typedef struct ap_loadavg_t ap_loadavg_t;
 1476 struct ap_loadavg_t {
 1477     /* current loadavg, ala getloadavg() */
 1478     float loadavg;
 1479     /* 5 min loadavg */
 1480     float loadavg5;
 1481     /* 15 min loadavg */
 1482     float loadavg15;
 1483 };
 1484 
 1494 AP_DECLARE(const char *) ap_context_document_root(request_rec *r);
 1495 
 1501 AP_DECLARE(const char *) ap_context_prefix(request_rec *r);
 1502 
 1511 AP_DECLARE(void) ap_set_context_info(request_rec *r, const char *prefix,
 1512                                      const char *document_root);
 1513 
 1519 AP_DECLARE(void) ap_set_document_root(request_rec *r, const char *document_root);
 1520 
 1528 AP_DECLARE(char *) ap_field_noparam(apr_pool_t *p, const char *intype);
 1529 
 1538 AP_DECLARE(char *) ap_ht_time(apr_pool_t *p, apr_time_t t, const char *fmt, int gmt);
 1539 
 1540 /* String handling. The *_nc variants allow you to use non-const char **s as
 1541    arguments (unfortunately C won't automatically convert a char ** to a const
 1542    char **) */
 1543 
 1551 AP_DECLARE(char *) ap_getword(apr_pool_t *p, const char **line, char stop);
 1552 
 1561 AP_DECLARE(char *) ap_getword_nc(apr_pool_t *p, char **line, char stop);
 1562 
 1570 AP_DECLARE(char *) ap_getword_white(apr_pool_t *p, const char **line);
 1571 
 1580 AP_DECLARE(char *) ap_getword_white_nc(apr_pool_t *p, char **line);
 1581 
 1590 AP_DECLARE(char *) ap_getword_nulls(apr_pool_t *p, const char **line,
 1591                                     char stop);
 1592 
 1602 AP_DECLARE(char *) ap_getword_nulls_nc(apr_pool_t *p, char **line, char stop);
 1603 
 1610 AP_DECLARE(char *) ap_getword_conf(apr_pool_t *p, const char **line);
 1611 
 1619 AP_DECLARE(char *) ap_getword_conf_nc(apr_pool_t *p, char **line);
 1620 
 1628 AP_DECLARE(char *) ap_getword_conf2(apr_pool_t *p, const char **line);
 1629 
 1638 AP_DECLARE(char *) ap_getword_conf2_nc(apr_pool_t *p, char **line);
 1639 
 1650 AP_DECLARE(const char *) ap_resolve_env(apr_pool_t *p, const char * word);
 1651 
 1661 AP_DECLARE(const char *) ap_size_list_item(const char **field, int *len);
 1662 
 1673 AP_DECLARE(char *) ap_get_list_item(apr_pool_t *p, const char **field);
 1674 
 1683 AP_DECLARE(int) ap_find_list_item(apr_pool_t *p, const char *line, const char *tok);
 1684 
 1692 AP_DECLARE(int) ap_find_etag_weak(apr_pool_t *p, const char *line, const char *tok);
 1693 
 1701 AP_DECLARE(int) ap_find_etag_strong(apr_pool_t *p, const char *line, const char *tok);
 1702 
 1703 /* Scan a string for field content chars, as defined by RFC7230 section 3.2
 1704  * including VCHAR/obs-text, as well as HT and SP
 1705  * @param ptr The string to scan
 1706  * @return A pointer to the first (non-HT) ASCII ctrl character.
 1707  * @note lws and trailing whitespace are scanned, the caller is responsible
 1708  * for trimming leading and trailing whitespace
 1709  */
 1710 AP_DECLARE(const char *) ap_scan_http_field_content(const char *ptr);
 1711 
 1712 /* Scan a string for token characters, as defined by RFC7230 section 3.2.6 
 1713  * @param ptr The string to scan
 1714  * @return A pointer to the first non-token character.
 1715  */
 1716 AP_DECLARE(const char *) ap_scan_http_token(const char *ptr);
 1717 
 1718 /* Scan a string for visible ASCII (0x21-0x7E) or obstext (0x80+)
 1719  * and return a pointer to the first SP/CTL/NUL character encountered.
 1720  * @param ptr The string to scan
 1721  * @return A pointer to the first SP/CTL character.
 1722  */
 1723 AP_DECLARE(const char *) ap_scan_vchar_obstext(const char *ptr);
 1724 
 1738 AP_DECLARE(const char *) ap_parse_token_list_strict(apr_pool_t *p, const char *tok,
 1739                                                     apr_array_header_t **tokens,
 1740                                                     int skip_invalid);
 1741 
 1752 AP_DECLARE(char *) ap_get_token(apr_pool_t *p, const char **accept_line, int accept_white);
 1753 
 1761 AP_DECLARE(int) ap_find_token(apr_pool_t *p, const char *line, const char *tok);
 1762 
 1770 AP_DECLARE(int) ap_find_last_token(apr_pool_t *p, const char *line, const char *tok);
 1771 
 1777 AP_DECLARE(int) ap_is_url(const char *u);
 1778 
 1784 AP_DECLARE(int) ap_unescape_all(char *url);
 1785 
 1792 AP_DECLARE(int) ap_unescape_url(char *url);
 1793 
 1801 AP_DECLARE(int) ap_unescape_url_keep2f(char *url, int decode_slashes);
 1802 
 1809 AP_DECLARE(int) ap_unescape_urlencoded(char *query);
 1810 
 1816 AP_DECLARE(void) ap_no2slash(char *name)
 1817                  AP_FN_ATTR_NONNULL_ALL;
 1825 AP_DECLARE(void) ap_no2slash_ex(char *name, int is_fs_path)
 1826                  AP_FN_ATTR_NONNULL_ALL;
 1827 
 1828 #define AP_NORMALIZE_ALLOW_RELATIVE     (1u <<  0)
 1829 #define AP_NORMALIZE_NOT_ABOVE_ROOT     (1u <<  1)
 1830 #define AP_NORMALIZE_DECODE_UNRESERVED  (1u <<  2)
 1831 #define AP_NORMALIZE_MERGE_SLASHES      (1u <<  3)
 1832 #define AP_NORMALIZE_DROP_PARAMETERS    (1u <<  4)
 1833 
 1841 AP_DECLARE(int) ap_normalize_path(char *path, unsigned int flags)
 1842                 AP_FN_ATTR_NONNULL((1));
 1843 
 1849 AP_DECLARE(void) ap_getparents(char *name)
 1850                  AP_FN_ATTR_NONNULL_ALL;
 1851 
 1859 AP_DECLARE(char *) ap_escape_path_segment(apr_pool_t *p, const char *s)
 1860                    AP_FN_ATTR_NONNULL_ALL;
 1861 
 1869 AP_DECLARE(char *) ap_escape_path_segment_buffer(char *c, const char *s)
 1870                    AP_FN_ATTR_NONNULL_ALL;
 1871 
 1882 AP_DECLARE(char *) ap_os_escape_path(apr_pool_t *p, const char *path, int partial)
 1883                    AP_FN_ATTR_NONNULL_ALL;
 1884 
 1886 #define ap_escape_uri(ppool,path) ap_os_escape_path(ppool,path,1)
 1887 
 1895 AP_DECLARE(char *) ap_escape_urlencoded(apr_pool_t *p, const char *s)
 1896                    AP_FN_ATTR_NONNULL_ALL;
 1897 
 1905 AP_DECLARE(char *) ap_escape_urlencoded_buffer(char *c, const char *s)
 1906                    AP_FN_ATTR_NONNULL_ALL;
 1907 
 1915 #define ap_escape_html(p,s) ap_escape_html2(p,s,0)
 1916 
 1924 AP_DECLARE(char *) ap_escape_html2(apr_pool_t *p, const char *s, int toasc)
 1925                    AP_FN_ATTR_NONNULL_ALL;
 1926 
 1934 AP_DECLARE(char *) ap_escape_logitem(apr_pool_t *p, const char *str)
 1935                    AP_FN_ATTR_NONNULL((1));
 1936 
 1945 AP_DECLARE(apr_size_t) ap_escape_errorlog_item(char *dest, const char *source,
 1946                                                apr_size_t buflen)
 1947                        AP_FN_ATTR_NONNULL((1));
 1948 
 1957 AP_DECLARE(char *) ap_construct_server(apr_pool_t *p, const char *hostname,
 1958                                     apr_port_t port, const request_rec *r)
 1959                    AP_FN_ATTR_NONNULL((1,4));
 1960 
 1968 AP_DECLARE(char *) ap_escape_shell_cmd(apr_pool_t *p, const char *s)
 1969                    AP_FN_ATTR_NONNULL_ALL;
 1970 
 1976 AP_DECLARE(int) ap_count_dirs(const char *path)
 1977                 AP_FN_ATTR_NONNULL_ALL;
 1978 
 1990 AP_DECLARE(char *) ap_make_dirstr_prefix(char *d, const char *s, int n)
 1991                    AP_FN_ATTR_NONNULL_ALL;
 1992 
 2000 AP_DECLARE(char *) ap_make_dirstr_parent(apr_pool_t *p, const char *s)
 2001                    AP_FN_ATTR_NONNULL_ALL;
 2002 
 2016 AP_DECLARE(char *) ap_make_full_path(apr_pool_t *a, const char *dir, const char *f)
 2017                    AP_FN_ATTR_NONNULL_ALL;
 2018 
 2027 AP_DECLARE(int) ap_os_is_path_absolute(apr_pool_t *p, const char *dir)
 2028                 AP_FN_ATTR_NONNULL_ALL;
 2029 
 2037 AP_DECLARE(int) ap_is_matchexp(const char *str)
 2038                 AP_FN_ATTR_NONNULL_ALL;
 2039 
 2046 AP_DECLARE(int) ap_strcmp_match(const char *str, const char *expected)
 2047                 AP_FN_ATTR_NONNULL_ALL;
 2048 
 2056 AP_DECLARE(int) ap_strcasecmp_match(const char *str, const char *expected)
 2057                 AP_FN_ATTR_NONNULL_ALL;
 2058 
 2066 AP_DECLARE(char *) ap_strcasestr(const char *s1, const char *s2)
 2067                    AP_FN_ATTR_NONNULL_ALL;
 2068 
 2075 AP_DECLARE(const char *) ap_stripprefix(const char *bigstring,
 2076                                         const char *prefix)
 2077                          AP_FN_ATTR_NONNULL_ALL;
 2078 
 2086 AP_DECLARE(char *) ap_pbase64decode(apr_pool_t *p, const char *bufcoded);
 2087 
 2105 AP_DECLARE(apr_status_t) ap_pbase64decode_strict(apr_pool_t *p,
 2106                                                  const char *encoded,
 2107                                                  char **decoded,
 2108                                                  apr_size_t *len);
 2109 
 2117 AP_DECLARE(char *) ap_pbase64encode(apr_pool_t *p, char *string);
 2118 
 2132 AP_DECLARE(ap_regex_t *) ap_pregcomp(apr_pool_t *p, const char *pattern,
 2133                                      int cflags);
 2134 
 2142 AP_DECLARE(void) ap_pregfree(apr_pool_t *p, ap_regex_t *reg);
 2143 
 2157 AP_DECLARE(char *) ap_pregsub(apr_pool_t *p, const char *input,
 2158                               const char *source, apr_size_t nmatch,
 2159                               ap_regmatch_t pmatch[]);
 2160 
 2175 AP_DECLARE(apr_status_t) ap_pregsub_ex(apr_pool_t *p, char **result,
 2176                                        const char *input, const char *source,
 2177                                        apr_size_t nmatch,
 2178                                        ap_regmatch_t pmatch[],
 2179                                        apr_size_t maxlen);
 2180 
 2186 AP_DECLARE(void) ap_content_type_tolower(char *s);
 2187 
 2192 AP_DECLARE(void) ap_str_tolower(char *s);
 2193 
 2198 AP_DECLARE(void) ap_str_toupper(char *s);
 2199 
 2207 AP_DECLARE(int) ap_ind(const char *str, char c);        /* Sigh... */
 2208 
 2216 AP_DECLARE(int) ap_rind(const char *str, char c);
 2217 
 2225 AP_DECLARE(char *) ap_escape_quotes(apr_pool_t *p, const char *instring);
 2226 
 2237 AP_DECLARE(char *) ap_append_pid(apr_pool_t *p, const char *string,
 2238                                  const char *delim);
 2239 
 2247 AP_DECLARE(int) ap_parse_strict_length(apr_off_t *len, const char *str);
 2248 
 2267 AP_DECLARE(apr_status_t) ap_timeout_parameter_parse(
 2268                                                const char *timeout_parameter,
 2269                                                apr_interval_time_t *timeout,
 2270                                                const char *default_time_unit);
 2271 
 2278 AP_DECLARE(int) ap_request_has_body(request_rec *r);
 2279 
 2281 #define AP_TAINT_HTACCESS 0x1
 2282 
 2289 AP_DECLARE(int) ap_request_tainted(request_rec *r, int flags);
 2290 
 2301 AP_DECLARE(apr_status_t) ap_pstr2_alnum(apr_pool_t *p, const char *src,
 2302                                         const char **dest);
 2303 
 2313 AP_DECLARE(apr_status_t) ap_str2_alnum(const char *src, char *dest);
 2314 
 2323 typedef struct {
 2324     const char *name;
 2325     apr_bucket_brigade *value;
 2326 } ap_form_pair_t;
 2327 
 2338 AP_DECLARE(int) ap_parse_form_data(request_rec *r, struct ap_filter_t *f,
 2339                                    apr_array_header_t **ptr,
 2340                                    apr_size_t num, apr_size_t size);
 2341 
 2342 /* Misc system hackery */
 2349 AP_DECLARE(int) ap_is_rdirectory(apr_pool_t *p, const char *name);
 2350 
 2357 AP_DECLARE(int) ap_is_directory(apr_pool_t *p, const char *name);
 2358 
 2359 #ifdef _OSD_POSIX
 2360 extern int os_init_job_environment(server_rec *s, const char *user_name, int one_process);
 2361 #endif /* _OSD_POSIX */
 2362 
 2368 char *ap_get_local_host(apr_pool_t *p);
 2369 
 2376 AP_DECLARE(void) ap_log_assert(const char *szExp, const char *szFile, int nLine)
 2377                             __attribute__((noreturn));
 2378 
 2382 #define ap_assert(exp) ((exp) ? (void)0 : ap_log_assert(#exp,__FILE__,__LINE__))
 2383 
 2391 #ifdef AP_DEBUG
 2392 #define AP_DEBUG_ASSERT(exp) ap_assert(exp)
 2393 #else
 2394 #define AP_DEBUG_ASSERT(exp) ((void)0)
 2395 #endif
 2396 
 2406 #define SIGSTOP_DETACH                  1
 2407 
 2408 #define SIGSTOP_MAKE_CHILD              2
 2409 
 2410 #define SIGSTOP_SPAWN_CHILD             4
 2411 
 2412 #define SIGSTOP_PIPED_LOG_SPAWN         8
 2413 
 2414 #define SIGSTOP_CGI_CHILD               16
 2415 
 2417 #ifdef DEBUG_SIGSTOP
 2418 extern int raise_sigstop_flags;
 2419 #define RAISE_SIGSTOP(x)        do { \
 2420         if (raise_sigstop_flags & SIGSTOP_##x) raise(SIGSTOP);\
 2421     } while (0)
 2422 #else
 2423 #define RAISE_SIGSTOP(x)
 2424 #endif
 2425 
 2432 AP_DECLARE(const char *) ap_psignature(const char *prefix, request_rec *r);
 2433 
 2434   /* The C library has functions that allow const to be silently dropped ...
 2435      these macros detect the drop in maintainer mode, but use the native
 2436      methods for normal builds
 2437 
 2438      Note that on some platforms (e.g., AIX with gcc, Solaris with gcc), string.h needs
 2439      to be included before the macros are defined or compilation will fail.
 2440   */
 2441 #include <string.h>
 2442 
 2443 AP_DECLARE(char *) ap_strchr(char *s, int c);
 2444 AP_DECLARE(const char *) ap_strchr_c(const char *s, int c);
 2445 AP_DECLARE(char *) ap_strrchr(char *s, int c);
 2446 AP_DECLARE(const char *) ap_strrchr_c(const char *s, int c);
 2447 AP_DECLARE(char *) ap_strstr(char *s, const char *c);
 2448 AP_DECLARE(const char *) ap_strstr_c(const char *s, const char *c);
 2449 AP_DECLARE(void *) ap_palloc_debug(apr_pool_t *p, apr_size_t size);
 2450 AP_DECLARE(void *) ap_pcalloc_debug(apr_pool_t *p, apr_size_t size);
 2451 
 2452 #ifdef AP_DEBUG
 2453 
 2454 #undef strchr
 2455 # define strchr(s, c)  ap_strchr(s,c)
 2456 #undef strrchr
 2457 # define strrchr(s, c) ap_strrchr(s,c)
 2458 #undef strstr
 2459 # define strstr(s, c)  ap_strstr(s,c)
 2460 
 2461 #if !defined(AP_DEBUG_NO_ALLOC_POISON) && !APR_POOL_DEBUG
 2462 /*
 2463  * ap_palloc_debug initializes allocated memory to non-zero
 2464  */
 2465 #define apr_palloc     ap_palloc_debug
 2466 /*
 2467  * this is necessary to avoid useless double memset of memory
 2468  * with ap_palloc_debug
 2469  */
 2470 #ifdef apr_pcalloc
 2471 #undef apr_pcalloc
 2472 #endif
 2473 #define apr_pcalloc    ap_pcalloc_debug
 2474 #endif
 2475 
 2476 #else
 2477 
 2479 # define ap_strchr(s, c)     strchr(s, c)
 2480 
 2481 # define ap_strchr_c(s, c)   strchr(s, c)
 2482 
 2483 # define ap_strrchr(s, c)    strrchr(s, c)
 2484 
 2485 # define ap_strrchr_c(s, c)  strrchr(s, c)
 2486 
 2487 # define ap_strstr(s, c)     strstr(s, c)
 2488 
 2489 # define ap_strstr_c(s, c)   strstr(s, c)
 2490 
 2491 #endif
 2492 
 2502 AP_DECLARE(void) ap_random_insecure_bytes(void *buf, apr_size_t size);
 2503 
 2510 AP_DECLARE(apr_uint32_t) ap_random_pick(apr_uint32_t min, apr_uint32_t max);
 2511 
 2515 AP_DECLARE(void) ap_abort_on_oom(void) __attribute__((noreturn));
 2516 
 2523 AP_DECLARE(void *) ap_malloc(size_t size)
 2524                     __attribute__((malloc))
 2525                     AP_FN_ATTR_ALLOC_SIZE(1);
 2526 
 2534 AP_DECLARE(void *) ap_calloc(size_t nelem, size_t size)
 2535                    __attribute__((malloc))
 2536                    AP_FN_ATTR_ALLOC_SIZE2(1,2);
 2537 
 2545 AP_DECLARE(void *) ap_realloc(void *ptr, size_t size)
 2546                    AP_FN_ATTR_WARN_UNUSED_RESULT
 2547                    AP_FN_ATTR_ALLOC_SIZE(2);
 2548 
 2553 AP_DECLARE(void) ap_get_sload(ap_sload_t *ld)
 2554                  AP_FN_ATTR_NONNULL_ALL;
 2555 
 2560 AP_DECLARE(void) ap_get_loadavg(ap_loadavg_t *ld)
 2561                  AP_FN_ATTR_NONNULL_ALL;
 2562 
 2571 AP_DECLARE(void) ap_bin2hex(const void *src, apr_size_t srclen, char *dest)
 2572                  AP_FN_ATTR_NONNULL_ALL;
 2573 
 2586 AP_DECLARE(apr_status_t) ap_password_validate(request_rec *r,
 2587                                               const char *username,
 2588                                               const char *passwd,
 2589                                               const char *hash);
 2590 
 2599 AP_DECLARE(char *) ap_get_exec_line(apr_pool_t *p,
 2600                                     const char *cmd,
 2601                                     const char * const *argv);
 2602 
 2603 
 2604 #define AP_NORESTART APR_OS_START_USEERR + 1
 2605 
 2615 AP_DECLARE(int) ap_array_str_index(const apr_array_header_t *array, 
 2616                                    const char *s,
 2617                                    int start);
 2618 
 2625 AP_DECLARE(int) ap_array_str_contains(const apr_array_header_t *array, 
 2626                                       const char *s);
 2627 
 2640 AP_DECLARE(int) ap_cstr_casecmp(const char *s1, const char *s2);
 2641 
 2654 AP_DECLARE(int) ap_cstr_casecmpn(const char *s1, const char *s2, apr_size_t n);
 2655 
 2659 #define AP_DIR_FLAG_NONE      0
 2660 
 2665 #define AP_DIR_FLAG_OPTIONAL  1
 2666 
 2671 #define AP_DIR_FLAG_RECURSIVE 2
 2672 
 2676 typedef struct ap_dir_match_t ap_dir_match_t;
 2677 
 2681 struct ap_dir_match_t {
 2683     apr_pool_t *p;
 2685     apr_pool_t *ptemp;
 2687     const char *prefix;
 2689     const char *(*cb)(ap_dir_match_t *w, const char *fname);
 2691     void *ctx;
 2693     int flags;
 2695     unsigned int depth;
 2696 };
 2697 
 2718 AP_DECLARE(const char *)ap_dir_nofnmatch(ap_dir_match_t *w, const char *fname)
 2719         __attribute__((nonnull(1,2)));
 2720 
 2739 AP_DECLARE(const char *)ap_dir_fnmatch(ap_dir_match_t *w, const char *path,
 2740         const char *fname) __attribute__((nonnull(1,3)));
 2741 
 2749 AP_DECLARE(int) ap_is_chunked(apr_pool_t *p, const char *line);
 2750 
 2751 #ifdef __cplusplus
 2752 }
 2753 #endif
 2754 
 2755 #endif  /* !APACHE_HTTPD_H */
