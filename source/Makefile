SEED ?= 0
BYTE ?= 0
LOGN ?= 30
ELEMENTS ?= 1000000
DEBUG ?= 0

CFLAGS := -g -gdwarf-4 -Wall -Wextra  -std=c11 -DSEED=$(SEED)

ifeq ($(DEBUG),0)
CFLAGS += -DNDEBUG
endif


all: runall

count_ints_basic: count_ints.c helpers.h
	$(CC) $(CFLAGS) -O0 -o $@ count_ints.c
	gdb -batch -ex "disassemble/rs count_ints" $@ > $@.dump
count_ints_opt_simple: count_ints.c helpers.h
	$(CC) $(CFLAGS) -O3 -mno-sse -fno-unroll-loops -o $@ count_ints.c
	gdb -batch -ex "disassemble/rs count_ints" $@ > $@.dump
count_ints_opt: count_ints.c helpers.h
	$(CC) $(CFLAGS) -O3 -mno-sse -o $@ count_ints.c
	gdb -batch -ex "disassemble/rs count_ints" $@ > $@.dump
count_ints_opt_vector: count_ints.c helpers.h
	$(CC) $(CFLAGS) -O3 -march=native -o $@ count_ints.c
	gdb -batch -ex "disassemble/rs count_ints" $@ > $@.dump
count_ints_opt_vector_with_long: count_ints.c helpers.h
	$(CC) $(CFLAGS) -O3 -march=native -DLONG -o $@ count_ints.c
	gdb -batch -ex "disassemble/rs count_ints" $@ > $@.dump

count_ints: count_ints_basic count_ints_opt_simple count_ints_opt count_ints_opt_vector count_ints_opt_vector_with_long
	@echo "### counting ints";
	./count_ints_basic $(BYTE) $(LOGN)
	@echo "";
	./count_ints_opt_simple $(BYTE) $(LOGN)
	@echo "";
	./count_ints_opt $(BYTE) $(LOGN)
	@echo "";
	./count_ints_opt_vector $(BYTE) $(LOGN)
	@echo "";
	./count_ints_opt_vector_with_long $(BYTE) $(LOGN)
	@echo "";




count_pairs_basic: count_pairs-a.c helpers.h
	$(CC) $(CFLAGS) -O0 -o $@ count_pairs-a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

count_pairs_O3: count_pairs-a.c helpers.h
	$(CC) $(CFLAGS) -O3  -mno-sse -o $@ count_pairs-a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

count_pairs_O3_unroll: count_pairs-a.c helpers.h
	$(CC) $(CFLAGS) -O3  -mno-sse -funroll-loops -o $@ count_pairs-a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

count_pairs_march_native: count_pairs-a.c helpers.h
	$(CC) $(CFLAGS) -O3 -funroll-loops -march=native -o $@ count_pairs-a.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

count_pairs_split_loops: count_pairs-b.c helpers.h
	$(CC) $(CFLAGS) -O3 -funroll-loops -march=native -o $@ count_pairs-b.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump

count_pairs_manual: count_pairs-c.c helpers.h
	$(CC) $(CFLAGS) -O3 -funroll-loops -march=native -o $@ count_pairs-c.c
	gdb -batch -ex "disassemble/rs count_pairs" $@ > $@.dump


count_pairs: count_pairs_basic count_pairs_O3 count_pairs_O3_unroll count_pairs_march_native count_pairs_split_loops count_pairs_manual
	@echo "### Solving with Unaligned Pairs";
	./count_pairs_basic $(BYTE) $(LOGN)
	@echo "";
	./count_pairs_O3 $(BYTE) $(LOGN)
	@echo "";
	./count_pairs_O3_unroll $(BYTE) $(LOGN)
	@echo "";
	./count_pairs_march_native $(BYTE) $(LOGN)
	@echo "";
	./count_pairs_split_loops $(BYTE) $(LOGN)
	@echo "";
	./count_pairs_manual $(BYTE) $(LOGN)
	@echo "";



clean:
	rm -f count_ints_basic count_ints_opt_simple count_ints_opt count_ints_opt_vector count_ints_opt_vector_with_long count_pairs_basic count_pairs_O3 count_pairs_O3_unroll count_pairs_march_native count_pairs_manual perf.data perf.data.old



runall: count_ints count_pairs

