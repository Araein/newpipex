NAME 			= pipex

SRCS_LIST		= main.c pipex.c split.c utils.c 

FOLDER			= srcs

SRCS			= $(addprefix ${FOLDER}/, ${SRCS_LIST})

OBJS			= ${SRCS:.c=.o}

HEADER			= header

CC				= gcc 
CFLAGS 			= -Wall -Wextra -Werror
RM				= rm -f

all:			${NAME}

$(NAME):		${OBJS}
				gcc -o ${NAME} ${OBJS}

%.o: %.c
				@${CC} ${CFLAGS} -I ${HEADER} -o $@ -c $<

clean:
				@${RM} ${OBJS} ${OUT}

fclean:			clean
				@${RM} ${NAME}

re:				fclean all

.PHONY: 		all fclean clean re