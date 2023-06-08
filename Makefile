# SRC += source/main.cpp source/globals.cpp source/data/data.cpp source/data/variable.cpp source/heap/heap.cpp
EXEC := xasic
SRC := $(shell find src/ -type f -name '*.cpp')
OBJ := $(addsuffix .o,$(basename $(SRC)))


CXXFLAGS  = -Ofast
CXXFLAGS += -std=c++17

$(EXEC): $(OBJ)

.PHONY: clean run
clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$^
