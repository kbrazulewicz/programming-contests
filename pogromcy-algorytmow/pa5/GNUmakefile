PROG	= $(PA_PREFIX)
PA_TEST ?= 0 1 2 3 4 5 6 7 8 9 10

CFLAGS	= -O2 -static -Wall
CCFLAGS	= -O2 -static -Wall

all: $(PROG)

clean:
	rm -f $(PROG)

run: all
	./$(PROG)

ifeq ($(PA_LANG),c)
$(PROG): $(PROG).c
	$(CC) $(CFLAGS) $^ -lm -o $@
endif

ifeq ($(PA_LANG),cpp)
$(PROG): $(PROG).cpp
	$(CXX) $(CCFLAGS) -static $^ -lm -o $@
endif


test: all
	@for i in $(PA_TEST); do \
		testIn=test/$(PA_PREFIX)$$i.in; \
		testOut=/tmp/$(PA_PREFIX).out; \
		testRef=test/$(PA_PREFIX)$$i.out; \
		if [ -f $$testIn ]; then \
			./$(PROG) < $$testIn > $$testOut; \
			diff -w $$testOut $$testRef /dev/null 2>&1; \
			if [ $$? -ne 0 ]; then \
				echo test $$i: FAILURE; \
			else \
				echo test $$i: OK; \
			fi \
		fi; \
		if [ -f $${testIn}.bz2 ]; then \
			bzcat $${testIn}.bz2 | ./$(PROG) > $$testOut; \
			diff -w $$testOut $$testRef /dev/null 2>&1; \
			if [ $$? -ne 0 ]; then \
				echo test $$i: FAILURE; \
			else \
				echo test $$i: OK; \
			fi \
		fi \
	done
