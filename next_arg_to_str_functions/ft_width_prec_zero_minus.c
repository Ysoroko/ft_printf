/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width_prec_zero_minus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:03:19 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/07 12:08:16 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** FT_PROCESS_MINUS_FLAG
** str_rec = recipient defined by width, inside we will insert str_to_insert
** the position of the str_to_insert in str_rec is defined by the presence of
** the '-' flag in list
** If there is a '-' flag -> insert at the start
** Otherwise -> insert at the end
**
** If there is no width, there should be no str_rec
** Returns the result of the insertion of str_to_insert inside str_rec
** Returns str_to_insert if there is no width/str_rec is a null pointer
*/

char	*ft_process_minus_flag(char *str_rec, char *str_to_insert, t_list *list)
{
	int i;
	int j;

	if (!(list->width) || !str_rec)
		return (str_to_insert);
	if (list->minus_flag && !(list->precision))
	{
		i = -1;
		while (str_to_insert[++i] && str_rec[i])
			str_rec[i] = str_to_insert[i];
	}
	else
	{
		i = ft_strlen(str_to_insert) + 1;
		j = ft_strlen(str_rec) + 1;
		while (--i && --j)
			str_rec[j] = str_to_insert[i];
	}
	return (str_rec);
}

/*
** FT_WIDTH_AND_ZERO_IN_STR
** takes the str_to_insert and checks the width from list
** if width is bigger than str_to_insert length, malloc's
** a new string of [width] length, fills it in with either
** '0' or ' ' depending on the '0' flag
** Returns the newly created string or 0 if width is too small
** or in case the malloc fails
*/

char	*ft_width_and_zero_to_str(char *str_to_insert, t_list *list)
{
	char	fill_in_char;

	if (list->width <= (int)ft_strlen(str_to_insert))
		return (0);
	if (list->zero_flag && !(list->minus_flag) && !(list->precision))
		fill_in_char = '0';
	else
		fill_in_char = ' ';
	return (ft_char_alloc(list->width, fill_in_char));
}

char	*ft_precision_to_str(char *str_to_format, t_list *list)
{
	char	*ret_str;
	int		str_to_format_len;
	int		i;
	int		j;
	int		precision;

	precision = list->precision;
	str_to_format_len = (int)ft_strlen(str_to_format);
	if (list->type_flag == 's')
	{
		if (precision >= str_to_format_len)
			return (0);
		else
		{
			ret_str = ft_char_alloc(precision, ' ');
			i = -1;
			while (ret_str[++i])
				ret_str[i] = str_to_format[i];
		}
	}
	else
	{
		if (list->precision <= str_to_format_len)
			return (0);
		else
		{
			if (!(ret_str = ft_char_alloc(precision, '0')))
				return (0);
			i = str_to_format_len + 1;
			j = (int)(ft_strlen(ret_str) + 1);
			while (--i && --j)
				ret_str[j] = str_to_format[i];
		}
	}
	return (ret_str);
}
