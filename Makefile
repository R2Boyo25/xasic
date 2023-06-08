# SRC += source/main.cpp source/globals.cpp source/data/data.cpp source/data/variable.cpp source/heap/heap.cpp
EXEC := xasic
SRC := $(shell find source/ -type f -name '*.cpp')
OBJ := $(addsuffix .o,$(basename $(SRC)))


CXXFLAGS  = -Ofast
CXXFLAGS += -std=c++17

$(EXEC): $(OBJ)

.PHONY: clean run
clean:
	rm $(OBJ) $(EXEC)

run: $(EXEC)
	./$^
