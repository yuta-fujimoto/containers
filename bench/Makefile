NAME := ft_vector ft_stack std_stack std_vector 
CXX := clang++
CXXFLAGS := -Wall -Werror -Wextra -std=c++98
FT_SRCS :=	timer.cpp \
		ft_vector.cpp
STD_SRCS :=	timer.cpp \
		std_vector.cpp
BINDIR := bin
FT_OBJS := $(addprefix $(BINDIR)/, $(FT_SRCS:.cpp=.o))
STD_OBJS := $(addprefix $(BINDIR)/, $(STD_SRCS:.cpp=.o))
DEPENDS := $(addprefix $(BINDIR)/, $(SRCS:.cpp=.d))

## general rules ##

all : $(NAME)

ft_%: $(BINDIR)/ft_%.o $(BINDIR)/timer.o
	$(CXX) $(CXXFLAGS) $^ -o  $@

std_%: $(BINDIR)/std_%.o $(BINDIR)/timer.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(BINDIR)/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BINDIR):
	mkir -p $@

leak: CXXFLAGS+= -fsanitize=address
leak: re

clean: FORCE
	@rm -f bin/*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY:	FORCE
FORCE:
