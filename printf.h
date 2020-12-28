/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:08:21 by ysoroko           #+#    #+#             */
/*   Updated: 2020/12/28 15:15:12 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

#include <stdarg.h>

typedef struct	s_str_with_flags_list
{
	int								minus_flag;
	int								int_before_point;
	int								star_before_point;
	int								zero_flag;
	int								point_flag;
	int								int_after_point;
	int								star_after_point;
	char							type_flag;
	char							*text_to_print;
	struct s_str_with_flags_list	*next;
}				t_str_flags;

int		ft_printf(const char *str, ...);
void	c_flag(char c);
void	s_flag(char *str);
void	p_flag(void *ptr);
void	d_i_flag(int n);
void	u_flag(unsigned int n);
void	x_flag(unsigned int n, char x);
void	percent_flag(void);

#endif