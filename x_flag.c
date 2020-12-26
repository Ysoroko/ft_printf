/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   x_flag.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 13:39:20 by ysoroko           #+#    #+#             */
/*   Updated: 2020/12/26 13:45:14 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** x and X flags are used for the hexadecimal conversion
** Lowercase "x" converts to hexadecimal using "0123456789abcdef" as the base
** Uppercase "X" converts to hexadecimal using "0123456789ABCDEF" as the base
*/
void	x_flag(unsigned int n, char x)
{
	if (x == 'x')
	{
		ft_putnbr_base(n, "0123456789abcdef");
		return ;
	}
	if (x == 'X')
	{
		ft_putnbr_base(n, "0123456789ABCDEF");
		return ;
	}
	return ;
}