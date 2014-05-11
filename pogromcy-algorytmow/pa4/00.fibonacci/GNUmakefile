all: cpp

run: all
	$(PROG)

PROG=./program

c:
	gcc -O2 -static -lm program.c -o program

cpp:
	g++ -O2 -static -lm program.cpp -o program

test: all
	for i in 1 2 3 4 5 6 7 8 9 10; do $(PROG) < test/fib$$i.in > /tmp/test.out; diff -w /tmp/test.out test/fib$$i.out; done
