/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:27:46 by ysoroko           #+#    #+#             */
/*   Updated: 2020/12/26 13:02:38 by ysoroko          ###   ########.fr       */
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
** Returns the expected parameters number based on the amount of "%" in the str
** This means that the str itself isn't counted in the return value
*/
static int	count_params_number(const char *str)
{
	int	i;
	int	count;

	if (str == 0)
		return (0);
	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if(str[i] == '%')
			count++;
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
	char	*type;
	int		param_number;
	int		i;

	if (str == 0)
		return (0);
	i = 0;
	param_number = count_params_number(str);
	va_start(a_list, str);



	va_end(a_list);

}