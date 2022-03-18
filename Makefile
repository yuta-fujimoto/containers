NAME := a.out
CXX := clang++
CXXFLAGS := -Wall -Werror -Wextra -std=c++98  -pedantic-errors -MMD -MP 
SRCS :=	main.cpp
BINDIR := bin
OBJS := $(addprefix $(BINDIR)/, $(SRCS:.cpp=.o))
DEPENDS := $(addprefix $(BINDIR)/, $(SRCS:.cpp=.d))

## general rules ##

all :$(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
	
$(BINDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BINDIR):
	mkir -p $@

clean: FORCE
	rm -f $(OBJS) $(DEPENDS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY:	FORCE
FORCE:

## debug and test rules ##

gdb: CXXFLAGS+=-g
gdb: re

debug: CXXFLAGS+=-g -fsanitize=address -fsanitize=undefined
debug: re

cover: CXX=g++
cover: re
cover: CXXFLAGS+= -g -fprofile-arcs -ftest-coverage
cover:
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)
	./$(NAME)
	lcov -c -b . -d . -o cov_test.info
	genhtml cov_test.info -o cov_test
	rm *.png
	rm -rf cov_test.info *.png tester *.gcda *.gcno *.info

#  Google test #
# -fsanitize=integer

CXXFLAG		:= -std=c++98 -DDEBUG -g -fsanitize=address
INCLUDE		:= -I./.doctest/doctest/

TESTDIR		:= ./tests/
# TESTSRCS_C	:= $(filter-out main.c,$(SRCS))
TESTSRCS_CPP:= $(wildcard $(TESTDIR)*.cpp)
TESTOBJS	:= $(addprefix $(SRCDIR), $(TESTSRCS_CPP:%.cpp=%.o))

%.o: %.cpp
	$(CXX) $(CXXFLAG) $(INCLUDE) -c $< -o $@

test: CXX=clang++
test: $(TESTOBJS) $(OBJS)
	$(CXX) $(CXXFLAG) $(TESTOBJS) -o tester && ./tester

tclean: FORCE
	$(RM) $(TESTOBJS)

tfclean: tclean
	$(RM) -r tester tester.dSYM

tre: tfclean test

-include $(BINDIR)/*.d
