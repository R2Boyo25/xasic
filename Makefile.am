AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = xasic

xasic_SOURCES = src/data/data.cpp src/data/variable.cpp src/main.cpp src/heap/heap.cpp src/globals.cpp src/flex/xasic.c src/parser/xasic.c

MAINTAINERCLEANFILES := src/flex/xasic.c src/flex/xasic.h src/parser/xasic.c src/parser/xasic.h

CXXFLAGS = -Ofast -Wall -Wextra -Wpedantic -Werror
CFLAGS   = -Ofast -Wall -Wextra -Wpedantic -Werror
# -MMD does "free" dependency file generation.
override CXXFLAGS += -std=c++17
override CFLAGS += -std=c17 --include stdbool.h -Wno-unused-function

%.c %.h &: %.lex
	$(LEX) $(LEXFLAGS) --header-file=$*.h -o $*.c $^

%.c %.h &: %.y
	cd $(dir $^); $(firstword $(YACC)) $(YFLAGS) $(notdir $*).y --defines=$(notdir $*).h -o $(notdir $*).c

-include $(OBJ:%.o=%.d)
