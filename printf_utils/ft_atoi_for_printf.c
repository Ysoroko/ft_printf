/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_for_printf.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 15:31:19 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/11 11:10:09 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		ft_char_is_in_charset(char c, const char *charset)
{
	int		i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int		ft_extreme(int number, unsigned long long extreme, int sign)
{
	unsigned long long	min;
	unsigned long long	max;

	min = 9223372036854775808U;
	max = 9223372036854775807U;
	if (extreme > max && sign == 1)
		return (-1);
	if (extreme > min && sign == -1)
		return (0);
	return (number * sign);
}

int				ft_atoi_p(const char *str)
{
	int					i;
	int					sign;
	int					number;
	unsigned long long	extreme;
	char				*my_str;

	if (!str)
		return (0);
	i = 0;
	sign = 1;
	number = 0;
	extreme = 0;
	my_str = (char *)(str);
	while (ft_char_is_in_charset(my_str[i], ".*-"))
		i++;
	while (my_str[i] >= '0' && my_str[i] <= '9')
	{
		number = number * 10 + my_str[i] - '0';
		extreme = extreme * 10 + my_str[i] - '0';
		i++;
	}
	return (ft_extreme(number, extreme, sign));
}
