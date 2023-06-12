EXEC := xasic
SRC := $(shell find src/ -type f -name '*.cpp') $(shell find src/ -type f -name '*.lex') $(shell find src/ -type f -name "*.y")
OBJ := $(addsuffix .o,$(basename $(SRC)))

CXXFLAGS = -Ofast -Wall -Wextra -Wpedantic -Werror
# -MMD does "free" dependency file generation.
override CXXFLAGS += -std=c++17 -MMD
override CFLAGS += -MMD
YACCFLAGS = 

$(EXEC): $(OBJ)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

%.c %.h &: %.lex
	flex $(LEXFLAGS) --header-file=$*.h -o $*.c $^

%.c %.h &: %.y
	cd $(dir $^); bison $(YACCFLAGS) $(notdir $*).y --defines=$(notdir $*).h -o $(notdir $*).c

.PHONY: run
run: $(EXEC)
	./$^

.PHONY: test
test: $(EXEC)
	bash test/test.sh ./$^

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: emacsclean
emacsclean:
	rm -f $(shell find -type f -name '*~')
	rm -f $(shell find -type f -name '#*#')

.PHONY: depclean
depclean:
	rm -f $(shell find -type f -name "*.d")

-include $(OBJ:%.o=%.d)
