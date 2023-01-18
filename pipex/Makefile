SRCS			=	src/main.c src/pipe.c src/split.c src/error.c src/strncmp.c src/ft_strjoin.c
INCLUDES		= include/
OBJS			= $(SRCS:.c=.o)

CC				= gcc
RM				= rm -f
CFLAGS			= -Wall -Wextra -Werror -I.
NAME			= pipex


all: 
		gcc -Wall -Wextra -Werror  ${SRCS} -I ${INCLUDES} -o $(NAME)

clean:
				$(RM) $(OBJS)

fclean:			clean
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re bonus