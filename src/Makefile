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
	PATH_APP = SmartCalc_v2.0/SmartCalc_v2
	ADD_LIB = -lgtest -lpthread -lm
	GCOV_FLAGS = 
endif

ifeq ($(UNAME_S),Darwin)
	OPEN_CMD = open -a "Google Chrome"
	LEAKS_CMD = leaks -atExit --
	PATH_APP = SmartCalc_v2.0/SmartCalc_v2.app/Contents/MacOS/SmartCalc_v2
	ADD_LIB = -lgtest -lm
	GCOV_FLAGS = --ignore-errors mismatch
endif

all: install

install:
	@rm -rf SmartCalc_v2.0
	@mkdir SmartCalc_v2.0
	@cd SmartCalc_v2.0/ && qmake ../view/SmartCalc_v2.0.pro && make -j6 && make clean && rm -rf Makefile .qmake.stash

uninstall:
	@rm -rf SmartCalc_v2.0

start:
	@cd SmartCalc_v2.0/ ./SmartCalc_v2

dist: install
	@rm -rf dist
	@mkdir dist
	@cp -R $(PATH_APP) model view controller tests Makefile README.md dist
	@cd dist && tar cvzf SmartCalc_v2.0.tgz * && rm -rf controller model tests view SmartCalc_v2 Makefile README.md
	@rm -rf SmartCalc_v2.0

dvi:
	@$(OPEN_CMD) README.md

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

