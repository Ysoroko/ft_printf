/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:27:46 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/11 11:10:09 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** va_arg allows to extract the next parameter from a_list with the type
** va_copy copies the list of params to a temporary list to read it > once
*/

int	ft_printf(const char *str, ...)
{
	va_list	v_list;
	int		ret;

	if (!str)
		return (-1);
	va_start(v_list, str);
	if (!(ret = ft_analyze_first_printf_argument(str, &v_list)))
		ret = -1;
	va_end(v_list);
	return (ret);
}

//TO DELETE
void	ft_print_t_list(t_list *list)
{
	printf("\nCONTENTS OF T_LIST\n\n");
	printf("DEFINER_STR: %s\n\n", list->definer_str);
	printf("Before dot: %s\n", list->before_dot);
	printf("After dot: %s\n", list->after_dot);
	printf("Minus flag: %s\n", list->minus_flag);
	printf("Star before point: %s\n", list->star_before_point);
	printf("Zero flag: %d\n", list->zero_flag);
	printf("Point flag: %s\n", list->point_flag);
	printf("Width: %d\n", list->width);
	printf("Precision: %d\n", list->precision);
	printf("Star after point: %s\n", list->star_after_point);
	printf("Type flag: %c\n", list->type_flag);
	printf("Text_to_print: %s\n\n", list->text_to_print);
}