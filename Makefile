GST_LIBS=`pkg-config --libs gstreamer-0.10 gstreamer-base-0.10`
GST_CFLAGS=`pkg-config --cflags gstreamer-0.10 gstreamer-base-0.10`
KERNEL=/data/public/dev/omap/linux-omap

CC=arm-linux-gcc
CFLAGS=-Wall -ggdb -ansi -std=c99

plugin=libgstomapfb.so

all: $(plugin)

$(plugin): omapfb.o
$(plugin): CFLAGS := $(CFLAGS) $(GST_CFLAGS) -I$(KERNEL)/arch/arm/plat-omap/include
$(plugin): LIBS := $(GST_LIBS)

# from Lauri Leukkunen's build system
ifdef V
Q = 
P = @printf "" # <- space before hash is important!!!
else
P = @printf "[%s] $@\n" # <- space before hash is important!!!
Q = @
endif

%.o:: %.c
	$(P)CC
	$(Q)$(CC) $(CFLAGS) -Wp,-MMD,$(dir $@).$(notdir $@).d -o $@ -c $<

%.so::
	$(P)SHLIB
	$(Q)$(CC) $(LDFLAGS) -shared -o $@ $^ $(LIBS)

clean:
	find -name '*.o' -delete
	rm -f $(plugin)
