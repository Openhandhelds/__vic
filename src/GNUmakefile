##############################################################################
# GNU Make 3.82+ Makefile
#
# Usage:
#   $ gmake [compiler={gcc|clang|msvc}] [std={98|11|14|17}]

include ../src/defs.mk
std = 14
compiler = gcc

##############################################################################
ifeq ($(compiler),gcc)
CC     := g++ -std=c++$(std) -mthreads
CFLAGS := -pedantic-errors -DNDEBUG -O3 -ffunction-sections -fdata-sections
WARNS  := $(if $(filter 98,$(std)),-Wno-long-long)
binutils = 1
##############################################################################
else ifeq ($(compiler),clang)
CC     := clang++
TARGET := -target $(patsubst %-msvc,%-gnu,$(lastword $(shell $(CC) --version|find "Target:")))
CC     += -std=c++$(std) $(TARGET) -pthread
CFLAGS := -pedantic-errors -DNDEBUG -O3
WARNS  := $(if $(filter 98,$(std)),-Wno-long-long )-Wno-non-literal-null-conversion
binutils = 1
##############################################################################
else ifeq ($(compiler),msvc)
ifneq ($(origin std),file)
$(error std option is not supported by MSVC++ compiler)
endif
std    :=
CC     := cl /nologo /Zc:__cplusplus /permissive-
CFLAGS := -DNDEBUG -D_CRT_SECURE_NO_DEPRECATE -O2 -Ob1
WARNS  :=
endif
##############################################################################

LIBSUFFIX = $(std)
ifdef binutils
OBJSUFF = o
ARSUFF = a
LIBFILE := lib$(LIBNAME)$(LIBSUFFIX).$(ARSUFF)
AR = ar
ARFLAGS = s
ARFLAGS_ALL = r$(ARFLAGS) $@
else
OBJSUFF = obj
ARSUFF = lib
LIBFILE := $(LIBNAME)$(LIBSUFFIX).$(ARSUFF)
AR = lib
ARFLAGS =
ARFLAGS_ALL = -nologo $(ARFLAGS) /OUT:$@
endif
CFLAGS_ALL = -I../include -DUNICODE=1 $(CFLAGS) $(WARNS)

ifndef SOURCES
SOURCES := $(wildcard *.cpp)
endif
OBJS := $(patsubst %.cpp,%.$(OBJSUFF),$(SOURCES))

.PHONY: clean
include ../src/rules.mk