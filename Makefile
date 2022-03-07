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

-include $(BINDIR)/*.d

## debug and test rules ##

gdb: CXXFLAGS+=-g
gdb: re

debug: CXXFLAGS+=-g -fsanitize=address
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

CXXFLAG		:= -std=c++11 -DDEBUG -g -fsanitize=address
# gTestDir	:= ./.google_test
# gVersion	:= release-1.11.0
# gTestVer	:= googletest-$(gVersion)
# gTest		:= $(gTestDir)/gtest $(gTestDir)/$(gTestVer)
INCLUDE		:= -I./.doctest/doctest/

TESTDIR		:= ./tests/
# TESTSRCS_C	:= $(filter-out main.c,$(SRCS))
TESTSRCS_CPP:= $(wildcard $(TESTDIR)*.cpp)
TESTOBJS	:= $(addprefix $(SRCDIR), $(TESTSRCS_CPP:%.cpp=%.o))

%.o: %.cpp
	$(CXX) $(CXXFLAG) $(INCLUDE) -c $< -o $@

# $(gTest):
# 	mkdir -p $(gTestDir)
# 	curl -OL https://github.com/google/googletest/archive/refs/tags/$(gVersion).tar.gz
# 	tar -xvzf $(gVersion).tar.gz $(gTestVer)
# 	$(RM) $(gVersion).tar.gz
# 	python3 $(gTestVer)/googletest/scripts/fuse_gtest_files.py $(gTestDir)
# 	mv $(gTestVer) $(gTestDir)

# gtest: $(gTest) $(TESTOBJS)
# 	$(CXX) $(CXXFLAG) \
# 		$(TESTOBJS) \
# 		$(gTestDir)/$(gTestVer)/googletest/src/gtest_main.cc \
# 		$(gTestDir)/gtest/gtest-all.cc \
# 		-I$(gTestDir) -I../ $(INCLUDE) $(LIBS) -lpthread -o tester && ./tester

test: CXX=clang++
test: $(TESTOBJS) $(OBJS)
	$(CXX) $(CXXFLAG) $(TESTOBJS) -o tester && ./tester

t_clean: FORCE
	$(RM) $(TESTOBJS)

t_fclean: t_clean
	$(RM) -r tester tester.dSYM

tre: t_fclean test
