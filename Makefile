# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/02 15:19:22 by ysoroko           #+#    #+#              #
#    Updated: 2021/01/15 15:03:14 by ysoroko          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC				=	gcc

CFLAGS			=	-Wall -Wextra -Werror

SRC				=	ft_printf.c \
					ft_printf_first_arg_utils.c \
					ft_flags_processing.c \
					\
					./error_checking_functions/ft_check_special_combo.c \
					\
					./libft_utils/ft_itoa.c \
					./libft_utils/ft_libft_utils.c \
					./libft_utils/ft_strdup.c \
					./libft_utils/ft_strjoin.c \
					./libft_utils/ft_uitoa_base.c \
					./libft_utils/ft_ultoa_base.c \
					./libft_utils/ft_strcmp.c \
					./libft_utils/ft_count_n_digits.c \
					\
					./next_arg_to_str_functions/ft_csp_percent_flags.c \
					./next_arg_to_str_functions/ft_diux_flags.c \
					./next_arg_to_str_functions/ft_width_prec_zero_minus.c \
					\
					./printf_utils/ft_atoi_for_printf.c \
					./printf_utils/ft_printf_utils.c \


BONUS			=	ft_lstadd_back.c \

OBJS			=	ft_printf.o \
					ft_printf_first_arg_utils.o \
					ft_flags_processing.o \
					\
					ft_check_special_combo.o \
					\
					ft_itoa.o \
					ft_libft_utils.o \
					ft_strdup.o \
					ft_strjoin.o \
					ft_uitoa_base.o \
					ft_ultoa_base.o \
					ft_strcmp.o \
					ft_count_n_digits.o \
					\
					ft_csp_percent_flags.o \
					ft_diux_flags.o \
					ft_width_prec_zero_minus.o \
					\
					ft_atoi_for_printf.o \
					ft_printf_utils.o 

NAME			=	libftprintf.a

LINK			=	ar rc


.c.o:		
			@ ${CC} ${CFLAGS} -I includes -c $(SRC) $< ${<:.c=.o}

all: 		$(NAME)

$(NAME):	.c.o
			@ $(LINK) $(NAME) $(OBJS)

bonus:		$(OBJS)
			@ $(LINK) $(NAME) $(OBJS)

clean:
			@ rm -f $(OBJS)

fclean:		clean
			@ rm -f $(NAME)

aclean:		fclean 
			@ rm -f a.out test1.txt test2.txt main \

re:			fclean all

run:		
			@ $(CC) -I includes $(SRC) main.c && ./a.out

run2:		
			@ $(CC) -I includes $(SRC) main2.c && ./a.out

.PHONY:		all clean fclean re bonus run