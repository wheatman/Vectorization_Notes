SEED ?= 0
BYTE ?= 0
LOGN ?= 29
ELEMENTS ?= 1000000
DEBUG ?= 0

CFLAGS := -g -gdwarf-4 -Wall -Wextra  -std=c11 -DSEED=$(SEED)

ifeq ($(DEBUG),0)
CFLAGS += -DNDEBUG
endif


all: runall

ex1_basic: ex1a.c helpers.h
	$(CC) $(CFLAGS) -O0 -o $@ ex1a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

ex1_O3: ex1a.c helpers.h
	$(CC) $(CFLAGS) -O3 -mno-sse -o $@ ex1a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

ex1_O3_unroll: ex1a.c helpers.h
	$(CC) $(CFLAGS) -O3 -mno-sse -funroll-loops -o $@ ex1a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

ex1_march_native: ex1a.c helpers.h
	$(CC) $(CFLAGS) -O3 -march=native -funroll-loops -o $@ ex1a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

ex1_specify_alignment: ex1b.c helpers.h
	$(CC) $(CFLAGS) -O3 -march=native -funroll-loops -o $@ ex1b.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

ex1_manual: ex1c.c helpers.h
	$(CC) $(CFLAGS) -O3 -march=native -o $@ ex1c.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump



ex2_basic: ex2a.c helpers.h
	$(CC) $(CFLAGS) -O0 -o $@ ex2a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

ex2_O3: ex2a.c helpers.h
	$(CC) $(CFLAGS) -O3  -mno-sse -o $@ ex2a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

ex2_O3_unroll: ex2a.c helpers.h
	$(CC) $(CFLAGS) -O3  -mno-sse -funroll-loops -o $@ ex2a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

ex2_march_native: ex2a.c helpers.h
	$(CC) $(CFLAGS) -O3 -funroll-loops -march=native -o $@ ex2a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

ex2_manual: ex2b.c helpers.h
	$(CC) $(CFLAGS) -O3 -funroll-loops -march=native -o $@ ex2b.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump


ex3_basic: ex3a.c helpers.h
	$(CC) $(CFLAGS) -O0 -o $@ ex3a.c
	gdb -batch -ex "disassemble/rs Decode" $@ > $@.dump

ex3_O3: ex3a.c helpers.h
	$(CC) $(CFLAGS) -O3 -o $@ ex3a.c
	gdb -batch -ex "disassemble/rs Decode" $@ > $@.dump

ex3_march_native: ex3a.c helpers.h
	$(CC) $(CFLAGS) -O3 -march=native -o $@ ex3a.c
	gdb -batch -ex "disassemble/rs Decode" $@ > $@.dump

ex3_manual1: ex3b.c helpers.h
	$(CC) $(CFLAGS) -O3 -march=native -o $@ ex3b.c
	gdb -batch -ex "disassemble/rs Decode" $@ > $@.dump

ex3_manual2: ex3c.c helpers.h
	$(CC) $(CFLAGS) -O3 -march=native -o $@ ex3c.c
	gdb -batch -ex "disassemble/rs Decode" $@ > $@.dump



clean:
	rm -f ex1_basic ex1_O3 ex1_O3_unroll ex1_march_native ex1_specify_alignment ex1_manual ex2_basic ex2_O3 ex2_O3_unroll ex2_march_native ex2_manual perf.data perf.data.old ex3_basic ex3_O3 ex3_march_native ex3_manual1 ex3_manual2

ex1: ex1_basic ex1_O3 ex1_O3_unroll ex1_march_native ex1_specify_alignment ex1_manual
	@echo "### Solving with Aligned Pairs";
	./ex1_basic $(BYTE) $(LOGN)
	@echo "";
	./ex1_O3 $(BYTE) $(LOGN)
	@echo "";
	./ex1_O3_unroll $(BYTE) $(LOGN)
	@echo "";
	./ex1_march_native $(BYTE) $(LOGN)
	@echo "";
	./ex1_specify_alignment $(BYTE) $(LOGN)
	@echo "";
	./ex1_manual $(BYTE) $(LOGN)
	@echo "";

ex2: ex2_basic ex2_O3 ex2_O3_unroll ex2_march_native ex2_manual
	@echo "### Solving with Unaligned Pairs";
	./ex2_basic $(BYTE) $(LOGN)
	@echo "";
	./ex2_O3 $(BYTE) $(LOGN)
	@echo "";
	./ex2_O3_unroll $(BYTE) $(LOGN)
	@echo "";
	./ex2_march_native $(BYTE) $(LOGN)
	@echo "";
	./ex2_manual $(BYTE) $(LOGN)
	@echo "";

ex3: ex3_basic ex3_O3 ex3_march_native ex3_manual1 ex3_manual2
	./ex3_basic $(ELEMENTS)
	@echo "";
	./ex3_O3 $(ELEMENTS)
	@echo "";
	./ex3_march_native $(ELEMENTS)
	@echo "";
	./ex3_manual1 $(ELEMENTS)
	@echo "";
	./ex3_manual2 $(ELEMENTS)
	@echo "";

runall: ex1 ex2 ex3

