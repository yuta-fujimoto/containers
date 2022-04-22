NAME := a.out
CXX := clang++
CXXFLAGS := -Wall -Werror -Wextra -std=c++98 -pedantic-errors -MMD -MP -DDEBUG -g -fsanitize=address
SRCS :=	$(wildcard *.cpp)
BINDIR := bin
OBJS := $(addprefix $(BINDIR)/, $(SRCS:.cpp=.o))
DEPENDS := $(addprefix $(BINDIR)/, $(SRCS:.cpp=.d))
INCLUDE		:= -I../../.doctest/doctest/ -I../../

## general rules ##

all : config $(NAME)

$(BINDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

config:
	@if [ -e .doctest ]; then\
		git submodule update --init --recursive;\
	fi

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJS)

clean: FORCE
	rm -f $(OBJS) $(DEPENDS)

fclean: clean
	rm -f $(NAME)

re: fclean all

FORCE:

-include $(BINDIR)/*.d
