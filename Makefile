INC = -Iinclude -I/home/renlan/workspace/openssl-1.0.1c/include/openssl
CC = gcc
CFLAGS = -Wall -O2 -DLINUX
ONLYCOMPILE = $(CC) $(CFLAGS) -c -g
OBJFILES :=  $(patsubst %.c,%.o,$(wildcard *.c))
PROGNAME = client

all: $(PROGNAME)

$(PROGNAME) : $(OBJFILES)
	$(CC) -o $(PROGNAME) $(OBJFILES) -lssl -lcrypto -ldl

%.o: %.c
	${ONLYCOMPILE} -o $@ $< ${INC} 

clean:
	rm *.o