/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_libft_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 12:38:56 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/15 18:28:54 by ysoroko          ###   ########.fr       */
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

/*
** A modified version which only returns !0 if both strings are the same,
** including the strlen
*/

int			ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (-1);
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((int)(s1[i] - s2[i]));
}

char		*ft_strjoin(char const *pref, char const *suff)
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
	while (pref[++i])
		ret[i] = pref[i];
	while (suff[++j] != '\0')
	{
		ret[i] = suff[j];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

/*
** FT_COUNT_N_DIGITS
** This function will count the number of digits in the string argument
** and return the number of digit characters found
*/

int			ft_count_n_digits(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isdigit(str[i]))
			count++;
		i++;
	}
	return (count);
}
