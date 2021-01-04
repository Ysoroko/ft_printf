# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/02 15:19:22 by ysoroko           #+#    #+#              #
#    Updated: 2021/01/04 13:18:45 by ysoroko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

SRC				=	ft_printf.c \
					ft_printf_first_arg_utils.c \
					ft_t_list_utils.c \
					ft_flags_processing.c \
					ft_atoi_for_printf.c 

BONUS			=	ft_lstadd_back.c \

OBJS			=	$(SRC:.c=.o) \
					./libft/ft_strchr.o \
					./libft/ft_isdigit.o \
					./libft/ft_strlen.o \
					./libft/ft_putchar_fd.o \
					./libft/ft_putstr_fd.o

NAME			=	libftprintf.a

LINK			=	ar rc


all: 		$(NAME)

lib:		
			make -C ./libft

$(NAME):	lib $(OBJS) 
			$(LINK) $(NAME) $(OBJS)

bonus:		$(OBJS)
			$(LINK) $(NAME) $(OBJS)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

run:		
			gcc -Wall -Wextra -Werror libftprintf.a main.c ./libft/libft.a && ./a.out

.PHONY:		all clean fclean re bonus run