CC := g++
src_target = $(wildcard *.cc)
target = $(patsubst %.cc,%,$(src_target))
SRC = $(wildcard ../../src/logger/*.cc  ../../src/utils/*.cc ../../src/reactor/*.cc ../../src/timer/*.cc  ../../src/server/*.cc ../../src/pool/*.cc) 

all: $(target)

$(target):%:%.cc
	$(CC) $< $(SRC) -o $@  -I ../../src/

clean:
	-rm -rf $(target)
.PHONY: clean all
