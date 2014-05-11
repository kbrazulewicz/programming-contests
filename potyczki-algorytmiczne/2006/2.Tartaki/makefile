#-----------------------------------------------------------------------------
PROG    = problem
SRC     = $(PROG).c
#-----------------------------------------------------------------------------
include ../makefile.global
#-----------------------------------------------------------------------------

test: all
	@for i in $(TEST_FILE); do \
        testIn=$$i; \
        testRef=`echo $$i | sed -e 's/\.in/\.out/'`; \
        testOut=`mktemp`; \
		testInTmp=`mktemp`; \
		testRefTmp=`mktemp`; \
        if [ -f $$testRef ]; then \
			cp $$testRef $$testRefTmp; \
		elif [ -f $${testRef}.bz2 ]; then \
            bzcat $${testRef}.bz2 > $$testRefTmp; \
		else \
			continue; \
		fi; \
        if [ -f $$testIn ]; then \
            ./$(PROG) < $$testIn > $$testOut; \
			test/tarchk.e $$testIn $$testOut; \
        fi; \
        if [ -f $${testIn}.bz2 -a -f $$testRef ]; then \
            bzcat $${testIn}.bz2 > $$testInTmp; \
            ./$(PROG) < $$testInTmp > $$testOut; \
			test/tarchk.e $$testInTmp $$testOut; \
        fi; \
		rm $$testOut; \
		rm $$testInTmp; \
		rm $$testRefTmp; \
	done
