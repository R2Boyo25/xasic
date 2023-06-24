EXEC := xasic
LEXFILES  := $(shell find src/ -type f -name '*.lex')
YACCFILES := $(shell find src/ -type f -name "*.y")
SRC := $(shell find src/ -type f -name '*.cpp') $(LEXFILES) $(YACCFILES)
OBJ := $(addsuffix .o,$(basename $(SRC)))

CXXFLAGS = -Ofast -Wall -Wextra -Wpedantic -Werror
CFLAGS   = -Ofast -Wall -Wextra -Wpedantic -Werror
# -MMD does "free" dependency file generation.
override CXXFLAGS += -std=c++17 -MMD
override CFLAGS += -std=c17 -MMD --include stdbool.h -Wno-unused-function
YACCFLAGS = 

$(EXEC): $(OBJ)
	$(CXX) $(CFLAGS) $(CXXFLAGS) $(LDFLAGS) $^ -o $@

%.c %.h &: %.lex
	flex $(LEXFLAGS) --header-file=$*.h -o $*.c $^

%.c %.h &: %.y
	cd $(dir $^); bison $(YACCFLAGS) $(notdir $*).y --defines=$(notdir $*).h -o $(notdir $*).c

src/main.o: src/flex/xasic.h src/parser/xasic.h

.PHONY: run
run: $(EXEC)
	./$^

.PHONY: test
test: $(EXEC)
	bash test/test.sh ./$^

.PHONY: clean
clean:
	rm -f $(OBJ) $(EXEC)

.PHONY: distclean
distclean: clean emacsclean depclean

.PHONY: emacsclean
emacsclean:
	rm -f $(shell find -type f -name '*~')
	rm -f $(shell find -type f -name '#*#')

.PHONY: depclean
depclean:
	rm -f $(shell find -type f -name "*.d")

.PHONY:	genclean
genclean:
	rm -f $(LEXFILES:%.lex=%.c) $(LEXFILES:%.lex=%.h) $(YACCFILES:%.y=%.c) $(YACCFILES:%.y=%.h)

.PHONY: install
install: $(EXEC)
	install $^ $(addprefix /usr/bin/,$^)

-include $(OBJ:%.o=%.d)
