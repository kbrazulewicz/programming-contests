#-----------------------------------------------------------------------------
PROG    = problem
SRC     = $(PROG).cpp
PROGEXEC = ../rpa/rpa.sh run --executable=./$(PROG) --nodes=20 --output=all
#-----------------------------------------------------------------------------
include ../makefile.global
#-----------------------------------------------------------------------------

$(PROG): $(PROG).cpp
	../rpa/rpa.sh build --source=$^

run: $(PROG)
	$(PROGEXEC)
