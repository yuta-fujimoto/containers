NAME := a.out
CXX := clang++
CXXFLAGS := -Wall -Werror -Wextra -std=c++98  -pedantic-errors -MMD -MP 
SRCS :=	main.cpp
BINDIR := bin
OBJS := $(addprefix $(BINDIR)/, $(SRCS:.cpp=.o))
DEPENDS := $(addprefix $(BINDIR)/, $(SRCS:.cpp=.d))

## general rules ##

all : config $(NAME)

config:
	@if [ -e .doctest ]; then\
		git submodule update --init --recursive;\
	fi

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

-include $(BINDIR)/*.d
