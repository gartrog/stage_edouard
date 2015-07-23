cpputilsdir = ../cpp-root-utils/
CXXFLAGS = -g -O2 $(shell root-config --cflags --ldflags) -I$(shell root-config --incdir) -I$(cpputilsdir)/include -fPIC -std=c++11
CXX = g++ $(CXXFLAGS)
curdir = $(shell pwd -P)
LINKFLAGS = -L$(shell root-config --libdir --libs) -L$(cpputilsdir)/lib -lUtils -Wl,-R -Wl,$(cpputilsdir)/lib

.PHONY: clean

all: bin

bin: run

run: run.cxx VHAnalysis.o VHNtuple.o BTagging.o
	$(CXX) $(LINKFLAGS) -o run $^

VHAnalysis.o : VHAnalysis.cxx
	$(CXX) -c -o $@ $^

VHNtuple.o : VHNtuple.C
	$(CXX) -c -o $@ $^

BTagging.o : BTagging.cxx
	$(CXX) -c -o $@ $^

clean:
	rm -f run

