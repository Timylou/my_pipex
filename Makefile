NAME	=	pipex

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g

SRC		=	pipex.c exec.c path.c file.c utils.c ft_split.c
OBJ		=	$(SRC:.c=.o)

all		:	$(NAME)

$(NAME)	:	$(OBJ)
	$(CC) $^ -o $@ 

%.o		:	%.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean	:
	rm $(OBJ)

fclean	:	clean
	rm $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re
