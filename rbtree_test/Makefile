NAME := a.out
CXX := clang++
CXXFLAGS := -Wall -Werror -Wextra -MMD -MP -g
SRCS :=	rb_tree.cpp
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
