/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:27:46 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/15 19:10:32 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_PRINTF
** This function is a copy of a well-known "printf" function
** It allows to print on the output and will return the number of characters
** printed or -1 if an error occurs
** This version applies "-0[1st*][width].[2nd *][precision]" flags and covers
** "cspdiuxX" type specifiers
*/

int	ft_printf(const char *str, ...)
{
	va_list	v_list;
	int		ret;

	if (!str)
		return (-1);
	if (!str[0])
		return (0);
	va_start(v_list, str);
	ret = ft_analyze_first_arg(str, &v_list);
	if (ret < 0)
		ret = -1;
	va_end(v_list);
	return (ret);
}
