/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width_prec_zero_minus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:03:19 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/15 19:13:47 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_WIDTH_AND_ZERO_IN_STR
** Analyzes the width and the '0' flag
** Mallocs a string filled with ' ' (or '0') chars
** depending on whether the '0' flag is applied
** Returns the newly created string or 0 if malloc fails
*/

char	*ft_width_and_zero_to_str(t_list *list)
{
	char	fill_in_char;
	char	*ret_str;

	if (list->zero_flag)
		fill_in_char = '0';
	else
		fill_in_char = ' ';
	if (!(ret_str = ft_char_alloc(list->width, fill_in_char)))
		return (0);
	if (list->text_to_print[0] == 0 && list->type_flag == 'c' && list->width)
		ret_str[list->width - 1] = 0;
	if (ft_strchr(list->text_to_print, '-') && fill_in_char == '0')
		ret_str[0] = '-';
	return (ret_str);
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

	if (!list->precision || list->precision >= (int)ft_strlen(str_to_format))
		return (ft_strdup(str_to_format));
	if (!(ret_str = ft_char_alloc(list->precision, ' ')))
		return (0);
	i = 0;
	while (ret_str[i] && str_to_format[i])
	{
		ret_str[i] = str_to_format[i];
		i++;
	}
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
	int		precision;
	int		c_max;

	if (list->type_flag == 'd' || list->type_flag == 'i')
		c_max = ft_count_n_digits(str_to_format);
	else
		c_max = (int)ft_strlen(str_to_format);
	precision = list->precision;
	if (!precision || (list->precision &&
		list->precision <= c_max))
		return (ft_strdup(str_to_format));
	ret_str = 0;
	if (ft_strchr(str_to_format, '-'))
		precision++;
	if (!(ret_str = ft_char_alloc(precision, '0')))
		return (0);
	i = ft_strlen(str_to_format) + 1;
	j = ft_strlen(ret_str) + 1;
	while (--i >= 0 && --j >= 0)
		ret_str[j] = str_to_format[i];
	if (ft_strchr(str_to_format, '-'))
	{
		ret_str[ft_strlen(ret_str) - ft_strlen(str_to_format)] = '0';
		ret_str[0] = '-';
	}
	return (ret_str);
}

/*
** FT_PROCESS_MINUS_FLAG
** w_str = recipient defined by width, inside we will insert p_str
** The position of the p_str in w_str is defined by the presence of
** the '-' flag in list
** If there is a '-' flag -> insert at the start
** Otherwise -> insert at the end
**
** If there is no width a copy of p_str is returned
** Returns the result of the insertion of p_str inside w_str
*/

char	*ft_minus_flag(char *w_str, char *p_str, t_list *list)
{
	int		i;
	int		j;

	if (!w_str)
		return (ft_strdup(p_str));
	if (list->minus_flag)
	{
		i = -1;
		while (p_str[++i] && w_str[i])
			w_str[i] = p_str[i];
	}
	else
	{
		if (list->zero_flag && p_str[0] == '-')
			p_str[0] = '0';
		i = ft_strlen(p_str) + 1;
		j = ft_strlen(w_str) + 1;
		while (--i > -1 && --j > -1)
		{
			w_str[j] = p_str[i];
		}
		if (list->zero_flag && ft_strchr(list->text_to_print, '-'))
			w_str[0] = '-';
	}
	return (ft_strdup(w_str));
}

/*
** FT_WIDTH_PREC_ZERO_MINUS
** This is the function that takes the previously converted to
** string next ft_printf argument and applies "0-[width].[precision]"
** flags to it
** Returns the resulting string or 0 if a malloc fails somewhere
*/

char	*ft_width_prec_zero_minus(char *str, t_list *list)
{
	char			*width_str;
	char			*prec_str;
	char			*ret;

	ret = 0;
	width_str = 0;
	prec_str = 0;
	if (list->type_flag == 's')
		prec_str = ft_precision_s_type_to_str(str, list);
	else if (list->type_flag != 's')
		prec_str = ft_precision_to_str(str, list);
	if (!prec_str)
	{
		ft_free(&width_str, 0, 0);
		return (0);
	}
	if (list->width && (list->width > (int)ft_strlen(prec_str)))
	{
		if (!(width_str = ft_width_and_zero_to_str(list)))
			return (0);
	}
	ret = ft_minus_flag(width_str, prec_str, list);
	ft_free(&width_str, &prec_str, 0);
	return (ret);
}
