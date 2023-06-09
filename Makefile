EXEC := xasic
SRC := $(shell find src/ -type f -name '*.cpp') $(shell find src/ -type f -name '*.lex')
OBJ := $(addsuffix .o,$(basename $(SRC)))

CXXFLAGS  = -Ofast -Wall -Wextra -Wpedantic
override CXXFLAGS += -std=c++17

$(EXEC): $(OBJ)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

%.c %.h &: %.lex
	flex --header-file=$*.h -o $*.c $^

.PHONY: clean run
clean:
	rm -f $(OBJ) $(EXEC)

run: $(EXEC)
	./$^
