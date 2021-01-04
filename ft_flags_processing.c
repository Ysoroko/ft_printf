/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:13:15 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/04 15:38:30 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** FT_CHECK_FOR_MISTAKES
** Checks for incompatible flags present in t_list argument (+ if va_list = 0)
** Returns 1 in case of mistake found, 0 otherwise
*/

int	ft_check_for_mistakes(t_list *list, va_list *v_list)
{
	if (!list || !v_list)
		return (1);
	//'0' flag present +type specifier is 's', 'c' or 'p'
	if (list->zero_flag && (ft_strchr("scp", list->type_flag)))
		return (1);
	//'0' Flag before precision after '.' -> error
	if (ft_zero_before_n_in_str(list->after_point))
		return (1);
	//Precision flag's undefined behaviour with 'c' and 'p' flags
	if (list->precision_flag && (ft_strchr("cp", list->type_flag)))
		return (1);
	//All things that shouldn't be present in the string
	if (ft_str_has_other_chars(list->definer_str, ACCEPTED_CHARS))
		return (1);
	if (ft_str_has_other_chars(list->after_point, "0123456789*cspdiuxX%"))
		return (1);
	return (0);
}


/*
** FT_PROCESS_LIST is the central hub of processing all the data from t_list
** It processes all the necessary info to create a string, used to print on the
** file descriptor
*/

int	ft_process_list(t_list *list, va_list *v_list)
{
	char	*str_to_print;

	if (ft_check_for_mistakes(list, v_list))
	{
		printf("Error found in t_list\n");
		return (0);
	}
	//AND NO '*'!!!
	if (list->type_flag == 's')
	{
		printf("printing a string\n");
		str_to_print = va_arg(*v_list, char *);
		ft_putstr_fd(str_to_print, FD);
	}
	//Should return the length of %string, to increment string in the ft_printf function
	return (0);
}
