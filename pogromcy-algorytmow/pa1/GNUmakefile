PROG	= program

all: $(PROG)

clean:
	rm -f $(PROG)

run: all
	./$(PROG)

ifeq ($(PA_LANG),c)
$(PROG): program.c
	gcc -O2 -static -lm program.c -o program
endif

ifeq ($(PA_LANG),cpp)
$(PROG): program.cpp
	g++ -O2 -static -lm program.cpp -o program
endif

test: all
	@for i in 0 1 2 3 4 5 6 7 8 9 10; do \
		testIn=test/$(PA_TEST_PREFIX)$$i.in; \
		testOut=/tmp/$(PA_TEST_PREFIX).out; \
		testRef=test/$(PA_TEST_PREFIX)$$i.out; \
		if [ -f $$testIn ]; then \
			./$(PROG) < $$testIn > $$testOut; \
			diff -w $$testOut $$testRef; \
			if [ $$? -ne 0 ]; then \
				echo test $$i: FAILURE; \
			else \
				echo test $$i: OK; \
			fi \
		fi; \
		if [ -f $${testIn}.bz2 ]; then \
			bzip2 -dc $${testIn}.bz2 | ./$(PROG) > $$testOut; \
			diff -w $$testOut $$testRef; \
			if [ $$? -ne 0 ]; then \
				echo test $$i: FAILURE; \
			else \
				echo test $$i: OK; \
			fi \
		fi \
	done
