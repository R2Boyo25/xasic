AUTOMAKE_OPTIONS = foreign
bin_PROGRAMS = xasic

xasic_SOURCES = src/data/data.cpp src/data/data.hpp src/data/variable.cpp src/data/variable.hpp src/main.cpp src/heap/heap.cpp src/heap/heap.hpp src/globals.cpp src/globals.hpp src/flex/xasic.h src/parser/xasic.h src/parser/xasic.y src/flex/xasic.l

MAINTAINERCLEANFILES := src/flex/xasic.c src/flex/xasic.h src/parser/xasic.c src/parser/xasic.h
CLEANFILES := *~ \#*\#

CXXFLAGS = -Ofast -Wall -Wextra -Wpedantic -Werror
CFLAGS   = -Ofast -Wall -Wextra -Wpedantic -Werror
# -MMD does "free" dependency file generation.
override CXXFLAGS += -std=c++17
override CFLAGS += -std=c17 -Wno-unused-function

%.c %.h &: %.l
	$(LEX) $(LEXFLAGS) --header-file=$*.h -o $*.c $^

%.c %.h &: %.y
	cd $(dir $^); $(firstword $(YACC)) $(YFLAGS) $(notdir $*).y --defines=$(notdir $*).h -o $(notdir $*).c

src/main.o: src/flex/xasic.h src/parser/xasic.h

.PHONY: test
test: xasic
	bash test/test.sh ./$^

-include $(OBJ:%.o=%.d)
