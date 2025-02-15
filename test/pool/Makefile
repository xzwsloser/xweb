SRC_TAR = $(wildcard *.cc)
SRC = $(wildcard ../../logger/*.cc ../../pool/*.cc ../../reactor/*.cc ../../utils/*.cc)
INC := ../../
TARGET = $(patsubst %.cc,%,$(SRC_TAR))
CC := g++

all: $(TARGET)
$(TARGET):%:%.cc
	$(CC) $< $(SRC) -o $@ -I ../../
