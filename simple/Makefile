# Makefile

CC	 = fccpx
CFLAGS   = -Kfast,optmsg=2 -DKCOMPUTER -Nrt_tune,src,sta
LDFLAGS  = $(CFLAGS)
LDLIBS   =
INCLUDES = 
SRC      = simple_bench.c
OBJS     = simple_bench.o
PROG     = simple_bench_fcc.out


all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

asm: $(INCLUDES) $(SRC)
	$(CC) -S $(CFLAGS) $(SRC)


*.o : $(INCLUDES) $(SRC)

.c.o:

clean:
	rm -fv $(OBJ) $(PROG) *~ *.o *.s

