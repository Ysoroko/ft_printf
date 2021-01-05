/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_csp_percent_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:57:40 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/05 18:13:44 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** FT_C_TYPE_NEXT_ARG_TO_STR
** FT_PERCENT_TYPE_NEXT_ARG_TO_STR
** FT_S_TYPE_NEXT_ARG_TO_STR
** FT_P_TYPE_NEXT_ARG_TO_STR
**
** Each of the following functions will transform the next argument from va_list
** to a malloc'd string depending on the corresponding type
** Returns the address of the newly created string or 0 in case of error
*/

char	*ft_c_type_next_arg_to_str(va_list *v_l)
{
	char *arg_as_str;

	arg_as_str = 0;
	if (!(arg_as_str = ft_char_alloc(sizeof(char) * 2, '0')))
		return (0);
	arg_as_str[0] = (char)va_arg(*v_l, unsigned int);
	return (arg_as_str);
}

char	*ft_percent_type_next_arg_to_str(void)
{
	char *arg_as_str;

	arg_as_str = 0;
	if (!(arg_as_str = ft_char_alloc(sizeof(char) * 2, '%')))
		return (0);
	return (arg_as_str);
}

char	*ft_s_type_next_arg_to_str(va_list *v_l)
{
	char *arg_as_str;

	arg_as_str = 0;
	if (!(arg_as_str = ft_strdup(va_arg(*v_l, char *))))
		return (0);
	return (arg_as_str);
}
