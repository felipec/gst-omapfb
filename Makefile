CROSS_COMPILE ?= arm-linux-
CC := $(CROSS_COMPILE)gcc

CFLAGS := -O2 -ggdb -Wall -Wextra -Wno-unused-parameter -ansi -std=c99
LDFLAGS := -Wl,--no-undefined

override CFLAGS += -D_GNU_SOURCE

GST_CFLAGS := $(shell pkg-config --cflags gstreamer-0.10 gstreamer-base-0.10)
GST_LIBS := $(shell pkg-config --libs gstreamer-0.10 gstreamer-base-0.10)

KERNEL := /data/public/dev/omap/linux-omap

prefix := /usr

all:

version := $(shell ./get-version)

libgstomapfb.so: omapfb.o log.o
libgstomapfb.so: override CFLAGS += $(GST_CFLAGS) -fPIC \
	-D VERSION='"$(version)"' \
	-I$(KERNEL)/include -I$(KERNEL)/arch/arm/include
libgstomapfb.so: override LIBS += $(GST_LIBS)

targets += libgstomapfb.so

all: $(targets)

# pretty print
ifndef V
QUIET_CC    = @echo '   CC         '$@;
QUIET_LINK  = @echo '   LINK       '$@;
QUIET_CLEAN = @echo '   CLEAN      '$@;
endif

D = $(DESTDIR)

%.o:: %.c
	$(QUIET_CC)$(CC) $(CFLAGS) -MMD -o $@ -c $<

%.so::
	$(QUIET_CC)$(CC) $(LDFLAGS) -shared -o $@ $^ $(LIBS)

install: $(targets)
	install -D libgstomapfb.so $(D)/$(prefix)/lib/gstreamer-0.10/libgstomapfb.so

clean:
	$(QUIET_CLEAN)$(RM) $(targets) *.o *.d

-include *.d
