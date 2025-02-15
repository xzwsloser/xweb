CC := g++
src_target = $(wildcard *.cc)
target = $(patsubst %.cc,%,$(src_target))
SRC = $(wildcard ../../logger/*.cc ../../utils/*.cc ../../reactor/*.cc)

all: $(target)

$(target):%:%.cc
	$(CC) $< $(SRC) -o $@  -I ../../

clean:
	-rm -rf $(target)
.PHONY: clean all
