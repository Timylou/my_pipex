NAME	=	pipex

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g

SRC		=	pipex.c path.c file.c process.c utils.c ft_split.c
OBJ		=	$(SRC:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	$(CC) $^ -o $@ 

%.o		:	%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean	:
	rm -f $(OBJ)

fclean	:	clean
	rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
