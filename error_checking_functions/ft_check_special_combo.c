/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_special_combo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:39:49 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/11 11:09:33 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	if (list->precision && list->type_flag != 's' &&
		list->precision <= ft_strlen(list->text_to_print))
		list->precision = 0;
	if (list->zero_flag && (list->minus_flag || (list->after_dot &&
		ft_strchr("diuxX", list->type_flag))))
		list->zero_flag = 0;
	if ((list->precision && list->width && list->precision >= list->width)
		|| (list->width && list->width <= ft_strlen(list->text_to_print)))
		list->width = 0;
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
