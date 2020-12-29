/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:27:46 by ysoroko           #+#    #+#             */
/*   Updated: 2020/12/29 14:30:02 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** va_arg allows to extract the next parameter from a_list with the type
** va_copy copies the list of params to a temporary list to read it > once
*/
int			ft_printf(const char *str, ...)
{
	va_list	a_list;
	va_list	a_list_copy;
	char	*type;
	int		param_number;
	int		i;

	if (str == 0)
		return (0);
	i = 0;
	param_number = count_expected_params_number(str);
	va_start(a_list, str);

	va_copy(a_list_copy, a_list);

	va_end(a_list);

}