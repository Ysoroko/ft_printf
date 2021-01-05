/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_t_list_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:27:24 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/05 11:58:35 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "printf.h"

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
	pnt->precision_flag = 0;
	pnt->width_flag = 0;
	pnt->star_after_point = 0;
	pnt->type_flag = 0;
	pnt->text_to_print = 0;
	return (pnt);
}
