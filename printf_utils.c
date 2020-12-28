/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 15:20:47 by ysoroko           #+#    #+#             */
/*   Updated: 2020/12/28 17:53:04 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** This function allows to tell whether a char argument is a type definer
** Char definer is the last flag we see before moving on to the next argument
** Returns 1 if the character is a type definer
** Returns 0 otherwise
*/

int		ft_char_defines_type(char c)
{
	char	*str;
	int		i;

	str = "cspdiuxX%";
	i = 0;
	while (str[i] != 0)
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

/*
** This function checks each character in the string and saves the used flags
** The list then stores all the flags inside 
*/

int		ft_flags_to_list(char *str_c, t_list *list, int before_point)
{
	if (before_point == 1)
	{
		if (str_c[0] == '-')
			list->minus_flag = 1;
		//To check for 0 + extract the width
		else if (ft_is_digit(str_c[0]) && n = ft_atoi(atoi_ptr))
			list -> width_flag = n;
		//UPDATE THIS FOR THE ZERO FLAG
		else
			list -> zero_flag = 1;
		else if (str_c[0] == '*')
			list->star_before_point = 1;
	}
	else
	{
		if (str_c[0] == '-')
			list->error = 1;
		//TO UPDATE
		else if (ft_is_digit(str_c[0]))
			list -> precision_flag = ft_atoi(atoi_ptr);
		else if (str_c[0] == '*')
			list->star_after_point = 1;
	}
	
}

t_list	*ft_analyze_first_printf_argument(const char *str)
{
	int		i;
	t_list	list;
	t_list	current_list;

	static int	atoi_next;

	i = -1;
	//don't forget to put all the variables of list to 0
	if (str == 0 || !(list = lst_new()))
		return (0);
	current_list = list;
	while (str[i] != 0)
	{
		while (str[++i] != '%' && str[i])
			ft_putchar_fd(str[i], 1);
		while (str[++i] != '.' && !ft_char_defines_type(str[i]) && str[i])
			ft_flags_to_list(&str[i], &current_list, 1);
		if (str[i] == '.')
		{
			while (!ft_char_defines_type(str[++i]) && str[i])
				ft_flags_to_list(&str[i], &current_list, 0);
		}
		if (!ft_char_defines_type(str[i]))	
			current_list.error = 1;
		else
		{
			current_list.type_flag = str[i];
			current_list.next = ft_lstadd_back(t_list &list, current_list);
		}
	}
	return (&list);
}