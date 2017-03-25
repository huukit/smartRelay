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

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

void adc_init(void);

int32_t adc_getCurrentmA(void);
uint16_t adc_getVoltagemV(void);
int8_t adc_getChipTemp(void);


#endif /* ADC_H_ */