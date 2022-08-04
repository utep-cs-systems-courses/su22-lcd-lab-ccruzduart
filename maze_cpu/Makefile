
CPU	       = msp430g2553
CFLAGS	       = -mmcu=${CPU} -Os -I../h
LDFLAGS        = -L../lib -L/opt/ti/msp430_gcc/include/

CC	       = msp430-elf-gcc
AS             = msp430-elf-gcc -mmcu=${CPU} -c

all: project3-c.elf

project3-c.elf: ${COMMON_OBJECTS} main.o buzzer.o wdt_handler.o

	${CC} ${CFLAGS} ${LDFLAGS} -o $@ $^ -lTimer -lLcd


buzzer.o: buzzer.h

load: project3-c.elf
	msp430loader.sh $^

clean:
	rm -f libLcd.a *.o *.elf
