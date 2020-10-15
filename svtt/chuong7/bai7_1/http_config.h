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
   26 #ifndef APACHE_HTTP_CONFIG_H
   27 #define APACHE_HTTP_CONFIG_H
   28 
   29 #include "util_cfgtree.h"
   30 #include "ap_config.h"
   31 #include "apr_tables.h"
   32 
   33 #ifdef __cplusplus
   34 extern "C" {
   35 #endif
   36 
   37 /*
   38  * The central data structures around here...
   39  */
   40 
   41 /* Command dispatch structures... */
   42 
   49 enum cmd_how {
   50     RAW_ARGS,           
   51     TAKE1,              
   52     TAKE2,              
   53     ITERATE,            
   56     ITERATE2,           
   59     FLAG,               
   60     NO_ARGS,            
   61     TAKE12,             
   62     TAKE3,              
   63     TAKE23,             
   64     TAKE123,            
   65     TAKE13,             
   66     TAKE_ARGV           
   67 };
   68 
   74 typedef struct cmd_parms_struct cmd_parms;
   75 
   76 #if defined(AP_HAVE_DESIGNATED_INITIALIZER) || defined(DOXYGEN)
   77 
   82 typedef union {
   84     const char *(*no_args) (cmd_parms *parms, void *mconfig);
   86     const char *(*raw_args) (cmd_parms *parms, void *mconfig,
   87                              const char *args);
   89     const char *(*take_argv) (cmd_parms *parms, void *mconfig,
   90                              int argc, char *const argv[]);
   92     const char *(*take1) (cmd_parms *parms, void *mconfig, const char *w);
   94     const char *(*take2) (cmd_parms *parms, void *mconfig, const char *w,
   95                           const char *w2);
   97     const char *(*take3) (cmd_parms *parms, void *mconfig, const char *w,
   98                           const char *w2, const char *w3);
  100     const char *(*flag) (cmd_parms *parms, void *mconfig, int on);
  101 } cmd_func;
  102 
  104 # define AP_NO_ARGS     func.no_args
  105 
  106 # define AP_RAW_ARGS    func.raw_args
  107 
  108 # define AP_TAKE_ARGV   func.take_argv
  109 
  110 # define AP_TAKE1       func.take1
  111 
  112 # define AP_TAKE2       func.take2
  113 
  114 # define AP_TAKE3       func.take3
  115 
  116 # define AP_FLAG        func.flag
  117 
  119 # define AP_INIT_NO_ARGS(directive, func, mconfig, where, help) \
  120     { directive, { .no_args=func }, mconfig, where, NO_ARGS, help }
  121 
  122 # define AP_INIT_RAW_ARGS(directive, func, mconfig, where, help) \
  123     { directive, { .raw_args=func }, mconfig, where, RAW_ARGS, help }
  124 
  125 # define AP_INIT_TAKE_ARGV(directive, func, mconfig, where, help) \
  126     { directive, { .take_argv=func }, mconfig, where, TAKE_ARGV, help }
  127 
  128 # define AP_INIT_TAKE1(directive, func, mconfig, where, help) \
  129     { directive, { .take1=func }, mconfig, where, TAKE1, help }
  130 
  131 # define AP_INIT_ITERATE(directive, func, mconfig, where, help) \
  132     { directive, { .take1=func }, mconfig, where, ITERATE, help }
  133 
  134 # define AP_INIT_TAKE2(directive, func, mconfig, where, help) \
  135     { directive, { .take2=func }, mconfig, where, TAKE2, help }
  136 
  137 # define AP_INIT_TAKE12(directive, func, mconfig, where, help) \
  138     { directive, { .take2=func }, mconfig, where, TAKE12, help }
  139 
  140 # define AP_INIT_ITERATE2(directive, func, mconfig, where, help) \
  141     { directive, { .take2=func }, mconfig, where, ITERATE2, help }
  142 
  143 # define AP_INIT_TAKE13(directive, func, mconfig, where, help) \
  144     { directive, { .take3=func }, mconfig, where, TAKE13, help }
  145 
  146 # define AP_INIT_TAKE23(directive, func, mconfig, where, help) \
  147     { directive, { .take3=func }, mconfig, where, TAKE23, help }
  148 
  149 # define AP_INIT_TAKE123(directive, func, mconfig, where, help) \
  150     { directive, { .take3=func }, mconfig, where, TAKE123, help }
  151 
  152 # define AP_INIT_TAKE3(directive, func, mconfig, where, help) \
  153     { directive, { .take3=func }, mconfig, where, TAKE3, help }
  154 
  155 # define AP_INIT_FLAG(directive, func, mconfig, where, help) \
  156     { directive, { .flag=func }, mconfig, where, FLAG, help }
  157 
  158 #else /* AP_HAVE_DESIGNATED_INITIALIZER */
  159 
  160 typedef const char *(*cmd_func) ();
  161 
  162 # define AP_NO_ARGS  func
  163 # define AP_RAW_ARGS func
  164 # define AP_TAKE_ARGV func
  165 # define AP_TAKE1    func
  166 # define AP_TAKE2    func
  167 # define AP_TAKE3    func
  168 # define AP_FLAG     func
  169 
  170 # define AP_INIT_NO_ARGS(directive, func, mconfig, where, help) \
  171     { directive, func, mconfig, where, NO_ARGS, help }
  172 # define AP_INIT_RAW_ARGS(directive, func, mconfig, where, help) \
  173     { directive, func, mconfig, where, RAW_ARGS, help }
  174 # define AP_INIT_TAKE_ARGV(directive, func, mconfig, where, help) \
  175     { directive, func, mconfig, where, TAKE_ARGV, help }
  176 # define AP_INIT_TAKE1(directive, func, mconfig, where, help) \
  177     { directive, func, mconfig, where, TAKE1, help }
  178 # define AP_INIT_ITERATE(directive, func, mconfig, where, help) \
  179     { directive, func, mconfig, where, ITERATE, help }
  180 # define AP_INIT_TAKE2(directive, func, mconfig, where, help) \
  181     { directive, func, mconfig, where, TAKE2, help }
  182 # define AP_INIT_TAKE12(directive, func, mconfig, where, help) \
  183     { directive, func, mconfig, where, TAKE12, help }
  184 # define AP_INIT_ITERATE2(directive, func, mconfig, where, help) \
  185     { directive, func, mconfig, where, ITERATE2, help }
  186 # define AP_INIT_TAKE13(directive, func, mconfig, where, help) \
  187     { directive, func, mconfig, where, TAKE13, help }
  188 # define AP_INIT_TAKE23(directive, func, mconfig, where, help) \
  189     { directive, func, mconfig, where, TAKE23, help }
  190 # define AP_INIT_TAKE123(directive, func, mconfig, where, help) \
  191     { directive, func, mconfig, where, TAKE123, help }
  192 # define AP_INIT_TAKE3(directive, func, mconfig, where, help) \
  193     { directive, func, mconfig, where, TAKE3, help }
  194 # define AP_INIT_FLAG(directive, func, mconfig, where, help) \
  195     { directive, func, mconfig, where, FLAG, help }
  196 
  197 #endif /* AP_HAVE_DESIGNATED_INITIALIZER */
  198 
  203 typedef struct command_struct command_rec;
  204 struct command_struct {
  206     const char *name;
  208     cmd_func func;
  210     void *cmd_data;
  212     int req_override;
  214     enum cmd_how args_how;
  215 
  217     const char *errmsg;
  218 };
  219 
  228 #define OR_NONE 0             
  229 #define OR_LIMIT 1           
  231 #define OR_OPTIONS 2         
  233 #define OR_FILEINFO 4        
  235 #define OR_AUTHCFG 8         
  237 #define OR_INDEXES 16        
  239 #define OR_UNSET 32          
  240 #define ACCESS_CONF 64       
  241 #define RSRC_CONF 128        
  242 #define EXEC_ON_READ 256     
  245 /* Flags to determine whether syntax errors in .htaccess should be
  246  * treated as nonfatal (log and ignore errors)
  247  */
  248 #define NONFATAL_OVERRIDE 512    /* Violation of AllowOverride rule */
  249 #define NONFATAL_UNKNOWN 1024    /* Unrecognised directive */
  250 #define NONFATAL_ALL (NONFATAL_OVERRIDE|NONFATAL_UNKNOWN)
  251 
  252 #define PROXY_CONF 2048      
  255 #define OR_ALL (OR_LIMIT|OR_OPTIONS|OR_FILEINFO|OR_AUTHCFG|OR_INDEXES)
  256 
  264 #define DECLINE_CMD "\a\b"
  265 
  267 typedef struct ap_configfile_t ap_configfile_t;
  268 struct ap_configfile_t {
  270     apr_status_t (*getch) (char *ch, void *param);
  272     apr_status_t (*getstr) (void *buf, apr_size_t bufsiz, void *param);
  274     apr_status_t (*close) (void *param);
  276     void *param;
  278     const char *name;
  280     unsigned line_number;
  281 };
  282 
  288 struct cmd_parms_struct {
  290     void *info;
  292     int override;
  294     int override_opts;
  296     apr_table_t *override_list;
  298     ap_method_mask_t limited;
  300     apr_array_header_t *limited_xmethods;
  302     ap_method_list_t *xlimited;
  303 
  305     ap_configfile_t *config_file;
  307     ap_directive_t *directive;
  308 
  310     apr_pool_t *pool;
  313     apr_pool_t *temp_pool;
  315     server_rec *server;
  322     char *path;
  324     const command_rec *cmd;
  325 
  327     struct ap_conf_vector_t *context;
  329     const ap_directive_t *err_directive;
  330  
  333     ap_directive_t *parent;
  334 };
  335 
  339 #define AP_MODULE_FLAG_NONE         (0)
  340 #define AP_MODULE_FLAG_ALWAYS_MERGE (1 << 0)
  341 
  347 typedef struct module_struct module;
  348 struct module_struct {
  352     int version;
  355     int minor_version;
  357     int module_index;
  358 
  360     const char *name;
  362     void *dynamic_load_handle;
  363 
  367     struct module_struct *next;
  368 
  371     unsigned long magic;
  372 
  377     void (*rewrite_args) (process_rec *process);
  384     void *(*create_dir_config) (apr_pool_t *p, char *dir);
  392     void *(*merge_dir_config) (apr_pool_t *p, void *base_conf, void *new_conf);
  399     void *(*create_server_config) (apr_pool_t *p, server_rec *s);
  407     void *(*merge_server_config) (apr_pool_t *p, void *base_conf,
  408                                   void *new_conf);
  409 
  412     const command_rec *cmds;
  413 
  420     void (*register_hooks) (apr_pool_t *p);
  421 
  423     int flags;
  424 };
  425 
  434 #ifdef AP_MAYBE_UNUSED
  435 #elif defined(__GNUC__)
  436 # define AP_MAYBE_UNUSED(x) x __attribute__((unused)) 
  437 #elif defined(__LCLINT__)
  438 # define AP_MAYBE_UNUSED(x) /*@unused@*/ x  
  439 #else
  440 # define AP_MAYBE_UNUSED(x) x
  441 #endif
  442     
  456 #define APLOG_USE_MODULE(foo) \
  457     extern module AP_MODULE_DECLARE_DATA foo##_module;                  \
  458     AP_MAYBE_UNUSED(static int * const aplog_module_index) = &(foo##_module.module_index)
  459 
  467 #define AP_DECLARE_MODULE(foo) \
  468     APLOG_USE_MODULE(foo);                         \
  469     module AP_MODULE_DECLARE_DATA foo##_module
  470 
  486 #define STANDARD_MODULE_STUFF   this_module_needs_to_be_ported_to_apache_2_0
  487 
  489 #define STANDARD20_MODULE_STUFF MODULE_MAGIC_NUMBER_MAJOR, \
  490                                 MODULE_MAGIC_NUMBER_MINOR, \
  491                                 -1, \
  492                                 __FILE__, \
  493                                 NULL, \
  494                                 NULL, \
  495                                 MODULE_MAGIC_COOKIE, \
  496                                 NULL      /* rewrite args spot */
  497 
  499 #define MPM20_MODULE_STUFF      MODULE_MAGIC_NUMBER_MAJOR, \
  500                                 MODULE_MAGIC_NUMBER_MINOR, \
  501                                 -1, \
  502                                 __FILE__, \
  503                                 NULL, \
  504                                 NULL, \
  505                                 MODULE_MAGIC_COOKIE
  506 
  509 /* CONFIGURATION VECTOR FUNCTIONS */
  510 
  512 typedef struct ap_conf_vector_t ap_conf_vector_t;
  513 
  522 AP_DECLARE(void *) ap_get_module_config(const ap_conf_vector_t *cv,
  523                                         const module *m);
  524 
  533 AP_DECLARE(void) ap_set_module_config(ap_conf_vector_t *cv, const module *m,
  534                                       void *val);
  535 
  539 #define AP_MODULE_FLAGS_MMN_MAJOR 20161018
  540 #define AP_MODULE_FLAGS_MMN_MINOR 7
  541 #define AP_MODULE_HAS_FLAGS(m) \
  542         AP_MODULE_MAGIC_AT_LEAST(AP_MODULE_FLAGS_MMN_MAJOR, \
  543                                  AP_MODULE_FLAGS_MMN_MINOR)
  544 
  549 AP_DECLARE(int) ap_get_module_flags(const module *m);
  550 
  551 #if !defined(AP_DEBUG)
  552 
  553 #define ap_get_module_config(v,m)       \
  554     (((void **)(v))[(m)->module_index])
  555 #define ap_set_module_config(v,m,val)   \
  556     ((((void **)(v))[(m)->module_index]) = (val))
  557 
  558 #endif /* AP_DEBUG */
  559 
  560 
  567 AP_DECLARE(int) ap_get_server_module_loglevel(const server_rec *s, int index);
  568 
  575 AP_DECLARE(int) ap_get_conn_module_loglevel(const conn_rec *c, int index);
  576 
  585 AP_DECLARE(int) ap_get_conn_server_module_loglevel(const conn_rec *c,
  586                                                    const server_rec *s,
  587                                                    int index);
  588 
  595 AP_DECLARE(int) ap_get_request_module_loglevel(const request_rec *r, int index);
  596 
  604 AP_DECLARE(void) ap_set_module_loglevel(apr_pool_t *p, struct ap_logconf *l,
  605                                         int index, int level);
  606 
  607 #if !defined(AP_DEBUG)
  608 
  609 #define ap_get_conn_logconf(c)                     \
  610     ((c)->log             ? (c)->log             : \
  611      &(c)->base_server->log)
  612 
  613 #define ap_get_conn_server_logconf(c,s)                             \
  614     ( ( (c)->log != &(c)->base_server->log && (c)->log != NULL )  ? \
  615       (c)->log                                                    : \
  616       &(s)->log )
  617 
  618 #define ap_get_request_logconf(r)                  \
  619     ((r)->log             ? (r)->log             : \
  620      (r)->connection->log ? (r)->connection->log : \
  621      &(r)->server->log)
  622 
  623 #define ap_get_module_loglevel(l,i)                                     \
  624     (((i) < 0 || (l)->module_levels == NULL || (l)->module_levels[i] < 0) ?  \
  625      (l)->level :                                                         \
  626      (l)->module_levels[i])
  627 
  628 #define ap_get_server_module_loglevel(s,i)  \
  629     (ap_get_module_loglevel(&(s)->log,i))
  630 
  631 #define ap_get_conn_module_loglevel(c,i)  \
  632     (ap_get_module_loglevel(ap_get_conn_logconf(c),i))
  633 
  634 #define ap_get_conn_server_module_loglevel(c,s,i)  \
  635     (ap_get_module_loglevel(ap_get_conn_server_logconf(c,s),i))
  636 
  637 #define ap_get_request_module_loglevel(r,i)  \
  638     (ap_get_module_loglevel(ap_get_request_logconf(r),i))
  639 
  640 #endif /* AP_DEBUG */
  641 
  647 AP_DECLARE(void) ap_reset_module_loglevels(struct ap_logconf *l, int val);
  648 
  656 AP_DECLARE_NONSTD(const char *) ap_set_string_slot(cmd_parms *cmd,
  657                                                    void *struct_ptr,
  658                                                    const char *arg);
  659 
  667 AP_DECLARE_NONSTD(const char *) ap_set_int_slot(cmd_parms *cmd,
  668                                                 void *struct_ptr,
  669                                                 const char *arg);
  670 
  677 AP_DECLARE(const char *) ap_parse_log_level(const char *str, int *val);
  678 
  689 AP_DECLARE(int) ap_method_is_limited(cmd_parms *cmd, const char *method);
  690 
  699 AP_DECLARE_NONSTD(const char *) ap_set_string_slot_lower(cmd_parms *cmd,
  700                                                          void *struct_ptr,
  701                                                          const char *arg);
  709 AP_DECLARE_NONSTD(const char *) ap_set_flag_slot(cmd_parms *cmd,
  710                                                  void *struct_ptr,
  711                                                  int arg);
  719 AP_DECLARE_NONSTD(const char *) ap_set_flag_slot_char(cmd_parms *cmd,
  720                                                       void *struct_ptr,
  721                                                       int arg);
  729 AP_DECLARE_NONSTD(const char *) ap_set_file_slot(cmd_parms *cmd,
  730                                                  void *struct_ptr,
  731                                                  const char *arg);
  744 AP_DECLARE_NONSTD(const char *) ap_set_deprecated(cmd_parms *cmd,
  745                                                   void *struct_ptr,
  746                                                   const char *arg);
  753 AP_DECLARE(char *) ap_server_root_relative(apr_pool_t *p, const char *fname);
  754 
  761 AP_DECLARE(char *) ap_runtime_dir_relative(apr_pool_t *p, const char *fname);
  762 
  769 AP_DECLARE(char *) ap_state_dir_relative(apr_pool_t *p, const char *fname);
  770 
  771 /* Finally, the hook for dynamically loading modules in... */
  772 
  779 AP_DECLARE(const char *) ap_add_module(module *m, apr_pool_t *p,
  780                                        const char *s);
  781 
  790 AP_DECLARE(void) ap_remove_module(module *m);
  797 AP_DECLARE(const char *) ap_add_loaded_module(module *mod, apr_pool_t *p,
  798                                               const char *s);
  803 AP_DECLARE(void) ap_remove_loaded_module(module *mod);
  809 AP_DECLARE(const char *) ap_find_module_name(module *m);
  815 AP_DECLARE(const char *) ap_find_module_short_name(int module_index);
  821 AP_DECLARE(module *) ap_find_linked_module(const char *name);
  822 
  829 AP_DECLARE(apr_status_t) ap_pcfg_openfile(ap_configfile_t **ret_cfg,
  830                                           apr_pool_t *p, const char *name);
  831 
  841 AP_DECLARE(ap_configfile_t *) ap_pcfg_open_custom(apr_pool_t *p,
  842     const char *descr,
  843     void *param,
  844     apr_status_t (*getc_func) (char *ch, void *param),
  845     apr_status_t (*gets_func) (void *buf, apr_size_t bufsiz, void *param),
  846     apr_status_t (*close_func) (void *param));
  847 
  856 AP_DECLARE(apr_status_t) ap_cfg_getline(char *buf, apr_size_t bufsize, ap_configfile_t *cfp);
  857 
  864 AP_DECLARE(apr_status_t) ap_cfg_getc(char *ch, ap_configfile_t *cfp);
  865 
  871 AP_DECLARE(int) ap_cfg_closefile(ap_configfile_t *cfp);
  872 
  881 AP_DECLARE(const char *) ap_pcfg_strerror(apr_pool_t *p, ap_configfile_t *cfp,
  882                                           apr_status_t rc);
  883 
  893 AP_DECLARE(const char *) ap_soak_end_container(cmd_parms *cmd, const char *directive);
  894 
  908 AP_DECLARE(const char *) ap_build_cont_config(apr_pool_t *p,
  909                                               apr_pool_t *temp_pool,
  910                                               cmd_parms *parms,
  911                                               ap_directive_t **current,
  912                                               ap_directive_t **curr_parent,
  913                                               const char *orig_directive);
  914 
  925 AP_DECLARE(const char *) ap_build_config(cmd_parms *parms,
  926                                          apr_pool_t *conf_pool,
  927                                          apr_pool_t *temp_pool,
  928                                          ap_directive_t **conftree);
  929 
  937 AP_DECLARE(const char *) ap_walk_config(ap_directive_t *conftree,
  938                                         cmd_parms *parms,
  939                                         ap_conf_vector_t *section_vector);
  940 
  952 AP_DECLARE(ap_dir_match_t *)ap_dir_cfgmatch(cmd_parms *cmd, int flags,
  953         const char *(*cb)(ap_dir_match_t *w, const char *fname), void *ctx)
  954         __attribute__((nonnull(1,3)));
  955 
  966 AP_DECLARE(const char *) ap_check_cmd_context(cmd_parms *cmd,
  967                                               unsigned forbidden);
  968 
  969 #define  NOT_IN_VIRTUALHOST     0x01 
  970 #define  NOT_IN_LIMIT           0x02 
  971 #define  NOT_IN_DIRECTORY       0x04 
  972 #define  NOT_IN_LOCATION        0x08 
  973 #define  NOT_IN_FILES           0x10 
  974 #define  NOT_IN_HTACCESS        0x20 
  975 #define  NOT_IN_PROXY           0x40 
  977 #define  NOT_IN_DIR_LOC_FILE    (NOT_IN_DIRECTORY|NOT_IN_LOCATION|NOT_IN_FILES)
  978 
  979 #define  NOT_IN_DIR_CONTEXT     (NOT_IN_LIMIT|NOT_IN_DIR_LOC_FILE|NOT_IN_PROXY)
  980 
  981 #define  GLOBAL_ONLY            (NOT_IN_VIRTUALHOST|NOT_IN_DIR_CONTEXT)
  982 
  988 typedef struct {
  989     const char *name;
  990     module *modp;
  991 } ap_module_symbol_t;
  992 
  997 AP_DECLARE_DATA extern module *ap_top_module;
  998 
 1003 AP_DECLARE_DATA extern module *ap_prelinked_modules[];
 1008 AP_DECLARE_DATA extern ap_module_symbol_t ap_prelinked_module_symbols[];
 1013 AP_DECLARE_DATA extern module *ap_preloaded_modules[];
 1018 AP_DECLARE_DATA extern module **ap_loaded_modules;
 1019 
 1020 /* For mod_so.c... */
 1026 AP_DECLARE(void) ap_single_module_configure(apr_pool_t *p, server_rec *s,
 1027                                             module *m);
 1028 
 1029 /* For http_main.c... */
 1034 AP_DECLARE(const char *) ap_setup_prelinked_modules(process_rec *process);
 1035 
 1041 AP_DECLARE(void) ap_show_directives(void);
 1042 
 1049 AP_DECLARE(int) ap_exists_directive(apr_pool_t *p, const char *name);
 1050 
 1054 AP_DECLARE(void) ap_show_modules(void);
 1055 
 1060 AP_DECLARE(const char *) ap_show_mpm(void);
 1061 
 1070 AP_DECLARE(server_rec *) ap_read_config(process_rec *process,
 1071                                         apr_pool_t *temp_pool,
 1072                                         const char *config_name,
 1073                                         ap_directive_t **conftree);
 1074 
 1079 AP_DECLARE(void) ap_run_rewrite_args(process_rec *process);
 1080 
 1086 AP_DECLARE(void) ap_register_hooks(module *m, apr_pool_t *p);
 1087 
 1093 AP_DECLARE(void) ap_fixup_virtual_hosts(apr_pool_t *p,
 1094                                         server_rec *main_server);
 1095 
 1102 AP_DECLARE(void) ap_reserve_module_slots(int count);
 1103 
 1111 AP_DECLARE(void) ap_reserve_module_slots_directive(const char *directive);
 1112 
 1113 /* For http_request.c... */
 1114 
 1120 AP_DECLARE(ap_conf_vector_t*) ap_create_request_config(apr_pool_t *p);
 1121 
 1127 AP_CORE_DECLARE(ap_conf_vector_t *) ap_create_per_dir_config(apr_pool_t *p);
 1128 
 1135 AP_CORE_DECLARE(ap_conf_vector_t*) ap_merge_per_dir_configs(apr_pool_t *p,
 1136                                            ap_conf_vector_t *base,
 1137                                            ap_conf_vector_t *new_conf);
 1138 
 1145 AP_DECLARE(struct ap_logconf *) ap_new_log_config(apr_pool_t *p,
 1146                                                   const struct ap_logconf *old);
 1147 
 1154 AP_DECLARE(void) ap_merge_log_config(const struct ap_logconf *old_conf,
 1155                                      struct ap_logconf *new_conf);
 1156 
 1157 /* For http_connection.c... */
 1163 AP_CORE_DECLARE(ap_conf_vector_t*) ap_create_conn_config(apr_pool_t *p);
 1164 
 1165 /* For http_core.c... (&lt;Directory&gt; command and virtual hosts) */
 1166 
 1178 AP_CORE_DECLARE(int) ap_parse_htaccess(ap_conf_vector_t **result,
 1179                                        request_rec *r,
 1180                                        int override,
 1181                                        int override_opts,
 1182                                        apr_table_t *override_list,
 1183                                        const char *path,
 1184                                        const char *access_name);
 1185 
 1194 AP_CORE_DECLARE(const char *) ap_init_virtual_host(apr_pool_t *p,
 1195                                                    const char *hostname,
 1196                                                    server_rec *main_server,
 1197                                                    server_rec **ps);
 1198 
 1207 AP_DECLARE(const char *) ap_process_resource_config(server_rec *s,
 1208                                                     const char *fname,
 1209                                                     ap_directive_t **conftree,
 1210                                                     apr_pool_t *p,
 1211                                                     apr_pool_t *ptemp);
 1212 
 1223 AP_DECLARE(const char *) ap_process_fnmatch_configs(server_rec *s,
 1224                                                     const char *fname,
 1225                                                     ap_directive_t **conftree,
 1226                                                     apr_pool_t *p,
 1227                                                     apr_pool_t *ptemp,
 1228                                                     int optional);
 1229 
 1238 AP_DECLARE(int) ap_process_config_tree(server_rec *s,
 1239                                        ap_directive_t *conftree,
 1240                                        apr_pool_t *p,
 1241                                        apr_pool_t *ptemp);
 1242 
 1249 AP_DECLARE(void *) ap_retained_data_create(const char *key, apr_size_t size);
 1250 
 1256 AP_DECLARE(void *) ap_retained_data_get(const char *key);
 1257 
 1258 /* Module-method dispatchers, also for http_request.c */
 1265 AP_CORE_DECLARE(int) ap_invoke_handler(request_rec *r);
 1266 
 1267 /* for mod_perl */
 1268 
 1275 AP_CORE_DECLARE(const command_rec *) ap_find_command(const char *name,
 1276                                                      const command_rec *cmds);
 1277 
 1287 AP_CORE_DECLARE(const command_rec *) ap_find_command_in_modules(const char *cmd_name,
 1288                                                                 module **mod);
 1289 
 1301 AP_CORE_DECLARE(void *) ap_set_config_vectors(server_rec *server,
 1302                                               ap_conf_vector_t *section_vector,
 1303                                               const char *section,
 1304                                               module *mod, apr_pool_t *pconf);
 1305 
 1306   /* Hooks */
 1307 
 1314 AP_DECLARE_HOOK(int,header_parser,(request_rec *r))
 1315 
 1324 AP_DECLARE_HOOK(int,pre_config,(apr_pool_t *pconf,apr_pool_t *plog,
 1325                                 apr_pool_t *ptemp))
 1326 
 1336 AP_DECLARE_HOOK(int,check_config,(apr_pool_t *pconf, apr_pool_t *plog,
 1337                                   apr_pool_t *ptemp, server_rec *s))
 1338 
 1349 AP_DECLARE_HOOK(void,test_config,(apr_pool_t *pconf, server_rec *s))
 1350 
 1360 AP_DECLARE_HOOK(int,post_config,(apr_pool_t *pconf,apr_pool_t *plog,
 1361                                  apr_pool_t *ptemp,server_rec *s))
 1362 
 1372 AP_DECLARE_HOOK(int,open_logs,(apr_pool_t *pconf,apr_pool_t *plog,
 1373                                apr_pool_t *ptemp,server_rec *s))
 1374 
 1381 AP_DECLARE_HOOK(void,child_init,(apr_pool_t *pchild, server_rec *s))
 1382 
 1389 AP_DECLARE_HOOK(int,handler,(request_rec *r))
 1390 
 1403 AP_DECLARE_HOOK(int,quick_handler,(request_rec *r, int lookup_uri))
 1404 
 1411 AP_DECLARE_HOOK(void,optional_fn_retrieve,(void))
 1412 
 1428 AP_DECLARE_HOOK(apr_status_t,open_htaccess,
 1429                 (request_rec *r, const char *dir_name, const char *access_name,
 1430                  ap_configfile_t **conffile, const char **full_name))
 1431 
 1435 apr_status_t ap_open_htaccess(request_rec *r, const char *dir_name,
 1436         const char *access_name, ap_configfile_t **conffile,
 1437         const char **full_name);
 1438 
 1445 AP_DECLARE_NONSTD(apr_status_t) ap_pool_cleanup_set_null(void *data);
 1446 
 1447 #ifdef __cplusplus
 1448 }
 1449 #endif
 1450 
 1451 #endif  /* !APACHE_HTTP_CONFIG_H */
