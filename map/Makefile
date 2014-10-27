bench_ob = bench.o c_orig.o neon_new.o neon_orig.o time.o
correctness_ob = correctness.o c_orig.o neon_new.o neon_orig.o correct.o
arch = $(shell uname -m)
ifeq ($(arch), aarch64)
CFLAGS+= -march=armv8-a+fp+simd+crc+crypto -ansi -std=c99 -Wall -Werror \
         -Wno-error=uninitialized -pedantic -O2 -static
else
CFLAGS+= -mfpu=neon -ansi -std=c99 -Wall -Werror -Wno-error=uninitialized \
         -pedantic -O2 -static
endif

all : bench correctness

bench : $(bench_ob)
	${CC} -o bench $(bench_ob)

correctness : $(correctness_ob)
	${CC} -o correctness $(correctness_ob)

time.o bench.o : time.h

neon_orig.o neon_new.o c_orig.o correctness.o bench.o : map.h

correctness.o correct.o : correct.h

c_orig.o : evas_blend_ops.h

.PHONY : clean check
clean :
	-rm bench correctness $(bench_ob) $(correctness_ob)

check : bench correctness
	./bench
	./correctness
