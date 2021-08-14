NAME		=	philo_bonus

SRCS		= 	main.c \
				sources/ft_atoi_s.c \
				sources/main_proc.c \
				sources/parser.c \
				sources/time.c \
				sources/init.c \
				sources/philo_start.c \

OBJS		= 	${SRCS:.c=.o}

CC			= 	gcc

CFLAGS		= 	-Wall -Wextra -Werror

INCLUDES	= 	includes/philo_bonus.h

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
