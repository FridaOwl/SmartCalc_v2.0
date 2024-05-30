.PHONY: all test gcov clean leaks style install uninstall
CC = g++
CPPFLAGS = -Wall -Werror -Wextra -std=c++17 -lstdc++
OBJ_MODEL = model/*.cc
OBJ_CONTROLLER = controller/*.cc
OBJ_TEST = tests/test.cc
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
  	OPEN_CMD = xdg-open
	LEAKS_CMD = valgrind --tool=memcheck --leak-check=yes
	PATH_APP = MyCalculator/MyCalc
	ADD_LIB = -lgtest -lpthread -lm
	GCOV_FLAGS = 
endif

ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open -a "Google Chrome"
	LEAKS_CMD = leaks -atExit --
	PATH_APP = MyCalculator/MyCalc.app/Contents/MacOS/MyCalc
	ADD_LIB = -lgtest -lm
	GCOV_FLAGS = --ignore-errors mismatch
endif

all: install

install:
	@rm -rf MyCalculator
	@mkdir MyCalculator
	@cd MyCalculator/ && qmake ../view/MyCalculator.pro && make -j6 && make clean && rm -rf Makefile .qmake.stash

uninstall:
	@rm -rf MyCalculator

start:
	@cd MyCalculator/ ./MyCalc

dist: install
	@rm -rf dist
	@mkdir dist
	@cp -R $(PATH_APP) model view controller tests Makefile dvi.md dist
	@cd dist && tar cvzf MyCalculator.tgz * && rm -rf controller model tests view MyCalc Makefile dvi.md
	@rm -rf MyCalculator

dvi:
	@$(OPEN_CMD) dvi.md

test:
	@$(CC) $(CPPFLAGS) $(OBJ_TEST) $(OBJ_MODEL) $(OBJ_CONTROLLER) -o test $(ADD_LIB)
	@./test

test_leaks:
	@$(CC) $(CPPFLAGS) $(OBJ_TEST) $(OBJ_MODEL) $(OBJ_CONTROLLER) -o test_leaks $(ADD_LIB)
	@$(LEAKS_CMD) ./test_leaks

gcov:
	@$(CC) $(CPPFLAGS) --coverage $(OBJ_TEST) $(OBJ_MODEL) $(OBJ_CONTROLLER) -o test $(ADD_LIB)
	@./test
	@rm -rf test.gcda test.gcno
	@lcov -t "test" -o test.info -c -d . $(GCOV_FLAGS)
	@genhtml -o report test.info
	@$(OPEN_CMD) report/index.html

style:
	@clang-format -style=Google -n */*.h */*.cc view/*.cpp

clean:
	@-rm -rf *.o *.gcno *.gcda *.info *.gcov *.a *.dSYM report test test_leaks main *.out

