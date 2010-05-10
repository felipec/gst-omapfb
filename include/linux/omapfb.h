/*
 * File: include/linux/omapfb.h
 *
 * Framebuffer driver for TI OMAP boards
 *
 * Copyright (C) 2004 Nokia Corporation
 * Author: Imre Deak <imre.deak@nokia.com>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */

#ifndef __LINUX_OMAPFB_H__
#define __LINUX_OMAPFB_H__

#include <linux/fb.h>
#include <linux/ioctl.h>
#include <linux/types.h>

#define OMAP_IOW(num, dtype)	_IOW('O', num, dtype)
#define OMAP_IO(num)		_IO('O', num)

#define OMAPFB_SETUP_PLANE	OMAP_IOW(52, struct omapfb_plane_info)
#define OMAPFB_QUERY_PLANE	OMAP_IOW(53, struct omapfb_plane_info)
#define OMAPFB_SETUP_MEM	OMAP_IOW(55, struct omapfb_mem_info)
#define OMAPFB_WAITFORGO	OMAP_IO(60)

#define OMAPFB_MEMTYPE_SDRAM		0
#define OMAPFB_MEMTYPE_SRAM		1
#define OMAPFB_MEMTYPE_MAX		1

enum omapfb_color_format {
	OMAPFB_COLOR_RGB565 = 0,
	OMAPFB_COLOR_YUV422,
	OMAPFB_COLOR_YUV420,
	OMAPFB_COLOR_CLUT_8BPP,
	OMAPFB_COLOR_CLUT_4BPP,
	OMAPFB_COLOR_CLUT_2BPP,
	OMAPFB_COLOR_CLUT_1BPP,
	OMAPFB_COLOR_RGB444,
	OMAPFB_COLOR_YUY422,

	OMAPFB_COLOR_ARGB16,
	OMAPFB_COLOR_RGB24U,	/* RGB24, 32-bit container */
	OMAPFB_COLOR_RGB24P,	/* RGB24, 24-bit container */
	OMAPFB_COLOR_ARGB32,
	OMAPFB_COLOR_RGBA32,
	OMAPFB_COLOR_RGBX32,
};

struct omapfb_plane_info {
	__u32 pos_x;
	__u32 pos_y;
	__u8  enabled;
	__u8  channel_out;
	__u8  mirror;
	__u8  reserved1;
	__u32 out_width;
	__u32 out_height;
	__u32 reserved2[12];
};

struct omapfb_mem_info {
	__u32 size;
	__u8  type;
	__u8  reserved[3];
};

#endif /* __LINUX_OMAPFB_H__ */
