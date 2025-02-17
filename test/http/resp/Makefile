SOURCE = $(wildcard *.cc)
SRC = $(wildcard ../../../src/*/*.cc ../../../src/*/*/*.cc ../../../src/*/*/*/*.cc)
INC = $(wildcard ../../../src/)
CC = g++

TARGET = $(patsubst %.cc,%,$(SOURCE))

All: $(TARGET)

$(TARGET):%:%.cc
	$(CC) $< $(SRC) -o $@ -I $(INC)

clean:
	-rm -rf $(TARGET)
.PHONY: all clean
