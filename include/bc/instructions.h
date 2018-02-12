﻿/*
 * Copyright 2018 Contributors
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.

 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.

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
 *******************************************************************************
 *
 * A special license exemption is granted to the Toybox project and to the
 * Android Open Source Project to use this source under the following BSD
 * 0-Clause License:
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 * OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 *******************************************************************************
 *
 * Definitions of bc instructions.
 *
 */

#ifndef BC_INSTRUCTIONS_H
#define BC_INSTRUCTIONS_H

#include <stdint.h>

#define BC_INST_CALL ((uint8_t) 'C')
#define BC_INST_RETURN ((uint8_t) 'R')
#define BC_INST_RETURN_ZERO ((uint8_t) '$')

#define BC_INST_READ ((uint8_t) 'r')

#define BC_INST_JUMP ((uint8_t) 'J')
#define BC_INST_JUMP_NOT_ZERO ((uint8_t) 'n')
#define BC_INST_JUMP_ZERO ((uint8_t) 'z')

#define BC_INST_PUSH_VAR ((uint8_t) 'V')
#define BC_INST_PUSH_ARRAY ((uint8_t) 'A')

#define BC_INST_PUSH_LAST ((uint8_t) 'L')
#define BC_INST_PUSH_SCALE ((uint8_t) '.')
#define BC_INST_PUSH_IBASE ((uint8_t) 'I')
#define BC_INST_PUSH_OBASE ((uint8_t) 'O')

#define BC_INST_SCALE_FUNC ((uint8_t) 'a')
#define BC_INST_LENGTH ((uint8_t) 'l')
#define BC_INST_SQRT ((uint8_t) 'q')

#define BC_INST_PUSH_NUM ((uint8_t) 'N')
#define BC_INST_PUSH_ZERO ((uint8_t) '0')
#define BC_INST_POP ((uint8_t) 'P')
#define BC_INST_DUP_NUM ((uint8_t) 'D')

#define BC_INST_INC ((uint8_t) 'i')
#define BC_INST_DEC ((uint8_t) 'd')

#define BC_INST_HALT ((uint8_t) 'H')

#define BC_INST_PRINT ((uint8_t) 'p')
#define BC_INST_STR ((uint8_t) 'S')
#define BC_INST_PRINT_STR ((uint8_t) 's')

#define BC_INST_OP_POWER ((uint8_t) '^')
#define BC_INST_OP_MULTIPLY ((uint8_t) '*')
#define BC_INST_OP_DIVIDE ((uint8_t) '/')
#define BC_INST_OP_MODULUS ((uint8_t) '%')
#define BC_INST_OP_PLUS ((uint8_t) '+')
#define BC_INST_OP_MINUS ((uint8_t) '-')

#define BC_INST_OP_REL_EQUAL ((uint8_t) '=')
#define BC_INST_OP_REL_LESS_EQ ((uint8_t) ';')
#define BC_INST_OP_REL_GREATER_EQ ((uint8_t) '?')
#define BC_INST_OP_REL_LESS ((uint8_t) '<')
#define BC_INST_OP_REL_GREATER ((uint8_t) '>')

#define BC_INST_OP_BOOL_NOT ((uint8_t) '!')

#define BC_INST_OP_BOOL_OR ((uint8_t) '|')
#define BC_INST_OP_BOOL_AND ((uint8_t) '&')

#define BC_INST_OP_NEGATE ((uint8_t) '_')

#define BC_INST_OP_ASSIGN_POWER ((uint8_t) '`')
#define BC_INST_OP_ASSIGN_MULTIPLY ((uint8_t) '{')
#define BC_INST_OP_ASSIGN_DIVIDE ((uint8_t) '}')
#define BC_INST_OP_ASSIGN_MODULUS ((uint8_t) '~')
#define BC_INST_OP_ASSIGN_PLUS ((uint8_t) '[')
#define BC_INST_OP_ASSIGN_MINUS ((uint8_t) ']')
#define BC_INST_OP_ASSIGN ((uint8_t) ',')

#endif // BC_INSTRUCTIONS_H
