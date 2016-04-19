TOP      = $(shell pwd)

# OS Name (Linux or Darwin)
OSUPPER = $(shell uname -s 2>/dev/null | tr [:lower:] [:upper:])
OSLOWER = $(shell uname -s 2>/dev/null | tr [:upper:] [:lower:])

# Flags to detect 32-bit or 64-bit OS platform
OS_SIZE = $(shell uname -m | sed -e "s/i.86/32/" -e "s/x86_64/64/")
OS_ARCH = $(shell uname -m | sed -e "s/i386/i686/")

# Flags to detect either a Linux system (linux) or Mac OSX (darwin)
DARWIN = $(strip $(findstring DARWIN, $(OSUPPER)))

# OS-specific build flags
ifneq ($(DARWIN),)
    CXXFLAGS   := -arch $(OS_ARCH)
else
  ifeq ($(OS_SIZE),32)
    CXXFLAGS   := -m32
  else
    CXXFLAGS   := -m64
  endif
endif

# COMPILERS OPTIONS
ifneq ($(DARWIN),)
  CXX          := g++-mp-4.9
  #CXX          := gcc
else
  CXX          := g++
endif

#CXXFLAGS       += -std=c++11 -fPIC
OPTIMFLAGS      = #-O2 -funroll-loops -falign-loops=8

ARCHIVE      := ar
ARCHFLAG     := -rc

# Debug build flags
ifeq ($(DEBUGVERSION),1)
  CXXFLAGS     += -DDEBUG=1 -g -W -Wall -pedantic -Wno-long-long
else
  CXXFLAGS     += -DDEBUG=0 $(OPTIMFLAGS)
endif

ifeq ($(USE_FLOATS_FOR_REALS),)
  CXXFLAGS     += -DUSE_FLOATS_FOR_REALS=0 
else
  CXXFLAGS     += -DUSE_FLOATS_FOR_REALS=$(USE_FLOATS_FOR_REALS)
endif

#INCDEFS        := -include localdefs.h

# FILES
COBJS=$(patsubst %.c,%.o,$(wildcard *.c))
CCOBJS=$(patsubst %.cc,%.o,$(wildcard *.cc))
CPPOBJS=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
OBJS= $(CCOBJS) $(CPPOBJS) $(COBJS)
HEADERS=$(wildcard *.h)
LIBOBJS=$(shell echo $(OBJS) | sed 's/main\.o//')
STATICLIB=$(shell pwd | sed 's;\(.*\)/\(.*\);\2.a;')

# -L: FOLDER LIBRARY
	LFLAGS+=#-L/usr/lib
	LFLAGS+=#-L.

# -l: LIBRARY
	lLIBS+=#-lgfnl_util
	lLIBS+= #-lapr-1 -laprutil-1 -llog4cxx

# -I: INCLUDES
	IFLAGS+=-I.

TARGET=target

$(TARGET): $(OBJS)
	$(info LINKING: $@)
	@$(CXX) -o main $(OBJS) $(LFLAGS) $(lLIBS) 
	$(info ARCHIVING: $(LIBOBJS))
	@$(ARCHIVE) $(ARFLAGS) $(STATICLIB) $(LIBOBJS)

$(COBJS): %.o: %.c
	$(info compiling: $@)
	@$(CXX) $(CXXFLAGS) -c $<  -o $@  $(IFLAGS) 

$(CPPOBJS): %.o: %.cpp
	$(info compiling: $@)
	@$(CXX) $(CXXFLAGS) -c $<  -o $@  $(IFLAGS) 

$(CCOBJS): %.o: %.cc		 
	$(info compiling: $@)
	@$(CXX) $(CXXFLAGS) -c $<  -o $@  $(IFLAGS) 

.PHONY: clean
clean:
	$(info CLEANING ALL)
	@$(RM) -f main
	@$(RM) -f $(TARGET) $(OBJS) $(STATICLIB) 2>/dev/null || true


list:
	@echo $(OBJS)
	@echo $(HEADERS)

listobjs:
	@echo $(LIBOBJS)

###########################################################################################
docu:
	@echo
	$(info Generating doxygen docu in : /doc/DOXYGEN_DOCUMENTATION)
	@echo
	cd src; doxygen ../doc/config-file-doxygen; mv DOXYGEN_DOCUMENTATION ../doc

