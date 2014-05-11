#-----------------------------------------------------------------------------
PROG    = problem
SRC     = $(PROG).c
#-----------------------------------------------------------------------------
include ../makefile.global
#-----------------------------------------------------------------------------

test: all
	@for i in $(TEST_FILE); do \
        testIn=$$i; \
        testOut=`mktemp`; \
        testRef=`echo $$i | sed -e 's/\.in/\.out/'`; \
        if [ -f $$testIn -a -f $$testRef ]; then \
            ./$(PROG) < $$testIn > $$testOut; \
			test/odcchk.e $$testIn $$testOut; \
        fi; \
        if [ -f $${testIn}.bz2 -a -f $$testRef ]; then \
        	testInTmp=`mktemp`; \
            bzcat $${testIn}.bz2 > $$testInTmp; \
            ./$(PROG) < $$testInTmp > $$testOut; \
			test/tarchk.e $$testInTmp $$testOut; \
			rm $$testInTmp; \
        fi; \
		rm $$testOut; \
	done
