/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_first_arg_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 09:37:44 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/02 15:50:07 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** This function is used to find whether there is a digit char in the string
** And if yes, whether it starts with 0. This helps us to find the '0' flag.
** If it starts with 0, returns 1
** Returns 0 otherwise
*/

static int		ft_zero_before_n_in_str(char *str)
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

static char		*ft_extract_str(char *start, const char *charset)
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

static t_list	*ft_flags_to_list(char *str_percent)
{
	char	*point;
	char	*before_point;
	char	*after_point;
	t_list	*list;

	if (!str_percent || !(list = lst_new()))
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
		list->precision_flag = ft_atoi(list->after_point);
	}
	list->minus_flag = ft_strchr(list->before_point, '-');
	list->star_before_point = ft_strchr(list->before_point, '*');
	list->width_flag = ft_atoi(list->before_point);
	list->zero_flag = ft_zero_before_n_in_str(list->before_point);
	list->type_flag = str_percent[ft_strlen(str_percent) - 1];
	return (list);
}

/*
** This function extracts all the necessary information from
** the first argument of printf. The flags corresponding to each
** next argument are stocked in a t_list data structure
*/

t_list			*ft_analyze_first_printf_argument(const char *s, va_list *v_l)
{
	int		i;
	t_list	*list;
	char	*temp;

	i = -1;
	if (s == 0 || v_l == 0)
		return (0);
	while (s[++i] != 0)
	{
		//change i position after we extract processing the t_list
		if (s[i] == '%')
		{
			if (!(temp = ft_extract_str(&s[i], "cspdiuxX%")))
				return (0);
			if (!(list = ft_flags_to_list(temp)))
				return (0);
			list->definer_str = temp;
			if (!(ft_process_list(list, v_l)))
				return (0);
			free(temp);
		}
	}
	return (list);
}
