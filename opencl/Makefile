# Makefile

CC	 	= nvcc
CFLAGS	 	= 
LDFLAGS		= 
INCLUDES 	= opencl_utils.h calc_utils.h
LIBS 		= -lm -lOpenCL
OBJS    	= calc_host.o opencl_utils.o calc_utils.o
PROG		= calc.out

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

*.o : $(INCLUDES) $(SRC)

.c.o:

clean:
	rm -f $(OBJS) $(PROG) *~ \#*

