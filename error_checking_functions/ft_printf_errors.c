/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_errors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 15:52:26 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/09 19:19:49 by ysoroko          ###   ########.fr       */
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
** 1) '0' flag present + type specifier is 's', 'c' or 'p'
** 2) Precision flag's undefined behaviour with 'c' and 'p' flags
** 3) All chars that shouldn't be present in the definer string
** 4) All chars that shouldn't be present in the string after the '.'
** 5) Too many '.' ot '*' flags
** 6) There are both a width in numbers and a '*' flag before the "."
** 7) There are both a precision in numbers and a '*' flag after the "."
** Returns corresponding int in case of mistake found, 0 otherwise
*/

int	ft_check_for_errors(t_list *list, va_list *v_list)
{
	if (!list || !v_list)
		return (-1);
	if (list->zero_flag && (ft_strchr("scp", list->type_flag)))
		return (1);
	if (list->precision && (ft_strchr("cp", list->type_flag)))
		return (2);
	if (ft_str_has_other_chars(list->definer_str, ACCEPTED_CHARS))
		return (3);
	if (ft_str_has_other_chars(list->after_dot, "0123456789*cspdiuxX%"))
		return (4);
	if (ft_too_many_flag_chars_in_str(list->definer_str,
			list->before_dot, list->after_dot))
		return (5);
	if (list->width && list->star_before_point)
		return (6);
	if (list->precision && list->star_after_point)
		return (7);
	return (0);
}

/*
** FT_CHECK_FLAGS_FOR_SPECIAL_COMBO
** This function checks for special flags combinations
** and the priorities between the flags
** | Special combinations |
** a) Both '0' and '-' flags present -> '0' flag ignored
** b) Type 'pdiuxX', trying to print "0", precision = 0 -> prints ""
** c) The string to print is a null pointer -> only print (null), flags ignored
** | Return values |
** 0: After sorting out all the priorities
** 1: "s" type, but the string pointer was a null pointer
** 2: A 's' type with no precision but a '.' present in definer string
*/

int	ft_check_flags_for_special_combo(t_list *list)
{
	int	temp;

	if (!list->precision && list->after_dot && list->type_flag == 's')
	{
		temp = list->width + 1;
		while (--temp)
			ft_putchar_fd(' ', FD);
		return (2);
	}
	if (list->precision && list->type_flag == 's' &&
		list->precision >= ft_strlen(list->text_to_print))
		list->precision = 0;
	if (list->zero_flag && (list->minus_flag || (list->after_dot &&
		ft_strchr("diuxX", list->type_flag))))
		list->zero_flag = 0;
	if ((list->precision && list->width && list->precision >= list->width)
		|| (list->width && list->width <= ft_strlen(list->text_to_print)))
		list->width = 0;
	if (list->precision && list->type_flag != 's' &&
		list->precision <= ft_strlen(list->text_to_print))
		list->precision = 0;
	if (!ft_strcmp(list->text_to_print, "(null)"))
	{
		ft_putstr_fd(list->text_to_print, FD);
		return (1);
	}
	if (ft_strchr("diuxX", list->type_flag) && list->after_dot &&
		!list->precision && !ft_strcmp("0", list->text_to_print))
	{
		ft_putstr_fd("", FD);
		return (3);
	}
	return (0);
}
