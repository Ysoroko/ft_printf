/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_first_arg_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 09:37:44 by ysoroko           #+#    #+#             */
/*   Updated: 2020/12/29 14:29:30 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** This function is used to find whether there is a digit char in the string
** And if yes, whether it starts with 0
** If it starts with 0, returns 1
** Returns 0 otherwise
*/

int		ft_zero_before_n_in_str(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (!ft_isdigit(str[i]) && str[i])
		i++;
	if (str[i] == '0')
		return (1);
	return (0);
}

/*
** This function is a modified strdup. Given the address of the '%' char
** it will extract the related flags string, duplicate it with malloc and 
** return its address. The extraction is done until a character from charset is
** encountered, this character is included in the copy
** Returns 0 in case of error
*/

char	*ft_extract_str(char *start, const char *charset)
{
	int		i;
	char	*ret;

	i = 0;
	if (!start || !charset)
		return (0);
	while (!(ft_strchr(charset, start[i])) && start[i])
		i++;
	if (ft_strchr(charset, start[i]) && start[i] != 0)
		i++;
	if (!(ret = malloc(sizeof(*ret) * (i + 1))))
		return (0);
	i = 0;
	while (!(ft_strchr(charset, start[i])) && start[i])
	{
		ret[i] = start[i];
		i++;
	}
	if (ft_strchr(charset, start[i]) && start[i] != 0)
	{
		ret[i] = start[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

/*
** This function checks each character in the string and saves the used flags
** in the initialised t_list which it returns
** It divides the string into 2 parts, before and after the '.' flag to
** be able to tell the difference between precision and width and the '*' flags
*/

t_list		*ft_flags_to_list(char *str_percent, t_list *current_list)
{
	char	*point;
	char	*before_point;
	char	*after_point;
	t_list	*list;

	//lst_new to adapt
	if (!str_percent || !(list = lst_new()));
		return (0);
	list->before_point = ft_extract_str(str_percent, ".");
	list->after_point = 0;
	if (point = ft_strchr(str_percent, '.'))
	{
		list->point_flag = point;
		list->after_point = ft_extract_str(point, "");
	}
	if (list->after_point)
	{
		list->star_after_point = ft_strchr(list->after_point, '*');
		//ATOI TO ADAPT
		list->precision_flag = ft_atoi(list->after_point);
	}
	list->minus_flag = ft_strchr(list->before_point, '-');
	list->star_before_point = ft_strchr(list->before_point, '*');
	//ATOI TO ADAPT
	list->width_flag = ft_atoi(list->before_point);
	list->zero_flag = ft_zero_before_n_in_str(list->before_point);
	list->type_flag = str_percent[ft_strlen(str_percent) - 1];
	current_list->next = list;
	return (list);
}

/*
** This function extracts all the necessary information from
** the first argument of printf. The flags corresponding to each
** next argument are stocked in a chained list data structure
*/

t_list	*ft_analyze_first_printf_argument(const char *str)
{
	int		i;
	t_list	*list;
	t_list	*current_list;
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
			if (!(current_list = ft_flags_to_list(temp, current_list)))
				return (0);
			free(temp);
		}
	}
	return (list);
}