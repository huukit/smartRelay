/*
 * <copyright>
 * Copyright (c) 2016: Tuomas Huuki / Miikka Tammi tut.fi
 *
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 * or the GNU Lesser General Public License version 2.1, both as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * Lesser GNU General Public License for more details.
 *
 * You should have received a copy of the (Lesser) GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 * </copyright>
 */

/* $Id$ */

/*! \file
 * Proximia debug header. (license: GPLv2 or LGPLv2.1)
 * \author Tuomas Huuki tuomas.huuki@proximia.fi
 * \copyright 2017 Tuomas Huuki / proximia.fi
 */
#ifndef DEBUG_H_
#define DEBUG_H_

#include "softuart.h"

#define __DEBUG_STR_TMPSIZE__ 128
extern char __debugstrtmp__[__DEBUG_STR_TMPSIZE__];

void assertblinker(void);

#include <stdio.h>
#define OUTPUT(...) {\
	snprintf(__debugstrtmp__, __DEBUG_STR_TMPSIZE__, __VA_ARGS__);\
	__debugstrtmp__[__DEBUG_STR_TMPSIZE__ - 1] = 0;\
	softuart_puts(__debugstrtmp__);\
}

#define ASSERT(x)\
{\
	if (!(x))\
	{\
		OUTPUT("\r\nAssert \"%s\" failed! File %s line %i.\n", #x, __FILE__, __LINE__);\
		assertblinker();\
	}\
}

#endif /* DEBUG_H_ */