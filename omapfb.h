/*
 * Copyright (C) 2008-2010 Felipe Contreras
 *
 * Author: Felipe Contreras <felipe.contreras@gmail.com>
 *
 * This file may be used under the terms of the GNU Lesser General Public
 * License version 2.1, a copy of which is found in LICENSE included in the
 * packaging of this file.
 */

#ifndef GST_OMAPFB_H
#define GST_OMAPFB_H

#include <gst/gst.h>
#include <gst/video/gstvideosink.h>
#include <gst/video/video.h>

#include <linux/fb.h>
#include <linux/omapfb.h>

#include <stdbool.h>

#define GST_OMAPFB_SINK_TYPE (gst_omapfb_sink_get_type())

struct page {
	unsigned yoffset;
	void *buf;
};

struct gst_omapfb_sink {
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

struct gst_omapfb_sink_class {
	GstBaseSinkClass parent_class;
};

GType gst_omapfb_sink_get_type(void);

#endif /* GST_OMAPFB_H */
