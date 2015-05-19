func_ob = op_copy_color_.o neon_intrinsics.o neon_inline.o
bench_ob = bench.o $(func_ob) time.o
correctness_ob = correctness.o $(func_ob) correct.o
arch = $(shell uname -m)
ifeq ($(arch), aarch64)
   CFLAGS+= -march=armv8-a+fp+simd+crc+crypto -ansi -std=c99 -Wall -Werror -pedantic -O2 -Wno-error=variadic-macros -static -Wno-variadic-macros
else
   CFLAGS+= -mfpu=neon -ansi -std=c99 -Wall -Werror -pedantic -O2 -Wno-error=variadic-macros -static -Wno-variadic-macros
endif

all : bench correctness

bench : $(bench_ob)
	cc -static -o bench $(bench_ob)

correctness : $(correctness_ob)
	cc -static -o correctness $(correctness_ob)

time.o bench.o : time.h

$(func_ob): copy.h op_copy_color_neon.c

correctness.o bench.o : copy.h

correctness.o correct.o : correct.h

c_orig.o : evas_blend_ops.h

.PHONY : clean check
clean :
	-rm bench correctness $(bench_ob) $(correctness_ob)

check : check-bench check-correctness

check-bench : bench
	./bench

check-correctness : correctness
	./correctness
