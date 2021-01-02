/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:27:46 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/02 15:38:09 by ysoroko          ###   ########.fr       */
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

	if (str == 0)
		return (0);
	va_start(v_list, str);

	ft_analyze_first_printf_argument(str, &v_list);

	va_end(v_list);
	return (0);
}
