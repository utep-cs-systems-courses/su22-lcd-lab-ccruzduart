
CPU	       = msp430g2553
CFLAGS	       = -mmcu=${CPU} -Os -I../h
LDFLAGS        = -L../lib -L/opt/ti/msp430_gcc/include/

CC	       = msp430-elf-gcc
AS             = msp430-elf-as

all: project3-c.elf

project3-c.elf: ${COMMON_OBJECTS} main.o buzzer.o

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd


project3-s.elf: ${COMMON_OBJECTS}../lib/libTimer.a

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^

buzzer.o: buzzer.h

load-c: project3-c.elf
	msp430loader.sh $^



load-s: project3-s.elf
	msp430loader.sh project3-s.elf

clean:
	rm -f libLcd.a *.o *.elf
