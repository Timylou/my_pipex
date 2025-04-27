NAME	=	pipex

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g

SRC	=	pipex.c path.c file.c struct.c error.c utils.c ft_split.c here_doc.c smart_split.c remove_quotes.c
OBJ	=	$(SRC:.c=.o)

all		:	$(NAME)

bonus	:	CFLAGS += -DBONUS=1
bonus	:	$(NAME)

$(OBJ)	:	$(SRC)
	$(CC) $(CFLAGS) -c $^

$(NAME)	:	$(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ 

clean	:
	rm -f $(OBJ)

fclean	:	clean
	rm -f $(NAME)

re		:	fclean all

.PHONY	:	all clean fclean re bonus
