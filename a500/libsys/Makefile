TOPDIR = $(realpath $(CURDIR)/..)
CPPFLAGS = -I$(TOPDIR)/include

OBJS = 8svx.o blitter.o common.o circle.o console.o coplist.o ffp.o gfx.o \
       hardware.o iff.o ilbm.o inflate.o io-dos.o io-extra.o keyboard.o \
       line.o memory.o mouse.o pixmap.o qsort.o random.o reader.o sound.o \
       sprite.o fx.o sintab.o color.o newstackswap.o hrtmon.o \
       sort.o amigahunk.o png.o c2p_1x1_4.o interrupts.o \
       blt-add-sat.o blt-dec-sat.o blt-inc-sat.o blt-copy.o blt-copy-area.o \
       blt-copy-fast.o blt-copy-mask.o blt-make-mask.o blt-fill-area.o \
       blt-line.o blt-set-area.o blt-set-mask-area.o \
       serial.o rawio-ser.o rawio-par.o io-floppy.o \
       __mulsi3.o __divsi3.o __udivsi3.o __modsi3.o __umodsi3.o floppy.o \
       event.o tasks.o gui.o font.o font-load.o

all:	libsys.a

libsys.a: $(OBJS)

sintab.s: sintab.py
	python sintab.py

include $(TOPDIR)/Makefile.common
