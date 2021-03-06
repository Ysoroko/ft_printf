/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_csp_percent_flags.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:57:40 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/18 09:53:49 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_C_TYPE_NEXT_ARG_TO_STR
** FT_PERCENT_TYPE_NEXT_ARG_TO_STR
** FT_S_TYPE_NEXT_ARG_TO_STR
** FT_P_TYPE_NEXT_ARG_TO_STR
** Each of the following functions will transform the next argument from va_list
** to a malloc'd string depending on the corresponding type
** Returns the address of the newly created string or 0 in case of error
*/

char	*ft_c_to_str(va_list *v_l)
{
	char	*ret_str;
	char	arg_as_char;
	char	zero;

	zero = 0;
	if (!(arg_as_char = (char)va_arg(*v_l, int)))
		return (ft_strdup(""));
	if (!(ret_str = ft_char_alloc(1, '0')))
		return (0);
	ret_str[0] = arg_as_char;
	return (ret_str);
}

char	*ft_percent_to_str(void)
{
	char *arg_as_str;

	arg_as_str = 0;
	if (!(arg_as_str = ft_char_alloc(1, '%')))
		return (0);
	return (arg_as_str);
}

char	*ft_s_to_str(va_list *v_l, t_list *list)
{
	char *arg_as_str;

	arg_as_str = va_arg(*v_l, char *);
	if (!list->precision && list->after_dot)
		return (ft_strdup(""));
	if (!(arg_as_str))
		return (ft_strdup("(null)"));
	return (ft_strdup(arg_as_str));
}

char	*ft_p_to_str(va_list *v_l, t_list *list)
{
	void			*address;
	unsigned long	address_to_ulong;
	char			*arg_as_str;
	char			*temp;

	arg_as_str = 0;
	address = va_arg(*v_l, void *);
	address_to_ulong = (unsigned long)address;
	if (!address && !list->precision && list->after_dot)
		return (ft_strdup("0x"));
	if (!(temp = ft_ultoa_base(address_to_ulong, BASE_LX)))
		return (0);
	arg_as_str = ft_strjoin("0x", temp);
	ft_free(&temp, 0, 0);
	return (arg_as_str);
}
