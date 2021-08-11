NAME		=	philo

SRCS		= 	main.c \
				sources/ft_atoi_s.c \
				sources/mainproc.c \
				sources/parser.c \
				sources/threads.c \
				sources/time.c \
				sources/checkphilo.c \

OBJS		= 	${SRCS:.c=.o}

CC			= 	gcc

CFLAGS		= 	-Wall -Wextra -Werror

INCLUDES	= 	includes/philosophers.h

RM			= 	rm -rf

all: 			$(NAME)

$(NAME): 		$(OBJS)
				${CC} ${CFLAGS} ${OBJS} -o ${NAME}

%.o : %.c 		${INCLUDES}
				${CC} ${CFLAGS} -c $< -I ${INCLUDES} -o ${<:.c=.o}

clean:
				${RM} $(OBJS)

fclean:			clean
				${RM} ${NAME}

re:				fclean all

.PHONY:			all clean fclean re
