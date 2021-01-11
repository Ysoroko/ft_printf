/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diux_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:09:35 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/11 11:10:09 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_D_IR_I_TYPE_NEXT_ARG_TO_STR
** FT_U_TYPE_NEXT_ARG_TO_STR
** FT_LOWERCASE_X_TYPE_NEXT_ARG_TO_STR
** FT_UPPERCASE_X_TYPE_NEXT_ARG_TO_STR
**
** Each of the following functions will transform the next argument from va_list
** to a malloc'd string depending on the corresponding type
** Returns the address of the newly created string or 0 in case of error
*/

char	*ft_d_or_i_type_next_arg_to_str(va_list *v_l)
{
	char	*arg_as_str;

	if (!(arg_as_str = ft_itoa(va_arg(*v_l, int))))
		return (0);
	return (arg_as_str);
}

char	*ft_u_type_next_arg_to_str(va_list *v_l)
{
	char *arg_as_str;

	arg_as_str = 0;
	if (!(arg_as_str = ft_uitoa_base(va_arg(*v_l, unsigned int), BASE_10)))
		return (0);
	return (arg_as_str);
}

char	*ft_lowercase_x_type_next_arg_to_str(va_list *v_l)
{
	char *arg_as_str;

	arg_as_str = 0;
	if (!(arg_as_str = ft_uitoa_base(va_arg(*v_l, unsigned int), BASE_LX)))
		return (0);
	return (arg_as_str);
}

char	*ft_uppercase_x_type_next_arg_to_str(va_list *v_l)
{
	char *arg_as_str;

	arg_as_str = 0;
	if (!(arg_as_str = ft_uitoa_base(va_arg(*v_l, unsigned int), BASE_UX)))
		return (0);
	return (arg_as_str);
}
