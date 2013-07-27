NAME		= libini.a
SRC		= ini.cpp
OBJ		= $(SRC:.cpp=.o)
CXXFLAGS	= -W -Wall
CC		= g++
RM		= rm -rf

all		: $(NAME)

$(NAME)		: $(OBJ)
		  ar r $(NAME) $(OBJ)
	 	  ranlib $(NAME)

clean		:
		  $(RM) *~
		  $(RM) $(OBJ)

fclean		: clean
		  $(RM) $(NAME)

re		: fclean all