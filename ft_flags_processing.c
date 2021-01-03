/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:13:15 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/03 16:29:06 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_check_for_mistakes(t_list *list, va_list *v_list)
{
	if (!list || !v_list)
		return (1);
	//'0' flag present +type specifier is 's', 'c' or 'p'
	if (list->zero_flag && (ft_strchr("scp", list->type_flag)))
		return (1);
	//Precision flag's undefined behaviour with 'c' and 'p' flags
	if (list->precision_flag && (ft_strchr("cp", list->type_flag)))
		return (1);
}


/*
** FT_PROCESS_LIST is the central hub of processing all the data from t_list
** It processes all the necessary info to create a string, used to print on the
** file descriptor
*/

int	ft_process_list(t_list *list, va_list *v_list)
{
	char	*str_to_print;

	if (ft_check_t_list_for_mistakes(list, v_list))
		return (0);

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
