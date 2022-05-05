# indicate how the object files are to be created

#BLIS_PREFIX = ../blis
#BLIS_INC = $(BLIS_PREFIX)/include/skx
#BLIS_LIB = $(BLIS_PREFIX)/lib/skx/libblis.a

#OTHER_LIBS = -L/usr/lib -lm -lpthread
CC         := gcc -O3
#CFLAGS     := -g -O3   -qopenmp
#CFLAGS     := -g -O0 -I$(BLIS_INC)
#CFLAGS     := -g -O3 -axCORE-AVX2  -qopenmp
#CFLAGS     := -g -O3 -axCORE-AVX2

OBJECT_FILES := saxpy.o driver.o helper.o sscal.o sdot.o sgemv.o sgemm.o
saxpy: $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) $(BLIS_LIB) $(OTHER_LIBS) -o saxpy

saxpy.o : saxpy.c
	$(CC) $(CFLAGS) -c saxpy.c
sdot.o : sdot.c
	$(CC) $(CFLAGS) -c sdot.c
sgemv.o : sgemv.c
	$(CC) $(CFLAGS) -c sgemv.c
sgemm.o : sgemm.c
	$(CC) $(CFLAGS) -c sgemm.c
driver.o : driver.c
	$(CC) $(CFLAGS) -c driver.c
sscal.o : sscal.c
	$(CC) $(CFLAGS) -c sscal.c

helper.o : helper.c
	$(CC) $(CFLAGS) -c helper.c

clean:
	rm *.o 
