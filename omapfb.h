/*
 * Copyright (C) 2008-2010 Felipe Contreras <felipe.contreras@gmail.com>
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
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02111-1301  USA
 */

#ifndef GST_OMAPFB_H
#define GST_OMAPFB_H

#include <gst/gst.h>
#include <gst/video/gstvideosink.h>
#include <gst/video/video.h>

#include <linux/fb.h>
#include <linux/omapfb.h>

#include <stdbool.h>

G_BEGIN_DECLS

#define GST_OMAPFB_SINK_TYPE (gst_omapfbsink_get_type())
#define GST_OMAPFB_SINK(obj) (G_TYPE_CHECK_INSTANCE_CAST((obj), GST_OMAPFB_SINK_TYPE, GstOmapFbSink))

typedef struct GstOmapFbSink GstOmapFbSink;
typedef struct GstOmapFbSinkClass GstOmapFbSinkClass;

struct page {
	unsigned yoffset;
	void *buf;
};

struct GstOmapFbSink {
	GstVideoSink videosink;

	struct fb_var_screeninfo varinfo;
	struct fb_var_screeninfo overlay_info;
	struct omapfb_mem_info mem_info;
	struct omapfb_plane_info plane_info;

	int overlay_fd;
	unsigned char *framebuffer;
	bool enabled;
	bool manual_update;

	struct page *pages;
	int nr_pages;
	struct page *cur_page;
};

struct GstOmapFbSinkClass {
	GstBaseSinkClass parent_class;
};

GType gst_omapfbsink_get_type(void);

G_END_DECLS

#endif /* GST_OMAPFB_H */
