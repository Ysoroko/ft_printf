/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 09:01:27 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/02 15:48:27 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int main()
{
	char	*str = "First";
	int		n = 2;

	//STRING
	//printf("%-0s", "oops");

	//INT
	ft_printf("%s\n", "Hello there");
	return (0);
}

/*
** ERRORS/SPECIAL CASES:
*/
// 1) printf("%.s", "oops"); --> point with no precision specified -> prints nothing
// 2) printf("%*.s", "oops"); --> ERROR, too few args

					//NUMBERS
//printf("%88888888888888888888888888888888d", n); -> error because 88... is too big (outside of int)
//printf("%0d", n); -> just prints n
//printf("%.0d", n); -> just prints n


					//ZERO FLAG
// 3) printf("%-08d", n); --> FLAG '0' IGNORED WHEN '-' PRESENT (both are stuck to the left)
// 4) printf("%.05d", n); --> flag '0' is ignored with the precision
// 5) printf("%010", str); --> flag '0' undefined behaviour with a string

					//'-' FLAG
// 6) printf("%.-2s", str); --> Flag '-' after '.' = error