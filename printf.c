/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:27:46 by ysoroko           #+#    #+#             */
/*   Updated: 2020/12/28 10:10:29 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/* 
** Checks if the character c is one of the "cspdiuxX%" flags which printf handles
*/
static int is_a_flag_char(char c)
{
	if (strchr("cspdiuxX%", c) != 0)
		return (1);
	return (0);
}

/*
** Looks for the next "%" in the str and check what's written after it
** Returns the type in the form of a spring as expected in the va_arg macro
*/
static char	*next_argument_type(const char *str)
{
	int i;

	i = 0;
	while (str[i] && !is_a_flag_char(str[i]))
		i++;
	if (!is_a_flg_char(str[i]))
		return (0);
	if (str[i] == 'c')
		return ("char");
	if (str[i] == 's')
		return ("char *");
	if (str[i] == 'p')
		return ("*");
	if (str[i] == 'd' || str[i] == 'i')
		return ("int");
	if (str[i] == 'u')
		return ("unsigned int");
	if (str[i] == 'x' || str[i] == 'X')
		return ("unsigned *");
	if (str[i] == '%')
		return ("%");
}

/*
** This function takes into account the ". and width flags"
** Returns the number of chars needed to create the output string
*/
static int	space_for_printed_string(const char *str)
{
	int count;
	int i;

	count = 0;
	i = 0;
	while (str[i] != '%')
		count++;
	
}

/*
** Returns the expected parameters number based on the amount of "%" in the str
** This means that the str itself isn't counted in the return value
*/
static int	count_exepcted_params_number(const char *str)
{
	int	i;
	int	count;
	int	str_len;

	if (str == 0)
		return (0);
	i = 0;
	count = 0;
	str_len = ft_strlen(str);
	while (str[i] != '\0')
	{
		if (i < str_len - 1)
		{
			if(str[i] == '%' && str[i+1]!= '%')
				count++;
		}
		else
		{
			if(str[i] == '%' && str[i - 1] != '%')
				return (0);
		}
		
		
	}
	return (count);
}

/*
** va_arg allows to extract the next parameter from a_list with the type
** va_copy copies the list of params to a temporary list to read it > once
*/
int			ft_printf(const char *str, ...)
{
	va_list	a_list;
	va_list	a_list_copy;
	char	*type;
	int		param_number;
	int		i;

	if (str == 0)
		return (0);
	i = 0;
	param_number = count_expected_params_number(str);
	va_start(a_list, str);

	va_copy(a_list_copy, a_list);

	va_end(a_list);

}