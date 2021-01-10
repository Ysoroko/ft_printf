/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_first_arg_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 09:37:44 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/10 15:32:11 by ysoroko          ###   ########.fr       */
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

static char		*ft_extract_str(const char *start, const char *charset)
{
	int		i;
	char	*ret;

	if (!start || !charset)
		return (0);
	i = 0;
	while (start[i] && !(ft_strchr(charset, start[i])))
		i++;
	if (start[i] && ft_strchr(charset, start[i]))
		i++;
	if (!(ret = malloc(sizeof(*ret) * (i + 1))))
		return (0);
	i = 0;
	while (start[i] && !(ft_strchr(charset, start[i])))
	{
		ret[i] = start[i];
		i++;
	}
	if (start[i] && ft_strchr(charset, start[i]))
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
	t_list	*list;

	if (!(list = ft_lstnew()))
		return (0);
	list->definer_str = str_percent;
	if (!(list->before_dot = ft_extract_str(str_percent, ".")))
		return (0);
	if ((list->point_flag = ft_strchr(str_percent, '.')) != 0)
	{
		if (!(list->after_dot = ft_extract_str(list->point_flag + 1, "")))
		{
			ft_free(&(list->before_dot), 0, 0);
			return (0);
		}
	}
	if (list->after_dot)
	{
		list->star_after_point = ft_strchr(list->after_dot, '*');
		list->precision = ft_atoi_p(list->after_dot);
	}
	list->minus_flag = ft_strchr(list->before_dot, '-');
	list->star_before_point = ft_strchr(list->before_dot, '*');
	list->width = ft_atoi_p(list->before_dot);
	list->zero_flag = ft_zero_before_n_in_str(list->before_dot);
	list->type_flag = str_percent[ft_strlen(str_percent) - 1];
	return (list);
}

/*
** This function extracts all the necessary information from
** the first argument of printf. The flags corresponding to each
** next argument are stocked in a t_list data structure
*/

int			ft_analyze_first_printf_argument(const char *s, va_list *v_l)
{
	int		i;
	int		printed;
	int		list_ret;
	t_list	*list;
	char	*temp;

	i = -1;
	printed = 0;
	if (v_l == 0)
		return (0);
	while (s[++i])
	{
		if (s[i] == '%')
		{
			if (!(temp = ft_extract_str(&(s[i + 1]), TYPE_CHARS)))
				return (0);
			if (!(list = ft_flags_to_list(temp)))
				return (ft_free(&temp, 0, 0));
			if (!(list_ret = (ft_process_list(list, v_l))))
				return (ft_free(&temp, 0, &list));
			i += list_ret;
			printed += ft_strlen(list->text_to_print);
			//printf("I after ft_process_list: %d", i);
			ft_free(&temp, 0, &list);
		}
		ft_putchar_fd(s[i], FD);
		printed++;
	}
	return (printed);
}
