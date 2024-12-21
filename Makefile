NAME	=	pipex
BNAME	=	pipex_bonus

CC		=	cc
CFLAGS	=	-Wall -Werror -Wextra -g

CSRC	=	path.c file.c process.c utils.c ft_split.c
COBJ	=	$(CSRC:.c=.o)

SRC		=	pipex.c
OBJ		=	$(SRC:.c=.o)

BSRC	=	pipex_bonus.c
BOBJ	=	$(BSRC:.c=.o)

all		:	$(NAME)

$(OBJ)	:	$(SRC)
	$(CC) $(CFLAGS) -c $^

$(BOBJ)	:	$(BSRC)
	$(CC) $(CFLAGS) -c $^

$(COBJ)	:	$(CSRC)
	$(CC) $(CFLAGS) -c $^

$(NAME)	:	$(OBJ) $(COBJ)
	$(CC) $^ -o $@ 

$(BNAME):	$(BOBJ) $(COBJ)
	$(CC) $^ -o $@

clean	:
	rm -f $(OBJ) $(BOBJ) $(COBJ)

fclean	:	clean
	rm -f $(NAME) $(BNAME)

re		:	fclean all

bonus	:	$(BNAME)

.PHONY	:	all clean fclean re bonus
