/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:52:44 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/05 14:12:20 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** FT_WRONG_ORDER_OF_FLAGS
** Checks if before the '.' the order |[%]["0*-" flags][width][.]| is respected
** Then, if there is a '.' and after_dot exists, checks the part after the '.'
** to see if the order ["0*" flags][precision][type definer char] is respected
*/

int	ft_wrong_order_of_flags(char *before_dot, char *after_dot)
{
	int i;

	i = ft_strlen(before_dot) - 1;
	if (i != '.' && !ft_strchr(TYPE_CHARS, before_dot[i]))
		return (2);
	if (i)
	{
		if (!ft_isdigit(before_dot[--i]) && !(ft_strchr("-0*", before_dot[i])))
			return (3);
		while (i && ft_isdigit(before_dot[i]))
			i--;
		if (!ft_strchr("0*-.", before_dot[i]))
			return (4);
		while (i && ft_strchr("0*-.", before_dot[i]))
			i--;
		if (i)
			return (5);
	}
	if (after_dot)
	{
		i = ft_strlen(after_dot);
		if (!(ft_strchr(TYPE_CHARS, after_dot[--i])))
			return (6);
		if (i)
		{
			if (!ft_isdigit(before_dot[--i]) && !ft_strchr("0*", after_dot[i]))
				return (7);
			while (i && ft_isdigit(after_dot[i]))
				i--;
			if (!ft_strchr("0*", after_dot[i]))
				return (8);
			while (i && ft_strchr("0*", before_dot[i]))
				i--;
			if (i)
				return (9);
		}
	}
	return (0);
}
