PROG	= $(PA_PREFIX)

CFLAGS	= -O2 -Wall
CCFLAGS	= -O2 -Wall

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
	$(CXX) $(CCFLAGS) $^ -lm -o $@
endif


test: all
	@for i in test/*.in; do \
		testIn=$$i; \
		testOut=`mktemp`; \
		testRef=`echo $$testIn | sed -e 's/\.in$$/\.out/'`; \
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
			bzcat $${testIn}.bz2 | ./$(PROG) > $$testOut; \
			diff -w $$testOut $$testRef; \
			if [ $$? -ne 0 ]; then \
				echo test $$i: FAILURE; \
			else \
				echo test $$i: OK; \
			fi \
		fi; \
		rm -f $$testOut; \
	done
