CC := arm-linux-gcc
CFLAGS := -O2 -Wall -Werror -ansi -std=c99

GST_LIBS := $(shell pkg-config --libs gstreamer-0.10 gstreamer-base-0.10)
GST_CFLAGS := $(shell pkg-config --cflags gstreamer-0.10 gstreamer-base-0.10)
KERNEL := /data/public/dev/omap/linux-omap

plugin_dir := $(DESTDIR)/usr/lib/gstreamer-0.10

all: libgstomapfb.so

libgstomapfb.so: omapfb.o
libgstomapfb.so: CFLAGS := $(CFLAGS) $(GST_CFLAGS) -I$(KERNEL)/arch/arm/plat-omap/include
libgstomapfb.so: LIBS := $(GST_LIBS)

# pretty print
V = @
Q = $(V:y=)
QUIET_CC      = $(Q:@=@echo ' CC         '$@;)
QUIET_LINK    = $(Q:@=@echo ' LINK       '$@;)
QUIET_CLEAN   = $(Q:@=@echo ' CLEAN      '$@;)
QUIET_INSTALL = $(Q:@=@echo ' INSTALL    '$@;)

%.o:: %.c
	$(QUIET_CC)$(CC) $(CFLAGS) -MMD -o $@ -c $<

%.so::
	$(QUIET_CC)$(CC) $(LDFLAGS) -shared -o $@ $^ $(LIBS)

install: libgstomapfb.so
	$(QUIET_INSTALL)install libgstomapfb.so $(plugin_dir)

clean:
	$(QUIET_CLEAN)$(RM) libgstomapfb.so *.o *.d

-include *.d
