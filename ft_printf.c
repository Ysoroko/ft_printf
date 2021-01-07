/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:27:46 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/07 16:53:01 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** va_arg allows to extract the next parameter from a_list with the type
** va_copy copies the list of params to a temporary list to read it > once
*/

int			ft_printf(const char *str, ...)
{
	va_list	v_list;
	int		ret;

	if (!str)
		return (-1);
	va_start(v_list, str);
	if (!(ret = ft_analyze_first_printf_argument(str, &v_list)))
		ret = -1;
	va_end(v_list);
	return (ret);
}
