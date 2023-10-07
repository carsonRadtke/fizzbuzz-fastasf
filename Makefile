CC=clang
CC_FLAGS=$(shell cat compiler_flags.txt)

.PHONY: all
all: bin/fizzbuzz

bin/fizzbuzz: fizzbuzz.c compiler_flags.txt
	$(CC) $(CC_FLAGS) -o bin/fizzbuzz fizzbuzz.c

.PHONY: clean
clean:
	rm -rf bin/*
	rm -rf perf/*

.PHONY: perf
perf: bin/fizzbuzz
	objdump --disassemble bin/fizzbuzz > perf/fizzbuzz.S
	strace -o perf/strace.out bin/fizzbuzz > /dev/null
	valgrind --tool=callgrind bin/fizzbuzz > /dev/null
	mv callgrind.out.* perf/
	callgrind_annotate perf/callgrind.out.* > perf/callgrind_annotate.out

.PHONY: eval
eval: bin/fizzbuzz
	bin/fizzbuzz | pv > /dev/null

.PHONY: docker-build
docker-build:
	docker build -t fizzbuzz-ubuntu-docker .

.PHONY: docker-run
docker-run:
	docker run -t -i 																\
		--mount type=bind,src=$(shell pwd),dst=/fizzbuzz  \
		--cap-add=SYS_PTRACE													\
		--ulimit core=-1															\
		fizzbuzz-ubuntu-docker /bin/bash