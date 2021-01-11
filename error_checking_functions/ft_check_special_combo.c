/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_special_combo.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/10 12:39:49 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/11 18:16:47 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_CHECK_FLAGS_FOR_SPECIAL_COMBO
** This function checks for special flags combinations
** and the priorities between the flags
** | Special combinations |
** Both '0' and '-' flags present -> '0' flag ignored
** '0' flag also ignored when the '.' flag is present
** and the types used are "diuxX"
*/

void	ft_check_flags_for_special_combo(t_list *list)
{
	if (!list)
		return ;
	if (list->zero_flag && (list->minus_flag || (list->after_dot &&
			ft_strchr("diuxX", list->type_flag))))
		list->zero_flag = 0;
}
