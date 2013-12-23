ObjSuf        = o
SrcSuf        = cc
ExeSuf        = 
DllSuf        = so
OutPutOpt     = -o
HeadSuf       = h

ROOTCFLAGS    = $(shell root-config --cflags)
ROOTLIBS      = $(shell root-config --libs) 
ROOTGLIBS     = $(shell root-config --libs)

# Linux with egcs
DEFINES       = 
CXX           = g++
CXXFLAGS      = -O -Wall -fPIC $(DEFINES) -Wno-unused-result
LD            = g++ 
LDFLAGS       = -g -O -Wall -fPIC -Wl,--no-undefined
SOFLAGS       = -shared

CXXFLAGS      += $(ROOTCFLAGS) -I./
LIBS          = $(ROOTLIBS)  -lEG 
#------------------------------------------------------------------------------
SOURCES       = $(wildcard src/*.cc)
OBJECTS       = $(SOURCES:.$(SrcSuf)=.$(ObjSuf))
#------------------------------------------------------------------------------

all:  libSonicScrewdriver.so

libSonicScrewdriver.so: $(OBJECTS) 
	@echo "Building libSonicScrewdriver..."
	$(LD) -L${ROOTSYS}/lib $+ -o $@ $(LIBS) $(SOFLAGS) $(LDFLAGS)

test:
	@make -C test test

clean:
	@echo "Cleaning..."
	@rm -f $(OBJECTS)

.SUFFIXES: .$(SrcSuf) .C .o .so

.PHONY : test


 


