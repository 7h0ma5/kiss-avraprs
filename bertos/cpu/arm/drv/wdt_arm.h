/**
 * \file
 * <!--
 * This file is part of BeRTOS.
 *
 * Bertos is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 * As a special exception, you may use this file as part of a free software
 * library without restriction.  Specifically, if other files instantiate
 * templates or use macros or inline functions from this file, or you compile
 * this file and link it with other files to produce an executable, this
 * file does not by itself cause the resulting executable to be covered by
 * the GNU General Public License.  This exception does not however
 * invalidate any other reasons why the executable file might be covered by
 * the GNU General Public License.
 *
 * Copyright 2009 Develer S.r.l. (http://www.develer.com/)
 *
 * -->
 *
 * \brief Watchdog interface for ARM architecture.
 *
 *
 * \author Luca Ottaviano <lottaviano@develer.com>
 *
 */
#ifndef DRV_WDT_ARM_H
#define DRV_WDT_ARM_H

#include <cfg/compiler.h> // INLINE
#include <cfg/macros.h> // BV

#if CPU_ARM_AT91
	#include <io/arm.h>

	INLINE void wdt_start(uint32_t _timeout) { (void) _timeout; /* implement me */ }
	INLINE void wdt_stop(void) { WDT_MR = BV(WDT_WDDIS); }
	INLINE void wdt_reset(void)
	{
		WDT_CR = WDT_KEY | BV(WDT_WDRSTT);
	}
#else
	#error "Missing watchdog support for yout CPU"
#endif

#endif /* DRV_WDT_ARM_H */
