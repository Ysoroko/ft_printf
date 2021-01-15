/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_diux_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 17:09:35 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/15 17:21:05 by ysoroko          ###   ########.fr       */
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

char	*ft_d_or_i_to_str(va_list *v_l, t_list *list)
{
	int		next_arg;
	char	*arg_as_str;

	next_arg = va_arg(*v_l, int);
	if (next_arg == 0 && list->after_dot && !list->precision)
		return (ft_strdup(""));
	if (!(arg_as_str = ft_itoa(next_arg)))
		return (0);
	return (arg_as_str);
}

char	*ft_u_to_str(va_list *v_l, t_list *list)
{
	unsigned int		next_arg;
	char				*arg_as_str;

	next_arg = va_arg(*v_l, unsigned int);
	if (next_arg == 0 && list->after_dot && !list->precision)
		return (ft_strdup(""));
	arg_as_str = 0;
	if (!(arg_as_str = ft_uitoa_base(next_arg, BASE_10)))
		return (0);
	return (arg_as_str);
}

char	*ft_lowercase_x_to_str(va_list *v_l, t_list *list)
{
	unsigned int		next_arg;
	char				*arg_as_str;

	next_arg = va_arg(*v_l, unsigned int);
	if (next_arg == 0 && list->after_dot && !list->precision)
		return (ft_strdup(""));
	arg_as_str = 0;
	if (!(arg_as_str = ft_uitoa_base(next_arg, BASE_LX)))
		return (0);
	return (arg_as_str);
}

char	*ft_uppercase_x_to_str(va_list *v_l, t_list *list)
{
	unsigned int		next_arg;
	char				*arg_as_str;

	next_arg = va_arg(*v_l, unsigned int);
	if (next_arg == 0 && list->after_dot && !list->precision)
		return (ft_strdup(""));
	arg_as_str = 0;
	if (!(arg_as_str = ft_uitoa_base(next_arg, BASE_UX)))
		return (0);
	return (arg_as_str);
}
