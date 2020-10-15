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
   22 #ifndef AP_CONFIG_H
   23 #define AP_CONFIG_H
   24 
   25 #include "ap_hooks.h"
   26 
   27 /* Although this file doesn't declare any hooks, declare the exports group here */
   33 #ifdef DOXYGEN
   34 /* define these just so doxygen documents them */
   35 
   47 # define AP_DECLARE_STATIC
   48 
   54 # define AP_DECLARE_EXPORT
   55 
   56 #endif /* def DOXYGEN */
   57 
   58 #if !defined(WIN32)
   59 
   67 #define AP_DECLARE(type)            type
   68 
   77 #define AP_DECLARE_NONSTD(type)     type
   78 
   89 #define AP_DECLARE_DATA
   90 
   91 #elif defined(AP_DECLARE_STATIC)
   92 #define AP_DECLARE(type)            type __stdcall
   93 #define AP_DECLARE_NONSTD(type)     type
   94 #define AP_DECLARE_DATA
   95 #elif defined(AP_DECLARE_EXPORT)
   96 #define AP_DECLARE(type)            __declspec(dllexport) type __stdcall
   97 #define AP_DECLARE_NONSTD(type)     __declspec(dllexport) type
   98 #define AP_DECLARE_DATA             __declspec(dllexport)
   99 #else
  100 #define AP_DECLARE(type)            __declspec(dllimport) type __stdcall
  101 #define AP_DECLARE_NONSTD(type)     __declspec(dllimport) type
  102 #define AP_DECLARE_DATA             __declspec(dllimport)
  103 #endif
  104 
  105 #if !defined(WIN32)
  106 
  115 #define APREQ_DECLARE(d)                APR_DECLARE(d)
  116 
  125 #define APREQ_DECLARE_NONSTD(d)         APR_DECLARE_NONSTD(d)
  126 
  136 #define APREQ_DECLARE_DATA
  137 #elif defined (APREQ_DECLARE_STATIC)
  138 #define APREQ_DECLARE(type)             type __stdcall
  139 #define APREQ_DECLARE_NONSTD(type)      type
  140 #define APREQ_DECLARE_DATA
  141 #elif defined (APREQ_DECLARE_EXPORT)
  142 #define APREQ_DECLARE(type)             __declspec(dllexport) type __stdcall
  143 #define APREQ_DECLARE_NONSTD(type)      __declspec(dllexport) type
  144 #define APREQ_DECLARE_DATA              __declspec(dllexport)
  145 #else
  146 #define APREQ_DECLARE(type)             __declspec(dllimport) type __stdcall
  147 #define APREQ_DECLARE_NONSTD(type)      __declspec(dllimport) type
  148 #define APREQ_DECLARE_DATA              __declspec(dllimport)
  149 #endif
  150 
  151 #if !defined(WIN32) || defined(AP_MODULE_DECLARE_STATIC)
  152 
  161 #if defined(WIN32)
  162 #define AP_MODULE_DECLARE(type)            type __stdcall
  163 #else
  164 #define AP_MODULE_DECLARE(type)            type
  165 #endif
  166 #define AP_MODULE_DECLARE_NONSTD(type)     type
  167 #define AP_MODULE_DECLARE_DATA
  168 #else
  169 
  176 #define AP_MODULE_DECLARE_EXPORT
  177 #define AP_MODULE_DECLARE(type)          __declspec(dllexport) type __stdcall
  178 #define AP_MODULE_DECLARE_NONSTD(type)   __declspec(dllexport) type
  179 #define AP_MODULE_DECLARE_DATA           __declspec(dllexport)
  180 #endif
  181 
  182 #include "os.h"
  183 #if (!defined(WIN32) && !defined(NETWARE)) || defined(__MINGW32__)
  184 #include "ap_config_auto.h"
  185 #endif
  186 #include "ap_config_layout.h"
  187 
  188 /* Where the main/parent process's pid is logged */
  189 #ifndef DEFAULT_PIDLOG
  190 #define DEFAULT_PIDLOG "httpd.pid"
  191 #endif
  192 
  193 #if defined(NETWARE)
  194 #define AP_NONBLOCK_WHEN_MULTI_LISTEN 1
  195 #endif
  196 
  197 #if defined(AP_ENABLE_DTRACE) && HAVE_SYS_SDT_H
  198 #include <sys/sdt.h>
  199 #else
  200 #undef _DTRACE_VERSION
  201 #endif
  202 
  203 #ifdef _DTRACE_VERSION
  204 #include "apache_probes.h"
  205 #else
  206 #include "apache_noprobes.h"
  207 #endif
  208 
  209 /* If APR has OTHER_CHILD logic, use reliable piped logs. */
  210 #if APR_HAS_OTHER_CHILD
  211 #define AP_HAVE_RELIABLE_PIPED_LOGS TRUE
  212 #endif
  213 
  214 #if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 199901L
  215 #define AP_HAVE_C99
  216 #endif
  217 
  218 /* Presume that the compiler supports C99-style designated
  219  * initializers if using GCC (but not G++), or for any other compiler
  220  * which claims C99 support. */
  221 #if (defined(__GNUC__) && !defined(__cplusplus)) || defined(AP_HAVE_C99)
  222 #define AP_HAVE_DESIGNATED_INITIALIZER
  223 #endif
  224 
  225 #ifndef __has_attribute         /* check for supported attributes on clang */
  226 #define __has_attribute(x) 0
  227 #endif
  228 #if (defined(__GNUC__) && __GNUC__ >= 4) || __has_attribute(sentinel)
  229 #define AP_FN_ATTR_SENTINEL __attribute__((sentinel))
  230 #else
  231 #define AP_FN_ATTR_SENTINEL
  232 #endif
  233 
  234 #if ( defined(__GNUC__) &&                                        \
  235       (__GNUC__ >= 4 || ( __GNUC__ == 3 && __GNUC_MINOR__ >= 4))) \
  236     || __has_attribute(warn_unused_result)
  237 #define AP_FN_ATTR_WARN_UNUSED_RESULT   __attribute__((warn_unused_result))
  238 #else
  239 #define AP_FN_ATTR_WARN_UNUSED_RESULT
  240 #endif
  241 
  242 #if ( defined(__GNUC__) &&                                        \
  243       (__GNUC__ >= 4 && __GNUC_MINOR__ >= 3))                     \
  244     || __has_attribute(alloc_size)
  245 #define AP_FN_ATTR_ALLOC_SIZE(x)     __attribute__((alloc_size(x)))
  246 #define AP_FN_ATTR_ALLOC_SIZE2(x,y)  __attribute__((alloc_size(x,y)))
  247 #else
  248 #define AP_FN_ATTR_ALLOC_SIZE(x)
  249 #define AP_FN_ATTR_ALLOC_SIZE2(x,y)
  250 #endif
  251 
  252 #if ( defined(__GNUC__) &&                                        \
  253       (__GNUC__ >= 4 || ( __GNUC__ == 3 && __GNUC_MINOR__ >= 3))) \
  254     || __has_attribute(nonnull)
  255 /* all pointer arguments */
  256 #define AP_FN_ATTR_NONNULL_ALL  __attribute__((nonnull))
  257 /* listed arguments, use with double braces: AP_FN_ATTR_NONNULL((1,3,6)) */
  258 #define AP_FN_ATTR_NONNULL(x)   __attribute__((nonnull x))
  259 #else
  260 #define AP_FN_ATTR_NONNULL_ALL
  261 #define AP_FN_ATTR_NONNULL(x)
  262 #endif
  263 
  264 
  265 #endif /* AP_CONFIG_H */
