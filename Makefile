# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/02 15:19:22 by ysoroko           #+#    #+#              #
#    Updated: 2021/01/05 15:33:24 by ysoroko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

SRC				=	ft_printf.c \
					ft_printf_first_arg_utils.c \
					ft_t_list_utils.c \
					ft_libft_utils.c \
					ft_flags_processing.c \
					ft_atoi_for_printf.c \
					ft_printf_utils.c \
					ft_printf_utils2.c

BONUS			=	ft_lstadd_back.c \

OBJS			=	$(SRC:.c=.o) \

NAME			=	libftprintf.a

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

run:		
			$(CC) $(CFLAGS) *.c && ./a.out

.PHONY:		all clean fclean re bonus run