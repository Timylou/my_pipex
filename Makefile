NAME	=	pipex

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g

SRC	=	pipex.c path.c file.c struct.c error.c utils.c ft_split.c
OBJ	=	$(SRC:.c=.o)

all		:	$(NAME)

bonus	:	CFLAGS += -DBONUS=1
bonus	:	$(NAME)

$(OBJ)	:	$(SRC)
	$(CC) $(CFLAGS) -c $^

$(NAME)	:	$(OBJ) $(COBJ)
	$(CC) $(CFLAGS) $^ -o $@ 

clean	:
	rm -f $(OBJ) $(BOBJ) $(COBJ)

fclean	:	clean
	rm -f $(NAME) $(BNAME)

re		:	fclean all

.PHONY	:	all clean fclean re bonus
