CC = gcc
FLAGS = -Wall -Werror -Wextra # -std=c11 -g -fsanitize=address
TEST_FLAGS = -lcheck -lm -lpthread
FLAG_COV = -lcheck -lgcov -fprofile --coverage
TARGET = calc/build/newCalc.app/Contents/MacOS/newCalc
TAR = calc.tar.gz
ifeq ($(shell uname), Linux)
	TEST_FLAGS += -lrt -lsubunit
	FLAG_COV = -lcheck -lgcov -lm -lpthread -lsubunit --coverage
endif

.PHONY: all
all: dvi dist gcov_report## install and run program
	$(TARGET)

.PHONY: install
install: ## install and run program
	cd ./calc/build && cmake ../ && $(MAKE) all

.PHONY: uninstall
uninstall:
	rm -fr ./calc/build/*

.PHONY: dvi
dvi: ## generate and open doc
	cd doxygen && ./doxygen Doxyfile && open html/index.html

.PHONY: dist
dist: install ## archive executable
	tar -zcf $(TAR) $(TARGET)

.PHONY: lint ## run linters
lint:
	cp ../materials/linters/.clang-format ./
	clang-format -n *.c
	rm .clang-format
# cppcheck --enable=all --suppress=missingIncludeSystem *.c

.PHONY: gcov_report
gcov_report: test
	gcc -o test s21_smart_calc.a s21_smart_calc.c ./tests/s21_smart_calc_test.c $(FLAG_COV)
	./test
	lcov -t "gcov_report" -o gcov_report.info -c -d ./
	genhtml -o report gcov_report.info
	rm *.gcno *.gcda

.PHONY: test
test: s21_smart_calc.a 
	$(CC) $(FLAGS) tests/s21_smart_calc_test.c s21_smart_calc.a $(TEST_FLAGS) -o test
	./test
	rm *.o

.PHONY: s21_smart_calc.a 
s21_smart_calc.a: o_files
	ar rcs s21_smart_calc.a *.o
	ranlib s21_smart_calc.a

.PHONY: o_files
o_files:
	gcc -c ./s21_smart_calc.c

.PHONY: clean
clean: 
	rm -fr ./calc/build/* ./doxygen/html report s21_smart_calc.o s21_smart_calc.a test gcov_report.info *.gcno *.gcda*.o .clang-format calc.tar.gz

