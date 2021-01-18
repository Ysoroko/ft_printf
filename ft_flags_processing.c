/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:13:15 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/18 10:45:41 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_PRINT_RESULT
** This function prints the result of the ft_printf conversion on the output fd
** It also covers a special case where we're dealing with a '\0' char which
** must be printed (which will never be printed using ft_putstr function)
*/

static void	ft_print_result(char *s, t_list *list)
{
	int		chars_printed;
	char	z;

	z = 0;
	chars_printed = (int)ft_strlen(s);
	if (list->text_to_print[0] == 0 && list->type_flag == 'c'
		&& list->minus_flag)
	{
		write(1, &z, FD);
		chars_printed++;
	}
	ft_putstr_fd(s, FD);
	if (list->text_to_print[0] == 0 && list->type_flag == 'c'
		&& !list->minus_flag)
	{
		write(1, &z, FD);
		chars_printed++;
	}
	list->chars_printed = chars_printed;
}

/*
** FT_NEXT_ARG_TO_STR
** Checks the flag type stored in list and depending on the type, sends
** va_list and t_list to the corresponding function, which extracts the next
** argument of printf and converts it to a string
** Returns the resulting string (which can be NULL if a malloc fails inside)
*/

char		*ft_next_arg_to_str(va_list *v_l, t_list *list)
{
	char *arg_as_str;

	arg_as_str = 0;
	if (list->type_flag == 'c')
		arg_as_str = ft_c_to_str(v_l);
	else if (list->type_flag == '%')
		arg_as_str = ft_percent_to_str();
	else if (list->type_flag == 's')
		arg_as_str = ft_s_to_str(v_l, list);
	else if (list->type_flag == 'p')
		arg_as_str = ft_p_to_str(v_l, list);
	else if (list->type_flag == 'd' || list->type_flag == 'i')
		arg_as_str = ft_d_or_i_to_str(v_l, list);
	else if (list->type_flag == 'u')
		arg_as_str = ft_u_to_str(v_l, list);
	else if (list->type_flag == 'x')
		arg_as_str = ft_lowercase_x_to_str(v_l, list);
	else if (list->type_flag == 'X')
		arg_as_str = ft_uppercase_x_to_str(v_l, list);
	return (arg_as_str);
}

/*
** FT_STARS_FLAGS_PROCESS
** This function processes the star_before_point and
** star_after_point flags, setting the width and the precision to the
** corresponding values
** If the * width < 0, '-' flag is activated and abs(width) is used
** If the * precision < 0, it's as if the '.' flag is absent
** (the respective field in t_list is set to a NULL pointer)
*/

void		ft_stars_flags_process(t_list *list, va_list *v_list)
{
	if (list->star_before_point)
	{
		list->width = va_arg(*v_list, int);
		if (list->width < 0)
		{
			list->width *= -1;
			list->minus_flag = list->definer_str;
		}
	}
	if (list->star_after_point)
	{
		list->precision = va_arg(*v_list, int);
		if (list->precision < 0)
		{
			list->precision = 0;
			list->after_dot = 0;
		}
	}
}

/*
** FT_PROCESS_LIST is the central hub of processing all the data from t_list
** It processes all the necessary info to create a string, used to print on the
** file descriptor
** First, it applies the '*' flags if there are any
** Then, it checks if the '0' flag is present and whether it is ignored or not
** Afterwards, it extracts the next argument of printf as a string
** And finally, it applies '-/0/width/precision' flags to that string to give us
** the final string we will print
** Returns 0 in case of an error, 1 otherwise
*/

int			ft_process_list(t_list *list, va_list *v_list)
{
	char	*printf_arg_str;
	char	*str_after_w_p_z_m;

	ft_stars_flags_process(list, v_list);
	ft_check_if_zero_flag_is_ignored(list);
	if (!(printf_arg_str = ft_next_arg_to_str(v_list, list)))
		return (0);
	list->text_to_print = printf_arg_str;
	if (!(str_after_w_p_z_m = ft_width_prec_zero_minus(printf_arg_str, list)))
		return (ft_free(&printf_arg_str, 0, 0));
	ft_print_result(str_after_w_p_z_m, list);
	ft_free(&printf_arg_str, &str_after_w_p_z_m, 0);
	return (1);
}
