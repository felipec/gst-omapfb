/*
 * Copyright (C) 2009-2010 Felipe Contreras
 *
 * Author: Felipe Contreras <felipe.contreras@gmail.com>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation
 * version 2.1 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include "log.h"

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <gst/gst.h>

#ifndef GST_DISABLE_GST_DEBUG
extern GstDebugCategory *omapfb_debug;
#endif

#ifndef GST_DISABLE_GST_DEBUG
static inline GstDebugLevel
log_level_to_gst(unsigned int level)
{
	switch (level) {
	case 0: return GST_LEVEL_ERROR;
	case 1: return GST_LEVEL_WARNING;
	case 2:
	case 3: return GST_LEVEL_INFO;
	default: return GST_LEVEL_DEBUG;
	}
}
#endif

void pr_helper(unsigned int level,
		void *object,
		const char *file,
		const char *function,
		unsigned int line,
		const char *fmt,
		...)
{
	char *tmp;
	va_list args;

	va_start(args, fmt);

	vasprintf(&tmp, fmt, args);

	if (level <= 1)
		g_printerr("%s: %s\n", function, tmp);
	else if (level == 2)
		g_print("%s:%s(%u): %s\n", file, function, line, tmp);
#if defined(DEVEL) || defined(DEBUG)
	else if (level == 3)
		g_print("%s: %s\n", function, tmp);
#endif
#ifdef DEBUG
	else if (level == 4)
		g_print("%s:%s(%u): %s\n", file, function, line, tmp);
#endif

#ifndef GST_DISABLE_GST_DEBUG
	gst_debug_log_valist(omapfb_debug, log_level_to_gst(level), file, function, line, object, fmt, args);
#endif

	free(tmp);

	va_end(args);
}
