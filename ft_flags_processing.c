/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags_processing.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:13:15 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/02 15:38:48 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	ft_process_list(t_list *list, va_list *v_list)
{
	if (list->type_flag == 's')
		ft_putstr_fd(va_arg(*v_list, char *), FD);
}
