NAME			=	philo

PHILO_FOLDER	=	src
FILES			=	init.c \
					philo.c \
					process.c \
					utils.c

SRCS		=	$(addprefix $(PHILO_FOLDER)/, $(FILES))
OBJS		=	$(SRCS:.c=.o)

CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
INCLUDES	=	-I includes/
RM			=	rm -f

all:		$(NAME)

$(NAME):	$(OBJS) includes/philo.h
			$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS)
clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
