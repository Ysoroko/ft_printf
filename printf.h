/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:08:21 by ysoroko           #+#    #+#             */
/*   Updated: 2020/12/29 13:11:31 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

#include <stdarg.h>

typedef struct	s_str_with_flags_list
{
	char							*minus_flag;
	char							*star_before_point;
	char							*zero_flag;
	char							*point_flag;
	int								precision_flag;
	int								width_flag;
	char							*star_after_point;
	char							type_flag;
	char							*text_to_print;
	char							*error;
	struct s_str_with_flags_list	*next;
}				t_list;

int		ft_printf(const char *str, ...);

#endif