/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width_prec_zero_minus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:03:19 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/07 16:11:19 by ysoroko          ###   ########.fr       */
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

char	*ft_process_minus_flag(char *width_str, char *prec_str, t_list *list)
{
	int		i;
	int		j;
	char	*str;

	if (!width_str || (list->precision >= ft_strlen(width_str)))
		return (prec_str);
	str = list->text_to_print;
	if (!prec_str)
		prec_str = str;
	if (list->minus_flag)
	{
		i = -1;
		while (prec_str[++i] && width_str[i])
			width_str[i] = prec_str[i];
	}
	else
	{
		i = ft_strlen(prec_str) + 1;
		j = ft_strlen(width_str) + 1;
		while (--i > -1 && --j > -1)
			width_str[j] = prec_str[i];
	}
	return (width_str);
}

/*
** FT_WIDTH_AND_ZERO_IN_STR
** Analyzes the width and the '0' flag
** Mallocs a string filled with ' ' (or '0') chars
** depending on whether '0' flag is present and not overriden
** by '-' flag or precision
** Returns the newly created string or 0 if malloc fails
*/

char	*ft_width_and_zero_to_str(t_list *list)
{
	char	fill_in_char;

	if (list->width <= ft_strlen(list->text_to_print))
		return (list->text_to_print);
	if (list->zero_flag && !(list->minus_flag) && !(list->precision))
		fill_in_char = '0';
	else
		fill_in_char = ' ';
	return (ft_char_alloc(list->width, fill_in_char));
}

/*
** FT_PRECISION_S_TYPE_TO_STR
** This function checks precision when the specified type is a string
** Mallocs a string of [precision] chars and copies first
** [precision] chars of str_to_format to it
** Returns the result or 0 malloc fails
*/

char	*ft_precision_s_type_to_str(char *str_to_format, t_list *list)
{
	char	*ret_str;
	int		i;

	if (!(ret_str = ft_char_alloc(list->precision, ' ')))
		return (0);
	i = -1;
	while (ret_str[++i] && str_to_format[i])
		ret_str[i] = str_to_format[i];
	printf("P to S result: %s\n", ret_str);
	return (ret_str);
}

/*
** FT_PRECISION_TO_STR
** This function checks precision when the specified type is not a string
** Mallocs a string of [precision] chars, fills it with '0'
** and copies str_to_format (at the end of it)
** Returns the result or 0 if malloc fails
*/

char	*ft_precision_to_str(char *str_to_format, t_list *list)
{
	char	*ret_str;
	int		i;
	int		j;

	ret_str = 0;
	if (!(ret_str = ft_char_alloc(list->precision, '0')))
		return (0);
	i = ft_strlen(str_to_format) + 1;
	j = ft_strlen(ret_str) + 1;
	while (--i >= 0 && --j >= 0)
		ret_str[j] = str_to_format[i];
	return (ret_str);
}

char	*ft_width_prec_zero_minus(char *str, t_list *list)
{
	char			*width_str;
	char			*prec_str;
	char			*ret;
	unsigned int	width;
	unsigned int	precision;

	width = list->width;
	precision = list->precision;
	ret = 0;
	width_str = 0;
	prec_str = 0;
	if (width)
	{
		if (!(width_str = ft_width_and_zero_to_str(list)))
			return (0);
	}
	//printf("W to S result: %s\n", width_str);
	if (precision && list->type_flag == 's' && precision < ft_strlen(str))
	{
		if (!(prec_str = ft_precision_s_type_to_str(str, list)))
			return (0);
	}
	else if (precision && list->type_flag != 's' && precision > ft_strlen(str))
		if (!(prec_str = ft_precision_to_str(str, list)))
			return (0);
	//printf("P to S result: %s\n", prec_str);
	if (!(ret = ft_process_minus_flag(width_str, prec_str, list)))
		return (0);
	//printf("- to S result: %s\n", ret);
	return (ret);
}

