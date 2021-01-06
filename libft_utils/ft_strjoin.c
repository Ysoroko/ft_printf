/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 11:51:24 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/06 11:52:14 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

char	*ft_strjoin(char const *pref, char const *suff)
{
	char	*ret;
	char	*my_pref;
	char	*my_suff;
	size_t	i;
	size_t	j;

	if (pref == 0 || suff == 0)
		return (0);
	i = -1;
	j = -1;
	my_pref = (char *)(pref);
	my_suff = (char *)(suff);
	ret = malloc(sizeof(char) * (ft_strlen(my_pref) + ft_strlen(my_suff) + 1));
	if (ret == 0)
		return (0);
	while (pref[++i] != '\0')
		ret[i] = pref[i];
	while (suff[++j] != '\0')
	{
		ret[i] = suff[j];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}
