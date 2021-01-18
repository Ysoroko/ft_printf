# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/02 15:19:22 by ysoroko           #+#    #+#              #
#    Updated: 2021/01/18 11:09:14 by ysoroko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

SRC				=	ft_printf.c \
					ft_analyze_first_arg.c \
					ft_flags_processing.c \
					\
					ft_itoa.c \
					ft_libft_utils.c \
					ft_libft_utils2.c \
					ft_uitoa_base.c \
					ft_ultoa_base.c \
					\
					ft_csp_percent_flags.c \
					ft_diux_flags.c \
					ft_width_prec_zero_minus.c \
					\
					ft_atoi_for_printf.c \
					ft_printf_utils.c \
					ft_precision.c


BONUS			=	ft_lstadd_back.c \

OBJS			=	$(SRC:.c=.o)

NAME			=	libftprintf.a

LINK			=	ar rc

all: 		$(NAME)

$(NAME):	$(OBJS)
			@ $(LINK) $(NAME) $(OBJS)

clean:
			@ rm -f $(OBJS)

fclean:		clean
			@ rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re