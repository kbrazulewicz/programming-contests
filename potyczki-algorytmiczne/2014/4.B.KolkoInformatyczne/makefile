#-----------------------------------------------------------------------------
PROG    = kol
PROGLIB = $(PROG)lib
PROGEXEC = ../message/run 20 $(PROG).e
TOCLEAN += $(PROGLIB).impl.o $(PROG).o $(PROG).e
#-----------------------------------------------------------------------------
include ../makefile.global
#-----------------------------------------------------------------------------

$(PROG): $(PROG).cc $(PROGLIB).cc
	../message/compile $^

run: $(PROG)
	../message/run 20 $(PROG).e

run-tag: $(PROG)
	../message/run --tag 20 $(PROG).e