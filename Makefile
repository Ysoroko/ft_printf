# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/02 15:19:22 by ysoroko           #+#    #+#              #
#    Updated: 2021/01/02 15:48:47 by ysoroko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

SRC				=	ft_printf.c \
					ft_printf_first_arg_utils.c \
					ft_printf_t_list_utils.c \
					ft_printf_list_processing.c \
					main.c 

BONUS			=	ft_lstadd_back.c \

OBJS	=	$(SRC:.c=.o)

NAME			=	printflibft.a

LINK			=	ar rc

all: 		$(NAME)

$(NAME):	$(OBJS)
			$(LINK) $(NAME) $(OBJS)

bonus:		$(OBJS)
			$(LINK) $(NAME) $(OBJS)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

run:		$(NAME)
			./a.out

.PHONY:		all clean fclean re bonus run