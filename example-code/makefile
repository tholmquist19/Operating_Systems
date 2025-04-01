all: counter counter-mutex perf-example counter-approx list-mutex list-improved list-hand-over

counter: counter.c
	gcc -pthread counter.c -o $@

counter-mutex: counter-mutex.c
	gcc -pthread counter-mutex.c -o $@

perf-example: perf-example.c
	gcc -pthread perf-example.c -o $@

counter-approx: counter-approx.c
	gcc -g -pthread counter-approx.c -o $@

list-mutex: list-mutex.c
	gcc -g -pthread list-mutex.c -o $@

list-improved: list-improved.c
	gcc -g -pthread list-improved.c -o $@

list-hand-over: list-hand-over.c
	gcc -g -pthread list-hand-over.c -o $@
