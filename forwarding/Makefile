SHELL =/bin/bash
CXX = g++
CXXFLAGS = -std=c++14 -g
INC = -I ./include
DIRS = trg output err 

VERLIST = 0 1 2 3 4 5 6
vers = $(addprefix VER, $(VERLIST))

TRGDIR = trg
ERRDIR = err
COMPDIR = trg err
OUTDIR = output
SRCDIR = src


USECASE = UC_A UC_B UC_C UC_D UC_E UC_F

BUILD= $(patsubst %, %/result, $(USECASE))
_SRCS = $(addsuffix .cpp, $(USECASE))
SRCS = $(patsubst %, $(SRCDIR)/%, $(_SRCS))

.PHONY: clean result

all: result #test

result: $(patsubst %, result/%, $(USECASE))

result/UC_%: $(SRCDIR)/UC_% 
	mkdir -p $(patsubst %, %/$(@F),$(OUTDIR))
	for file in $(notdir $(wildcard $(TRGDIR)/$(@F)/*)); \
		do \
		$(TRGDIR)/$(@F)/$$file > $(OUTDIR)/$(@F)/$$file.output; \
	done

$(SRCDIR)/UC_%:
	mkdir -p $(patsubst %, %/$(@F),$(COMPDIR))
	for ver in $(vers); \
		do \
		$(CXX) $(CXXFLAGS) $@.cpp -o $(TRGDIR)/$(@F)/$$ver -D$$ver $(INC) >& $(ERRDIR)/$(@F)/$$ver.err ; \
	done

clean:
	rm -rf $(DIRS)
