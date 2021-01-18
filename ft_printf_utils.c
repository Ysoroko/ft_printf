/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 13:25:23 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/18 09:53:36 by ysoroko          ###   ########.fr       */
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
** FT_CHECK_IF_ZERO_FLAG_IS_IGNORED
** This function checks whether the combinaton of flags leads to '0' flag
** being ignored. (It's ignored when '-' flag is present or with a precision
** present)
*/

void	ft_check_if_zero_flag_is_ignored(t_list *list)
{
	if (!list)
		return ;
	if (list->zero_flag && (list->minus_flag || (list->after_dot &&
			ft_strchr("diuxX", list->type_flag))))
		list->zero_flag = 0;
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
** The first two arguments are saved for freeing 'char *' type
** The last one is for t_list data structure, and will also
** free its content
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
		free(*list);
		*list = 0;
	}
	return (0);
}
