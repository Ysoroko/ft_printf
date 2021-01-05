/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 16:52:44 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/05 12:56:29 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** FT_WRONG_ORDER_OF_FLAGS
** Checks if before the '.' the order |[%]["0*-" flags][width][.]| is respected
** Then, if there is a '.' and after_dot exists, checks the part after the '.'
** to see if the order ["0*" flags][precision][type definer char] is respected
**
** 
*/

"%04-20."

int	ft_wrong_order_of_flags(char *before_dot, char *after_dot)
{
	int i;

	i = ft_strlen(before_dot);
	if (--i != '.' && !(ft_strchr(TYPE_CHARS, before_dot[i])))
		return (1);
	if (--i != '.' && !ft_isdigit(before_dot[i]) && !ft_strchr("0*-.", before_dot[i]))
		return (1);
	while(ft_isdigit(before_dot[i]))
		i--;
	while (i && ft_strchr("0*-.", before_dot[i]))
		i--;
	if ((before_dot[i] != 0) && !ft_isdigit(before_dot[i]) && !ft_strchr(TYPE_CHARS, before_dot[i]))
		return (1);
	while (before_dot[i] && ft_isdigit(before_dot[i]))
		i++;
	if (((before_dot[i] != 0) && (before_dot[i] != '.')))
		return (1);
	if (after_dot != 0)
	{
		while (after_dot[i = 0] && ft_strchr("0*", after_dot[i]))
			i++;
		if ((after_dot[i] != 0) && !ft_isdigit(after_dot[i]))
			return (1);
		while (after_dot[i] && ft_isdigit(after_dot[i]))
			i++;
		if (!ft_strchr(TYPE_CHARS, after_dot[i]))
			return (1);
		if (after_dot[++i] != 0)
			return (1);
	}
	return (0);
}
