NAME := ft_vector ft_stack ft_map ft_set std_stack std_vector std_map std_set 
CXX := clang++
CXXFLAGS := -Wall -Werror -Wextra -std=c++98 
FT_SRCS :=	timer.cpp \
		ft_vector.cpp
STD_SRCS :=	timer.cpp \
		std_vector.cpp
INCLUDE := -I ../../
BINDIR := bin
FT_OBJS := $(addprefix $(BINDIR)/, $(FT_SRCS:.cpp=.o))
STD_OBJS := $(addprefix $(BINDIR)/, $(STD_SRCS:.cpp=.o))
DEPENDS := $(addprefix $(BINDIR)/, $(SRCS:.cpp=.d))

## general rules ##

all : $(BINDIR) $(NAME)

ft_%: $(BINDIR)/ft_%.o $(BINDIR)/timer.o
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^ -o  $@

std_%: $(BINDIR)/std_%.o $(BINDIR)/timer.o
	$(CXX) $(CXXFLAGS) $(INCLUDE) $^ -o $@

$(BINDIR)/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(BINDIR):
	mkdir -p $@

leak: CXXFLAGS+= -fsanitize=address
leak: re

clean: FORCE
	@rm -f bin/*.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY:	FORCE
FORCE:
