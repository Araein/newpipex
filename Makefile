NAME 			= pipex

SRCS_LIST		= main.c pipex.c split.c utils.c 

FOLDER			= srcs

SRCS			= $(addprefix ${FOLDER}/, ${SRCS_LIST})

OBJS			= ${SRCS:.c=.o}

HEADER			= header

CC				= gcc 
CFLAGS 			= -Wall -Wextra -Werror
RM				= rm -f

%.o: %.c
				 @${CC}  ${CFLAGS} -I ${HEADER} -o $@ -c $< 

all:			${NAME}

$(NAME):		${OBJS}
				gcc -fsanitize=address -g3 -o ${NAME} ${OBJS}
clean:
				@${RM} ${OBJS} ${OUT}

fclean:			clean
				@${RM} ${NAME}

re:				fclean all

.PHONY: 		all fclean clean re

# -fsanitize=address -g3