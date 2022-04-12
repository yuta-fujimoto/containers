FT_NAME := ft
STD_NAME := std
CXX := clang++
CXXFLAGS := -Wall -Werror -Wextra -MMD -MP -std=c++98
FT_SRCS :=	timer.cpp \
		ft_vector.cpp
STD_SRCS :=	timer.cpp \
		std_vector.cpp
BINDIR := bin
FT_OBJS := $(addprefix $(BINDIR)/, $(FT_SRCS:.cpp=.o))
STD_OBJS := $(addprefix $(BINDIR)/, $(STD_SRCS:.cpp=.o))
DEPENDS := $(addprefix $(BINDIR)/, $(SRCS:.cpp=.d))

## general rules ##

all :$(FT_NAME) $(STD_NAME)

$(FT_NAME): $(FT_OBJS)
	@$(CXX) $(CXXFLAGS) -o $(FT_NAME) $(FT_OBJS)

$(STD_NAME): $(STD_OBJS)
	@$(CXX) $(CXXFLAGS) -o $(STD_NAME) $(STD_OBJS)
	
$(BINDIR)/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -o $@ -c $<

$(BINDIR):
	mkir -p $@

leak: CXXFLAGS+= -fsanitize=address
leak: re

clean: FORCE
	@rm -f $(FT_OBJS) $(STD_OBJS) $(DEPENDS)

fclean: clean
	@rm -f $(FT_NAME) $(STD_NAME)

re: fclean all

.PHONY:	FORCE
FORCE:
