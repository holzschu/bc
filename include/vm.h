/*
 * *****************************************************************************
 *
 * SPDX-License-Identifier: BSD-2-Clause
 *
 * Copyright (c) 2018-2021 Gavin D. Howard and contributors.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * *****************************************************************************
 *
 * Definitions for bc's VM.
 *
 */

#ifndef BC_VM_H
#define BC_VM_H

#include <assert.h>
#include <stddef.h>
#include <limits.h>

#include <signal.h>

#if BC_ENABLE_NLS

#	ifdef _WIN32
#	error NLS is not supported on Windows.
#	endif // _WIN32

#include <nl_types.h>

#endif // BC_ENABLE_NLS

#include <version.h>
#include <status.h>
#include <num.h>
#include <parse.h>
#include <program.h>
#include <history.h>

#if !BC_ENABLE_LIBRARY
#include <file.h>
#endif // !BC_ENABLE_LIBRARY

#if !BC_ENABLED && !DC_ENABLED
#error Must define BC_ENABLED, DC_ENABLED, or both
#endif

// CHAR_BIT must be at least 6.
#if CHAR_BIT < 6
#error CHAR_BIT must be at least 6.
#endif

#ifndef BC_ENABLE_NLS
#define BC_ENABLE_NLS (0)
#endif // BC_ENABLE_NLS

#ifndef MAINEXEC
#define MAINEXEC bc
#endif // MAINEXEC

#ifndef _WIN32
#ifndef EXECPREFIX
#define EXECPREFIX
#endif // EXECPREFIX
#else // _WIN32
#undef EXECPREFIX
#endif // _WIN32

#define GEN_STR(V) #V
#define GEN_STR2(V) GEN_STR(V)

#define BC_VERSION GEN_STR2(VERSION)
#define BC_MAINEXEC GEN_STR2(MAINEXEC)
#define BC_BUILD_TYPE GEN_STR2(BUILD_TYPE)

#ifndef _WIN32
#define BC_EXECPREFIX GEN_STR2(EXECPREFIX)
#else // _WIN32
#define BC_EXECPREFIX ""
#endif // _WIN32

#if !BC_ENABLE_LIBRARY

#if DC_ENABLED
#define DC_FLAG_X (UINTMAX_C(1)<<0)
#endif // DC_ENABLED

#if BC_ENABLED
#define BC_FLAG_W (UINTMAX_C(1)<<1)
#define BC_FLAG_S (UINTMAX_C(1)<<2)
#define BC_FLAG_L (UINTMAX_C(1)<<3)
#define BC_FLAG_G (UINTMAX_C(1)<<4)
#endif // BC_ENABLED

#define BC_FLAG_Q (UINTMAX_C(1)<<5)
#define BC_FLAG_I (UINTMAX_C(1)<<6)
#define BC_FLAG_P (UINTMAX_C(1)<<7)
#define BC_FLAG_R (UINTMAX_C(1)<<8)
#define BC_FLAG_TTYIN (UINTMAX_C(1)<<10)
#define BC_FLAG_TTY (UINTMAX_C(1)<<11)
#define BC_FLAG_SIGINT (UINTMAX_C(1)<<12)
#define BC_TTYIN (vm.flags & BC_FLAG_TTYIN)
#define BC_TTY (vm.flags & BC_FLAG_TTY)
#define BC_SIGINT (vm.flags & BC_FLAG_SIGINT)

#if BC_ENABLED

#define BC_S (vm.flags & BC_FLAG_S)
#define BC_W (vm.flags & BC_FLAG_W)
#define BC_L (vm.flags & BC_FLAG_L)
#define BC_G (vm.flags & BC_FLAG_G)

#endif // BC_ENABLED

#if DC_ENABLED
#define DC_X (vm.flags & DC_FLAG_X)
#endif // DC_ENABLED

#define BC_I (vm.flags & BC_FLAG_I)
#define BC_P (vm.flags & BC_FLAG_P)
#define BC_R (vm.flags & BC_FLAG_R)

#if BC_ENABLED

#define BC_IS_POSIX (BC_S || BC_W)

#if DC_ENABLED
#define BC_IS_BC (vm.name[0] != 'd')
#define BC_IS_DC (vm.name[0] == 'd')
#else // DC_ENABLED
#define BC_IS_BC (1)
#define BC_IS_DC (0)
#endif // DC_ENABLED

#else // BC_ENABLED
#define BC_IS_POSIX (0)
#define BC_IS_BC (0)
#define BC_IS_DC (1)
#endif // BC_ENABLED

#if BC_ENABLED
#define BC_PROMPT (BC_P && !BC_IS_POSIX)
#else // BC_ENABLED
#define BC_PROMPT (BC_P)
#endif // BC_ENABLED

#endif // !BC_ENABLE_LIBRARY

#define BC_MAX(a, b) ((a) > (b) ? (a) : (b))
#define BC_MIN(a, b) ((a) < (b) ? (a) : (b))

#define BC_MAX_OBASE ((BcBigDig) (BC_BASE_POW))
#define BC_MAX_DIM ((BcBigDig) (SIZE_MAX - 1))
#define BC_MAX_SCALE ((BcBigDig) (BC_NUM_BIGDIG_MAX - 1))
#define BC_MAX_STRING ((BcBigDig) (BC_NUM_BIGDIG_MAX - 1))
#define BC_MAX_NAME BC_MAX_STRING
#define BC_MAX_NUM BC_MAX_SCALE

#if BC_ENABLE_EXTRA_MATH
#define BC_MAX_RAND ((BcBigDig) (((BcRand) 0) - 1))
#endif // BC_ENABLE_EXTRA_MATH

#define BC_MAX_EXP ((ulong) (BC_NUM_BIGDIG_MAX))
#define BC_MAX_VARS ((ulong) (SIZE_MAX - 1))

#define BC_VM_BUF_SIZE (1<<12)
#define BC_VM_STDOUT_BUF_SIZE (1<<11)
#define BC_VM_STDERR_BUF_SIZE (1<<10)
#define BC_VM_STDIN_BUF_SIZE (BC_VM_STDERR_BUF_SIZE - 1)

#define BC_VM_MAX_TEMPS (1 << 9)

#define BC_VM_SAFE_RESULT(r) ((r)->t >= BC_RESULT_TEMP)

#define BC_VM_INVALID_CATALOG ((nl_catd) -1)

#define BC_VM_MUL_OVERFLOW(a, b, r) \
	((r) >= SIZE_MAX || ((a) != 0 && (r) / (a) != (b)))

