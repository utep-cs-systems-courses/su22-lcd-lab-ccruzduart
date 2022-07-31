
CPU	       = msp430g2553
CFLAGS	       = -mmcu=${CPU} -Os -I../h
LDFLAGS        = -L/opt/ti/msp430_gcc/include -L../lib

CC	       = msp430-elf-gcc
AS             = msp430-elf-as

all: libLcd.a project3-c.elf

libLcd.a:lcdutils.o lcddraw.o
	$(AR) crs $@ $^
lcddraw.o: lcddraw.c lcddraw.h lcdutils.h
lcdutils.o: lcdutils.c lcdutils.h

install: libLcd.a
	mkdir -p ../h ./lib
	mv $^ ../lib
	cp *.h ../h

project3-c.elf: ${COMMON_OBJECTS} main.o libLcd.a

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer


project3-s.elf: ${COMMON_OBJECTS}../lib/libTimer.a

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^



load-c: project3-c.elf
	msp430loader.sh $^



load-s: project3-s.elf
	msp430loader.sh project3-s.elf

clean:
	rm -f libLcd.a *.o *.elf
