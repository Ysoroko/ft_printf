/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:05:19 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/11 15:10:11 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** FT_REPLACE_ALLOC
** It frees the memore allocated at the address of str_to_replace,
** and replaces it with a different, newly allocated string
** specified as an argument
** Returns 0 if the allocation fails or the new adress otherwise
*/

char	*ft_replace_alloc(char **str_to_replace, char *replace_by)
{
	char	*new_address;

	if (!str_to_replace || !replace_by)
		return (0);
	ft_free(str_to_replace, 0, 0);
	if (!(new_address = ft_strdup(replace_by)))
		return (0);
	return (new_address);
}