typedef struct BcVm {

	volatile sig_atomic_t status;
	volatile sig_atomic_t sig_pop;

#if !BC_ENABLE_LIBRARY
	BcParse prs;
	BcProgram prog;

	BcVec line_buf;
	BcVec buffer;
#endif // !BC_ENABLE_LIBRARY

	BcVec jmp_bufs;

	size_t temps_len;

#if BC_ENABLE_LIBRARY

	BcVec ctxts;
	BcVec out;

	BcRNG rng;

	BclError err;
	bool abrt;

	unsigned int refs;

	volatile sig_atomic_t running;
#endif // BC_ENABLE_LIBRARY

#if !BC_ENABLE_LIBRARY
	const char* file;

	const char *sigmsg;
#endif // !BC_ENABLE_LIBRARY
	volatile sig_atomic_t sig_lock;
	volatile sig_atomic_t sig;
#if !BC_ENABLE_LIBRARY
	uchar siglen;

	uchar read_ret;
	uint16_t flags;

	uint16_t nchars;
	uint16_t line_len;

	bool no_exit_exprs;
	bool exit_exprs;
	bool eof;
	bool is_stdin;
#endif // !BC_ENABLE_LIBRARY

	BcBigDig maxes[BC_PROG_GLOBALS_LEN + BC_ENABLE_EXTRA_MATH];

#if !BC_ENABLE_LIBRARY
	BcVec files;
	BcVec exprs;

	const char *name;
	const char *help;

#if BC_ENABLE_HISTORY
	BcHistory history;
#endif // BC_ENABLE_HISTORY

	BcLexNext next;
	BcParseParse parse;
	BcParseExpr expr;

	const char *func_header;

	const char *err_ids[BC_ERR_IDX_NELEMS + BC_ENABLED];
	const char *err_msgs[BC_ERR_NELEMS];

	const char *locale;
#endif // !BC_ENABLE_LIBRARY

	BcBigDig last_base;
	BcBigDig last_pow;
	BcBigDig last_exp;
	BcBigDig last_rem;

#if !BC_ENABLE_LIBRARY
	char *env_args_buffer;
	BcVec env_args;
#endif // !BC_ENABLE_LIBRARY

	BcNum max;
	BcNum max2;
	BcDig max_num[BC_NUM_BIGDIG_LOG10];
	BcDig max2_num[BC_NUM_BIGDIG_LOG10];

#if !BC_ENABLE_LIBRARY
	BcFile fout;
	BcFile ferr;

#if BC_ENABLE_NLS
	nl_catd catalog;
#endif // BC_ENABLE_NLS

	char *buf;
	size_t buf_len;

	BcVec main_const_slab;
	BcVec main_slabs;
#if BC_ENABLED
	BcVec other_slabs;
#endif // BC_ENABLED
#endif // !BC_ENABLE_LIBRARY

#if BC_DEBUG_CODE
	size_t func_depth;
#endif // BC_DEBUG_CODE

} BcVm;

void bc_vm_info(const char* const help);
void bc_vm_boot(int argc, char *argv[]);
void bc_vm_init(void);
void bc_vm_shutdown(void);
void bc_vm_addTemp(BcDig *num);
BcDig* bc_vm_takeTemp(void);
void bc_vm_freeTemps(void);

#if !BC_ENABLE_HISTORY
#define bc_vm_putchar(c, t) bc_vm_putchar(c)
#endif // !BC_ENABLE_HISTORY

void bc_vm_printf(const char *fmt, ...);
void bc_vm_putchar(int c, BcFlushType type);
size_t bc_vm_arraySize(size_t n, size_t size);
size_t bc_vm_growSize(size_t a, size_t b);
void* bc_vm_malloc(size_t n);
void* bc_vm_realloc(void *ptr, size_t n);
char* bc_vm_strdup(const char *str);

bool bc_vm_readLine(bool clear);

void bc_pledge(const char *promises, const char *execpromises);

char* bc_vm_getenv(const char* var);
void bc_vm_getenvFree(char* val);

#if BC_DEBUG_CODE
void bc_vm_jmp(const char *f);
#else // BC_DEBUG_CODE
void bc_vm_jmp(void);
#endif // BC_DEBUG_CODE

#if BC_ENABLE_LIBRARY
void bc_vm_handleError(BcErr e);
void bc_vm_fatalError(BcErr e);
void bc_vm_atexit(void);
#else // BC_ENABLE_LIBRARY
void bc_vm_handleError(BcErr e, size_t line, ...);
#if !BC_ENABLE_LIBRARY && !BC_ENABLE_MEMCHECK
BC_NORETURN
#endif // !BC_ENABLE_LIBRARY && !BC_ENABLE_MEMCHECK
void bc_vm_fatalError(BcErr e);
int bc_vm_atexit(int status);
#endif // BC_ENABLE_LIBRARY

extern const char bc_copyright[];
extern const char* const bc_err_line;
extern const char* const bc_err_func_header;
extern const char *bc_errs[];
extern const uchar bc_err_ids[];
extern const char* const bc_err_msgs[];

extern const char bc_pledge_start[];
extern const char bc_pledge_end_history[];
extern const char bc_pledge_end[];

extern BcVm vm;
extern char output_bufs[BC_VM_BUF_SIZE];

#endif // BC_VM_H
