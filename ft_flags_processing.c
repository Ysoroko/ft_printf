/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:13:15 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/05 14:59:47 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** FT_CHECK_FOR_ERRORS
** Checks for error cases present in t_list argument (+ if t_list/va_list = 0)
** 1) '0' flag present + type specifier is 's', 'c' or 'p'
** 2) '0' and '-' flags present together
** 3) Precision flag's undefined behaviour with 'c' and 'p' flags
** 4) All chars that shouldn't be present in the definer string
** 5) All chars that shouldn't be present in the string after the '.'
** 6) Too many '.' ot '*' flags
** 7) Wrong order of accepted chars
** 8) There are both a width in numbers and a '*' flag before the "."
** 9) There are both a precision in numbers and a '*' flag after the "."
** Returns 1 in case of mistake found, 0 otherwise
*/

int	ft_check_for_errors(t_list *list, va_list *v_list)
{
	if (!list || !v_list)
		return (-1);
	if (list->zero_flag && (ft_strchr("scp", list->type_flag)))
		return (1);
	//printf("1) '0' flag present + type specifier is 's', 'c' or 'p' done \n\n");
	if (list->zero_flag && list->minus_flag)
		return (2);
	if (list->precision && (ft_strchr("cp", list->type_flag)))
		return (3);
	//printf("3) Precision flag's undefined behaviour with 'c' and 'p' flags done \n\n");
	if (ft_str_has_other_chars(list->definer_str, ACCEPTED_CHARS))
		return (4);
	//printf("4) Forbidden chars in definer string \n\n");
	if (ft_str_has_other_chars(list->after_dot, "0123456789*cspdiuxX%"))
		return (5);
	//printf("5) Forbidden chars in the string after the '.' done \n\n");
	if (ft_too_many_flag_chars_in_str(list->definer_str,
			list->before_dot, list->after_dot))
		return (6);
	//printf("6) Too many '.' ot '*' flags done \n\n");
	if (ft_wrong_order_of_flags(list->before_dot, list->after_dot))
		return (7);
	//printf("7) Wrong order of accepted chars done \n\n");
	if (list->width && list->star_before_point)
		return (8);
	//printf("8) There are both a width in numbers and a '*' flag before the '.' done \n\n");
	if (list->precision && list->star_after_point)
		return (9);
	//printf("9) There are both a precision in numbers and a '*' flag after the '.' done \n\n");
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

	if (ft_check_for_errors(list, v_list))
		return (0);
	if (list->star_before_point)
		list->width = va_arg(*v_list, unsigned int);
	if (list->star_after_point)
		list->precision = va_arg(*v_list, unsigned int);
	printf("WIDTH: %d\n", list->width);
	if (list->type_flag == 's')
	{
		//printf("printing a string\n");
		str_to_print = va_arg(*v_list, char *);
		ft_putstr_fd(str_to_print, FD);
	}
	//Should return the length of %string, to increment string in the ft_printf function
	return (ft_strlen(list->definer_str) + 1);
}




/*
** "Width":		Specifies how many spaces are needed for the printed string. (= number before the '.' flag)
**				- By default, the character is formatted to the right (Ex: printf("%5s\n", "ha") --> "   ha")
**				- If the width is too little to print the string, it's ignored ("Ex: printf("%2s\n", "haha"); --> "haha")
**				- Works with all the formats "cspdiuxX% "
**				- Several widths separated by other flags --> error
**
**
** "Precision":	Specifies the precision for the numbers (= number after '.' if it's present)
**				- Undefined behaviour with: "%cp"
**				- With "%s" string format specifier, sets the number of chars from the string that will be printed
				  (Ex: printf("%4.2s\n", "ahah") --> "  ah")
**				- With "%diUxX" format specifiers, it sets the number of chars in the output string
**				  Unlike with "%s", it will always print at least the number itself, even if the precision is too little
**				  If the precision is bigger than the space needed to print the number, it will fill the rest of it (left) with '0'.
**				- In combination with WIDTH: 
**					1) The precision sort of "callocs" a string with "precision" number of '0'. It then writes inside the number
**					2) The width sort of "mallocs" a string with "width" number of spaces in it.It then writes the string from 1) inside
**				- If there is a '.', but no number afterwards --> no effect
**				- If a precision of 0 is used with a '0' in diUxX -> prints nothing
*/