/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:25:23 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/11 11:10:09 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_CHAR_ALLOC
** Malloc's the required space for a string to be printed by printf
** Is like "calloc", but instead of filling the string with zeroes it fills it
** with the char provided in the argument
** Note: N_CHARS shouldn't include space for '\0' (strlen can be used for it)
**
** Returns the pointer to the newly allocated string, NULL if malloc fails
*/

char	*ft_char_alloc(int n_chars, char c)
{
	char	*ret_str;
	int		i;

	if (!(ret_str = malloc(sizeof(*ret_str) * (n_chars + 1))))
		return (0);
	i = -1;
	while (++i < n_chars)
		ret_str[i] = c;
	ret_str[n_chars] = 0;
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

int		ft_number_of_c_char_in_str(char *str, char c)
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

/*
** FT_FREE
** Used for freeing any argument pointer and setting it to 0
** Always returns 0
*/

int		ft_free(char **ptr1, char **ptr2, t_list **list)
{
	if (ptr1 && *ptr1)
	{
		free(*ptr1);
		*ptr1 = 0;
	}
	if (ptr2 && *ptr2)
	{
		free(*ptr2);
		*ptr2 = 0;
	}
	if (list && *list)
	{
		free((*list)->before_dot);
		(*list)->before_dot = 0;
		free((*list)->after_dot);
		(*list)->after_dot = 0;
		free(*list);
		*list = 0;
	}
	return (0);
}
