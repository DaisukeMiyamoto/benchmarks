# Makefile

CC	 = icc
CFLAGS   = -Wall -O3 -mkl
LDFLAGS  = $(CFLAGS)
LDLIBS   =
INCLUDES = 
SRC      = simple_bench.c
OBJS     = simple_bench.o
PROG     = simple_bench_icc.out


all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDLIBS) $(LDFLAGS)

asm: $(INCLUDES) $(SRC)
	$(CC) -S $(CFLAGS) $(SRC)


*.o : $(INCLUDES) $(SRC)

.c.o:

clean:
	rm -fv $(OBJ) $(PROG) *~ *.o *.s

