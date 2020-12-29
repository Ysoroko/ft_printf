/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_first_arg_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 09:37:44 by ysoroko           #+#    #+#             */
/*   Updated: 2020/12/29 12:56:25 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** This function is a modified strdup. Given the address of the '%' char
** it will extract the related flags string, duplicate it with malloc and 
** return its address. The extraction is done until a character from charset is
** encountered 
** Returns 0 in case of error
*/

char	*ft_extract_str(char *start, const char charset)
{
	int		i;
	char	*ret;

	i = 0;
	if (!start)
		return (0);
	while (!(ft_strchr(charset, start[i])) && start[i])
		i++;
	if (!(ret = malloc(sizeof(*ret) * (i + 1))))
		return (0);
	i = 0;
	while (!(ft_strchr(charset, start[i])) && start[i])
	{
		ret[i] = start[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

/*
** This function checks each character in the string and saves the used flags
** The list then stores all the flags inside 
*/

t_list		*ft_flags_to_list(char *str_percent)
{
	char	*point;
	char	*before_point;
	char	*after_point;
	t_list	*list;

	if (!str_percent || !(list = lst_new()));
		return (0);
	before_point = ft_extract_str(str_percent, ".");
	after_point = 0;
	if (point = strchr(str_percent, '.'))
	{
		list->point_flag = point;
		after_point = ft_extract_str(point, "");
	}
	if (after_point)
	{
		//'-' Flag after '.' = error
		list->error = strchr(after_point, '-'))
		list->star_after_point = strchr(after_point, '*');
		//ATOI TO ADAPT
		list->precision_flag = ft_atoi(after_point);
	}
	list->width_flag = ft_atoi(before_point);
	list->minus_flag = strchr(before_point, '-');
	list->star_before_point = strchr(before_point, '*');
	//ATOI TO ADAPT
	list->width_flag = ft_atoi(before_point);
	//CREATE FUNCTION TO LOOK FOR 0
	list->zero_flag =

	
}

/*
** This function extracts all the necessary information from
** the first argument of printf. The flags corresponding to each
** next argument are stocked in a chained list data structure
*/

t_list	*ft_analyze_first_printf_argument(const char *str)
{
	int		i;
	t_list	list;
	t_list	current_list;
	char	*temp;

	static int	atoi_next;

	i = -1;
	//don't forget to put all the variables of list to 0
	if (str == 0 || !(list = lst_new()))
		return (0);
	current_list = list;
	while (str[++i] != 0)
	{
		if (str[i] == '%')
		{
			if (!(temp = ft_extract_str(&str[i], "cspdiuxX%")))
				return (0);
			ft_flags_to_list(temp);

		}
	}
	return (&list);
}