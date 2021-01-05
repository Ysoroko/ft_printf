/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:13:15 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/05 18:14:35 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** cspdiuxX%
*/

char	*ft_next_arg_to_str(va_list *v_l, t_list *list)
{
	char *arg_as_str;

	arg_as_str = 0;
	if (list->type_flag == 'c')
		arg_as_str = ft_c_type_next_arg_to_str(v_l);
	else if (list->type_flag == '%')
		arg_as_str = ft_percent_type_next_arg_to_str();
	else if (list->type_flag == 's')
		arg_as_str = ft_s_type_next_arg_to_str(v_l);
	else if (list->type_flag == 'd' || list->type_flag == 'i')
		arg_as_str = ft_d_or_i_type_next_arg_to_str(v_l);
	else if (list->type_flag == 'u')
		arg_as_str = ft_u_type_next_arg_to_str(v_l);
	else if (list->type_flag == 'x')
		arg_as_str = ft_lowercase_x_type_next_arg_to_str(v_l);
	else if (list->type_flag == 'X')
		arg_as_str = ft_uppercase_x_type_next_arg_to_str(v_l);
	return (arg_as_str);
}

/*
** FT_PROCESS_LIST is the central hub of processing all the data from t_list
** It processes all the necessary info to create a string, used to print on the
** file descriptor
*/

int		ft_process_list(t_list *list, va_list *v_list)
{
	char	*str_to_print;

	if (ft_check_for_errors(list, v_list))
		return (0);
	if (list->star_before_point)
		list->width = va_arg(*v_list, unsigned int);
	if (list->star_after_point)
		list->precision = va_arg(*v_list, unsigned int);
	//str_to_print = ft_next_arg_to_str(v_list, list);
	if (list->type_flag == 's')
	{
		//printf("printing a string\n");
		str_to_print = va_arg(*v_list, char *);
		ft_putstr_fd(str_to_print, FD);
	}
	//Should return the length of %string, to increment string in the ft_printf function
	return (ft_strlen(list->definer_str) + 1);
}
