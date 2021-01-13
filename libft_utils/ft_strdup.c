/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 16:31:36 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/13 15:28:53 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int		i;
	char	*my_src;

	if (!dest || !src)
		return (0);
	my_src = (char *)(src);
	i = -1;
	while (my_src[++i])
		dest[i] = my_src[i];
	dest[i] = '\0';
	return (dest);
}

char		*ft_strdup(const char *src)
{
	char *str;
	char *my_src;

	if (!src)
		return (0);
	my_src = (char *)(src);
	if (!(str = malloc(sizeof(*str) * (ft_strlen(my_src) + 1))))
		return (0);
	return (ft_strcpy(str, my_src));
}
