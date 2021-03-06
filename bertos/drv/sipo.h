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
 * \defgroup sipo_driver SIPO driver
 * \ingroup drivers
 * \{
 *
 * \brief Generic Serial-in, Parallel-out implementation (SIPO).
 *
 *
 *
 * \author Andrea Grandi <andrea@develer.com>
 * \author Daniele Basile <asterix@develer.com>
 *
 * $WIZ$ module_name = "sipo"
 * $WIZ$ module_depends = "kfile"
 * $WIZ$ module_hw = "bertos/hw/hw_sipo.h"
 */

#ifndef DRV_SIPO_H
#define DRV_SIPO_H

#include "hw/hw_sipo.h"
#include "cfg/cfg_sipo.h"

#include <io/kfile.h>


/*
 * The following macros are needed to maintain compatibility with older sipo API.
 * They can be safely removed once the old API is removed.
 */

 /**
  * \addtogroup sipo_api
  * \{
  */
#if COMPILER_C99
	#define sipo_init(...)           PP_CAT(sipo_init ## _, COUNT_PARMS(__VA_ARGS__)) (__VA_ARGS__)
#else
	/**
	 * Initialize SIPO module.
	 *
	 * To initialize the module you can write this code:
	 * \code
	 * Sipo ctx;
	 * sipo_init(&ctx, settings);
	 * \endcode
	 */
	#define sipo_init(args...)       PP_CAT(sipo_init ## _, COUNT_PARMS(args)) (args)

#endif
/**\}*/


#define SIPO_DATAORDER_START_LSB        1
#define SIPO_DATAORDER_START_MSB     0x80

#if !CONFIG_SIPO_DISABLE_OLD_API
/**
 * Define enum to set sipo data order.
 */
typedef enum SipoBitOrder
{
	SIPO_DATAORDER_MSB = 0,
	SIPO_DATAORDER_LSB = 1
} SipoBitOrder;

/**
 * Define enum to set the start level of clock.
 */
typedef enum SipoClockPol
{
	SIPO_START_LOW = 0,
	SIPO_START_HIGH = 1

} SipoClkPol;

/**
 * Define enum to set load signal level.
 */
typedef enum SipoLoadPol
{
	SIPO_LOW_TO_HIGH = 0,
	SIPO_HIGH_TO_LOW = 1

} SipoLoadPol;

/**
 * Sipo KFile context structure.
 */
typedef struct Sipo
{
	KFile fd;                 ///< File descriptor.
	SipoMap load_device;      ///< Descriptor of the device that we want drive.
	SipoLoadPol load_pol;     ///< Set polarity of load signal.
	SipoClkPol clock_pol;     ///< Set polarity of data clock.
	SipoBitOrder bit_order;   ///< Set the order of pushed bits in sipo.

} Sipo;
#else /* New api */

#define SIPO_DATAORDER      BV(0)
#define SIPO_DATAORDER_MSB  BV(0) ///< Set MSB sipo data order setting
#define SIPO_DATAORDER_LSB     0  ///< Set LSB sipo data order setting

#define SIPO_CLOCK_POL      BV(1)
#define SIPO_START_LOW      BV(1) ///< Set sipo clock start level high setting
#define SIPO_START_HIGH        0  ///< Set sipo clock start level low setting

#define SIPO_LOAD_LEV       BV(2)
#define SIPO_LOW_TO_HIGH    BV(2) ///< Set sipo load high signal level setting.
#define SIPO_HIGH_TO_LOW       0  ///< Set sipo load low signal level setting.

/**
 * Sipo KFile context structure.
 */
typedef struct Sipo
{
	KFile fd;                 ///< File descriptor.
	SipoMap device;           ///< Descriptor of the device that we want drive.
	uint8_t settings;		  ///< Sipo signal configuration.
} Sipo;

#endif

/**
 * ID for sipo.
 */
#define KFT_SIPO MAKE_ID('S', 'I', 'P', 'O')

/**
 * Convert + ASSERT from generic KFile to Sipo.
 */
INLINE Sipo * SIPO_CAST(KFile *fd)
{
	ASSERT(fd->_type == KFT_SIPO);
	return (Sipo *)fd;
}

void sipo_init_1(Sipo *fd);
void sipo_init_3(Sipo *fd, SipoMap dev, uint8_t settings);

/** \} */ //defgroup sipo_driver

#endif /* DRV_SIPO_H */

