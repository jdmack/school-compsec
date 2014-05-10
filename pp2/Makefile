# tools
CC := gcc
RM := rm -f
CP := cp

# flags
CFLAGS := -ggdb -O1 -m32 -fno-stack-protector
LDFLAGS :=
LDLIBS :=

# sources
sources := cmdb.c cmdb_generate.c
targets := cmdb test_local

# gmake magic
.PHONY: default all clean generate

#targets
default: all
all: $(targets)

generate:
	./generate.py

clean:
	$(RM) $(targets) cmdb_generate.c cmdb_struct.h cmdb_generate.o

install:
	$(CP) cmdb /tmp/

python:
	python -m py_compile sploit.py
#dependencies
install: cmdb
cmdb: cmdb_generate.o
cmdb_generate.o: cmdb_generate.c
