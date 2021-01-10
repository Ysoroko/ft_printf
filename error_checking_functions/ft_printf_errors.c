/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:52:26 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/10 13:37:56 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** FT_TOO_MANY_FLAG_CHARS_IN_STR
** Checks for the number of occurences of '.' and '*' in the total string,
** the part before the dot, and the part after the dot
** Returns 1 if there is too many of those flags, 0 otherwise
*/

int	ft_too_many_flag_chars_in_str(char *all, char *bef, char *aft)
{
	if (ft_number_of_c_char_in_str(all, '.') > 1)
		return (1);
	if (ft_number_of_c_char_in_str(bef, '*') > 1)
		return (1);
	if (aft)
	{
		if (ft_number_of_c_char_in_str(aft, '*') > 1)
			return (1);
	}
	return (0);
}

/*
** FT_CHECK_FOR_ERRORS
** Checks for error cases present in t_list argument (+ if t_list/va_list = 0)
** 1) Precision flag's undefined behaviour with 'c' and 'p' flags
** 2) All chars that shouldn't be present in the definer string
** 3) All chars that shouldn't be present in the string after the '.'
** 4) Too many '.' ot '*' flags
** 5) There are both a width in numbers and a '*' flag before the "."
** 6) There are both a precision in numbers and a '*' flag after the "."
** Returns corresponding int in case of mistake found, 0 otherwise
*/

int	ft_check_for_errors(t_list *list, va_list *v_list)
{
	if (!list || !v_list)
		return (-1);
	if (list->precision && (ft_strchr("cp", list->type_flag)))
		return (1);
	if (ft_str_has_other_chars(list->definer_str, ACCEPTED_CHARS))
		return (2);
	if (ft_str_has_other_chars(list->after_dot, "0123456789*cspdiuxX%"))
		return (3);
	if (ft_too_many_flag_chars_in_str(list->definer_str,
			list->before_dot, list->after_dot))
		return (4);
	if (list->width && list->star_before_point)
		return (5);
	if (list->precision && list->star_after_point)
		return (6);
	return (0);
}
