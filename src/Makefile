DIRBUILD = build
DIRTESTLOGS = test_logs

DIRFILES = functions
CFILES = $(DIRFILES)/*.c 
OBJFILES = $(patsubst $(DIRFILES)/%.c,$(DIRBUILD)/%.o,$(CFILES))

NAMETEST = test
FILETEST = $(NAMETEST).c
OBJTEST = $(DIRBUILD)/$(FILETEST:.c=.o)
LIBTEST = $(FILETEST:.c=.a)
GCNOTESTFILES = $(DIRBUILD)/*.gcno

LIBDEC = s21_matrix.a

CC = gcc
FORMAT = clang-format
CFLAGS = -Wall -Werror -Wextra -g -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage

OS := $(shell uname -s)
ifeq ($(OS), Linux)
	CHECKFLAGS = -lcheck -lm -lrt -lpthread -lsubunit
	MEMLEAKAGE = sleep 2; CK_FORK=no valgrind --leak-check=full --track-origins=yes -s ./$(NAMETEST)
else
	CHECKFLAGS = -lcheck
	MEMLEAKAGE = sleep 2; leaks -atExit -- ./$(NAMETEST) | grep LEAK:
endif

all : clean gcov_report

s21_matrix.a :
	mkdir $(DIRBUILD) $(DIRTESTLOGS)
	$(CC) $(CFLAGS) -c $(CFILES)
	mv *.o $(DIRBUILD)
	ar rc $(LIBDEC) $(OBJFILES)
	ranlib $(LIBDEC)

test : s21_matrix.a
	$(CC) $(CFLAGS) $(GCOVFLAGS) -c $(FILETEST)
	mv *.o $(DIRBUILD)
	ar rc $(LIBTEST) $(OBJTEST)
	ranlib $(LIBTEST)
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o $(NAMETEST) $(LIBDEC) $(LIBTEST) $(CFILES) $(CHECKFLAGS)
	./$(NAMETEST)
	mv *.gcda *.gcno $(DIRBUILD) 

gcov_report : test
	$(foreach file, $(wildcard $(GCNOTESTFILES)), gcov $(file);)
	lcov --capture --directory . --output-file html.info
	genhtml -o gcov_report html.info
	echo "Code coverage report generated in gcov_report directory."
	mv *.info $(DIRBUILD)
	open gcov_report/index.html
	mv *.gcov $(DIRBUILD)

clean :
	-rm -rf gcov_report *.a *.o *.gcno *.gcda
	-rm -f test
	-rm -R $(DIRBUILD) $(DIRTESTLOGS)

style :
	$(FORMAT) -i -style=Google *.c *.h */*.c

checking : clean test
	clear
	$(FORMAT) -n -style=Google *.c *.h */*.c
	$(MEMLEAKAGE)
	sleep 2; cppcheck --enable=all --suppress=missingIncludeSystem *.c
	-rm -R $(DIRBUILD) $(DIRTESTLOGS)
	-rm -rf gcov_report *.a *.gcda $(NAMETEST)

