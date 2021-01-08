/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:13:15 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/08 17:18:12 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** FT_NEXT_ARG_TO_STR
** Checks the flag type stored in list and depending on the type, sends
** va_list and t_list to the corresponding function, which extracts the next
** argument of printf and converts it to a string
** Returns the resulting string
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
	else if (list->type_flag == 'p')
		arg_as_str = ft_p_type_next_arg_to_str(v_l);
	else if (list->type_flag == 'd' || list->type_flag == 'i')
		arg_as_str = ft_d_or_i_type_next_arg_to_str(v_l, list);
	else if (list->type_flag == 'u')
		arg_as_str = ft_u_type_next_arg_to_str(v_l);
	else if (list->type_flag == 'x')
		arg_as_str = ft_lowercase_x_type_next_arg_to_str(v_l);
	else if (list->type_flag == 'X')
		arg_as_str = ft_uppercase_x_type_next_arg_to_str(v_l);
	return (arg_as_str);
}

/*
** FT_STARS_FLAGS_PROCESS
** This function processes the star_before_point and
** star_after_point flags, setting the width and the precision to the
** corresponding values
** If the corresponding va_arg is negative, '-' flag is activated
*/

void	ft_stars_flags_process(t_list *list, va_list *v_list)
{
	if (list->star_before_point)
	{
		list->width = va_arg(*v_list, int);
		if (list->width < 0)
		{
			list->width *= -1;
			list->minus_flag = list->definer_str;
		}
		//printf("W:%u\n", list->width);
	}
	if (list->star_after_point)
	{
		list->precision = va_arg(*v_list, int);
		if (list->precision < 0)
		{
			list->precision = 0;
			list->minus_flag = list->definer_str;
		}
	}
}

/*
** FT_PROCESS_LIST is the central hub of processing all the data from t_list
** It processes all the necessary info to create a string, used to print on the
** file descriptor
*/

int		ft_process_list(t_list *list, va_list *v_list)
{
	char	*str_to_print;
	char	*str_after_w_p_z_m;

	//ft_print_t_list(list);
	if (ft_check_for_errors(list, v_list))
	{
		printf ("Error found in t_list\n");
		return (0);
	}
	ft_stars_flags_process(list, v_list);
	if (!(str_to_print = ft_next_arg_to_str(v_list, list)))
	{
		printf ("ft_next_arg_to_str = 0\n");
		return (0);
	}
	//printf("STR_TO_PRINT: %s\n", str_to_print);
	list->text_to_print = str_to_print;
	ft_check_flags_for_special_combo(list);
	if (!ft_strcmp(str_to_print, "(null)"))
	{
		ft_putstr_fd(str_to_print, FD);
		ft_free(str_to_print, 0, 0);
		return (ft_strlen(list->definer_str) + 1);
	}
	//printf("S before w/p/0/-: %s\n", str_to_print);
	if (!(str_after_w_p_z_m = ft_width_prec_zero_minus(str_to_print, list)))
	{
		printf("ft_width_prec_zero_minus = 0\n");
		return (ft_free(str_to_print, 0, 0));
	}
	//printf("S after w/p/0/-: %s\n", str_after_w_p_z_m);
	ft_putstr_fd(str_after_w_p_z_m, FD);
	//THIS ONE IS CONSIDERED AS FREEING UNALLOCATED MEM ft_free(str_to_print, 0, 0);
	return (ft_strlen(list->definer_str) + 1);
}
