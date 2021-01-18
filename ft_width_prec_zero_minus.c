/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_width_prec_zero_minus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:03:19 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/18 18:56:01 by ysoroko          ###   ########.fr       */
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
** FT_PROCESS_MINUS_FLAG
** w_str = recipient defined by width, inside we will insert p_str
** The position of the p_str in w_str is defined by the presence of
** the '-' flag in list
** If there is a '-' flag -> insert at the start
** Otherwise -> insert at the end
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
			w_str[j] = p_str[i];
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
	if (!(prec_str = ft_precision(str, list)))
		return (0);
	if (list->width && (list->width > (int)ft_strlen(prec_str)))
	{
		if (!(width_str = ft_width_and_zero_to_str(list)))
		{
			ft_free(&prec_str, 0, 0);
			return (0);
		}
	}
	ret = ft_minus_flag(width_str, prec_str, list);
	ft_free(&width_str, &prec_str, 0);
	return (ret);
}
