EXEC := xasic
SRC := $(shell find src/ -type f -name '*.cpp') $(shell find src/ -type f -name '*.lex')
OBJ := $(addsuffix .o,$(basename $(SRC)))

CXXFLAGS  = -Ofast -Wall -Wextra -Wpedantic
override CXXFLAGS += -std=c++17 -MMD
override CFLAGS += -MMD


$(EXEC): $(OBJ)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

%.c %.h &: %.lex
	flex $(LEXFLAGS) --header-file=$*.h -o $*.c $^

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: run
run: $(EXEC)
	./$^

.PHONY: test
test: $(EXEC)
	bash test/test.sh ./$^

.PHONY: emacsclean
emacsclean:
	rm -f $(shell find -type f -name '*~')
	rm -f $(shell find -type f -name '#*#')

.PHONY: depclean
depclean:
	rm -f $(shell find -type f -name "*.d")

-include $(OBJ:%.o=%.d)
