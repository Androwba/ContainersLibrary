CXX = g++ -std=c++17

SOURCES = containers/*.h
SOURCE_TREE = main_tree.cc
OUT_TREE = a.out

SOURCE_TEST = main_test.cc
OUT_TEST = s21_containers_test
RM = rm -rf

OS=$(shell uname)
ifeq ($(OS), Linux)
CPPFLAGS_TEST = -lgtest -lpthread -L/usr/lib
LEAK_CHECK = valgrind --leak-check=full -s
OPEN := xdg-open ./report/index.html
endif
ifeq ($(OS), Darwin)
CPPFLAGS_TEST = -lgtest
LEAK_CHECK = leaks -q --atExit --
OPEN := open ./report/index.html
endif

all: clean test

test: clean
	$(CXX) $(SOURCE_TEST) $(CPPFLAGS_TEST) -o $(OUT_TEST)
	./$(OUT_TEST)

leaks: test
	$(LEAK_CHECK) ./$(OUT_TEST)

check:
	cppcheck --language=c++ containers/*
	cp ../materials/linters/.clang-format ./containers
	cp ../materials/linters/.clang-format ./tests
	cp ../materials/linters/.clang-format ./
	clang-format -i *.cc
	clang-format -i *.h
	clang-format -i ./containers/*.h
	clang-format -i ./tests/*.cc
	clang-format -n *.cc
	clang-format -n *.h
	clang-format -n ./containers/*.h
	clang-format -n ./tests/*.cc
	$(RM) .clang-format
	$(RM) ./containers/.clang-format
	$(RM) ./tests/.clang-format

gcov_report: clean
	$(CXX) --coverage $(SOURCE_TEST) -o s21_test $(CPPFLAGS_TEST)
	./s21_test
	lcov -t "s21_test" -o s21_test.info --no-external -c -d .
	genhtml -o report s21_test.info
	$(OPEN)

clean:
	$(RM) ./lcov_report
	$(RM) *.gcno *.out *.dSYM *.gcda *.gcov *.info a.out ./$(OUT_TEST) *.txt ./s21_test ./gcov_tests report

# visualization of red-black tree
tree:
	@$(CXX) $(SOURCE_TREE) && ./$(OUT_TREE)
