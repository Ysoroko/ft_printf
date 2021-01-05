/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:25:23 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/05 16:45:22 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

/*
** FT_CHAR_ALLOC
** Malloc's the required space for a string to be printed by printf
** Is like "calloc", but instead of filling the string with zeroes it fills it
** with the char provided in the argument
**
** Returns the pointer to the newly allocated string, NULL if malloc fails
*/

char	*ft_char_alloc(int n_chars, char c)
{
	char	*ret_str;
	int		i;

	if (!(ret_str = malloc(sizeof(*ret_str) * n_chars + 1)))
		return (0);
	i = -1;
	ret_str[n_chars] = 0;
	while (ret_str[++i])
		ret_str[i] = c;
	return (ret_str);
}

/*
** FT_STR_HAS_CHARS_OTHERS_THAN_CHARSET
** Works like ft_strchr, but instead of looking for a specific char in "str",
** Looks for any chars different from "charset" chars in "str" argument
** Returns 1 if str has any "forbidden" chars, 0 otherwise
*/

int		ft_str_has_other_chars(char *str, char *charset)
{
	int i;
	int j;

	i = -1;
	j = -1;
	if (!str || !charset)
		return (0);
	while (str[++i])
	{
		if (!(ft_strchr(charset, str[i])))
			return (1);
	}
	return (0);
}

/*
** FT_NUMBER_OF_C_CHAR_IN_STR
** Returns the number of occurences of c char argument in str string argument
*/

int				ft_number_of_c_char_in_str(char *str, char c)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (str[++i])
	{
		if (str[i] == c)
			count++;
	}
	return (count);
}

/*
** FT_TOO_MANY_FLAG_CHARS_IN_STR
** Checks for the number of occurences of '.' and '*' in the total string,
** the part before the dot, and the part after the dot
** Returns 1 if there is too many of those flags, 0 otherwise
*/

int				ft_too_many_flag_chars_in_str(char *all, char *bef, char *aft)
{
	if (ft_number_of_c_char_in_str(all, '.') > 1)
		return (1);
	if (ft_number_of_c_char_in_str(bef, '*') > 1)
		return (1);
	if (aft)
	{
		if (ft_number_of_c_char_in_str(aft, '*') > 1)
			return (1);
	}
	return (0);
}

/*
** FT_LSTNEW
** Malloc's the necessary size of the t_list type on the heap
** and sets all of its components to 0
** Returns the pointer to the newly created t_list or 0 if malloc fails
*/

t_list	*ft_lstnew(void)
{
	t_list *pnt;

	if (!(pnt = malloc(sizeof(t_list))))
		return (0);
	pnt->definer_str = 0;
	pnt->before_dot = 0;
	pnt->after_dot = 0;
	pnt->minus_flag = 0;
	pnt->star_before_point = 0;
	pnt->zero_flag = 0;
	pnt->point_flag = 0;
	pnt->precision = 0;
	pnt->width = 0;
	pnt->star_after_point = 0;
	pnt->type_flag = 0;
	pnt->text_to_print = 0;
	return (pnt);
}