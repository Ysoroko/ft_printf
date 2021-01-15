/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_analyze_first_arg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 09:37:44 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/15 19:16:58 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_ZERO_BEFORE_N_IN_STR
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
** FT_EXTRACT_STR
** This function, given the address of the '%' char
** will extract the related flags string, duplicate it with malloc and
** return its address. The extraction is done until a character from charset is
** encountered, this character is included in the copy
** Returns the address of the extracted string or 0 in case of error
*/

static char		*ft_extract_str(const char *start, const char *charset)
{
	int		i;
	int		len;
	char	*ret;

	if (!start || !charset)
		return (0);
	if (!ft_strcmp((char *)charset, ""))
		return (ft_strdup(""));
	i = 0;
	len = 0;
	while (start[len] && !(ft_strchr(charset, start[len])))
		len++;
	if (start[len] && ft_strchr(charset, start[len]))
		len++;
	if (!(ret = malloc(sizeof(*ret) * (len + 1))))
		return (0);
	i = -1;
	while (++i < len)
		ret[i] = start[i];
	ret[i] = 0;
	return (ret);
}

/*
** FT_FLAGS_TO_LIST
** This function recieves the [%][...][type] part of the ft_printf
** argument. It analyzes it and stores all the necessary flags
** data in a newly created t_list structure.
** Returns the pointer to this new t_list or 0 in case of error.
*/

static t_list	*ft_flags_to_list(char *str_percent)
{
	t_list	*list;

	if (!str_percent || !(list = ft_lstnew()))
		return (0);
	list->definer_str = str_percent;
	if (!(list->before_dot = ft_extract_str(str_percent, ".")))
		return (0);
	if ((list->after_dot = ft_strchr(str_percent, '.')) != 0)
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
** FT_FIRST_ARG_HELP
** This is the function used to help the ft_analyze_first_flag.
** It will:
** 1) Extract the [%][flags][type char] string from s string argument,
** 2) Use the result to store data about flags inside a newly created
**		t_list data structure
** 3) Process the data to print the necessary output
** Return the t_list structure with all the flags info stored inside or
** 0 if a malloc fails somewhere or an error occurs
*/

static t_list	*ft_first_arg_help(char **t, va_list **v, char **s, int *i)
{
	t_list	*list;

	list = 0;
	if (!(*t = ft_extract_str(s[*i + 1], TYPE_CHARS)))
		return (0);
	if (!(list = ft_flags_to_list(*t)))
	{
		ft_free(t, 0, 0);
		return (0);
	}
	if (!(ft_process_list(list, *v)))
	{
		ft_free(t, 0, &list);
		return (0);
	}
	*i += (int)ft_strlen(list->definer_str);
	return (list);
}

/*
** FT_ANALYZE_FIRST_ARG
** This function is the central hub of printf.
** It goes through the first printf argument, reads all the characters,
** prints everything outside the '%...[type]' part and sends everything
** else to other functions to extract needed informations
** It returns the number of chars printed during one whole call to printf
** or -1 if an error occurs
*/

int				ft_analyze_first_arg(const char *s, va_list *v_l)
{
	int		i;
	int		printed;
	t_list	*list;
	char	*temp;

	i = -1;
	printed = 0;
	while (s[++i])
	{
		if (s[i] == '%')
		{
			if (!(temp = ft_extract_str(&s[i + 1], TYPE_CHARS)))
				return (0);
			if (!(list = ft_flags_to_list(temp)))
			{
				ft_free(&temp, 0, 0);
				return (-1);
			}
			if (!(ft_process_list(list, v_l)))
			{
				ft_free(&temp, 0, &list);
				return (-1);
			}
			i += (int)ft_strlen(list->definer_str);
			/*if (!(list = ft_first_arg_help(&temp, &v_l, (char **)&s, &i)))
				return (-1);*/
			printed += list->chars_printed;
			ft_free(&temp, 0, &list);
			if (!(s[i]))
				return (printed);
		}
		else
		{
			ft_putchar_fd(s[i], FD);
			printed++;
		}
	}
	return (printed);
}
