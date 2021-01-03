/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 09:01:27 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/03 16:09:47 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "printf.h"

/* 
** PRINTF ARGUMENTS STRUCTURE
** %[flags][width][.precision][length]specifier
*/



int main()
{
	//char	*str = "First";
	int		n = 14;

	//STRING
	//printf("%-0s", "oops");

	//INT
	//ft_printf("Lol%s\n", "Hello there, general Kenobi\n");

	//"0" FLAG
	//printf("08s + test: %08s\n", "test");
	printf("%*.*s", 8, 3, "haha");

	return (0);
}



/*
** TYPE SPECIFIERS:
**
** %C = Char
** %S = String
** %P = Address
** %D + I = Integer (no difference between the two for the output)
** %U = Unsigned Integer
** %x = Hexadecimal with base "0123456789abcdef"
** %X = Hexadecimal with base "0123456789ABCDEF"
*/


/*
** FLAGS:
**
** "Width":		Specifies how many spaces are needed for the printed string. (= number before the '.' flag)
**				- By default, the character is formatted to the right (Ex: printf("%5s\n", "ha") --> "   ha")
**				- If the width is too little to print the string, it's ignored ("Ex: printf("%2s\n", "haha"); --> "haha")
**				- Works with all the formats "cspdiuxX% "
**
**
** "Precision":	Specifies the precision for the numbers (= number after '.' if it's present)
**				- Undefined behaviour with: "%cp"
**				- With "%s" string format specifier, sets the number of chars from the string that will be printed
				  (Ex: printf("%4.2s\n", "ahah") --> "  ah")
**				- With "%diUxX" format specifiers, it sets the number of chars in the output string
**				  Unlike with "%s", it will always print at least the number itself, even if the precision is too little
**				  If the precision is bigger than the space needed to print the number, it will fill the rest of it (left) with '0'.
**				- In combination with WIDTH: 
**					1) The precision sort of "callocs" a string with "precision" number of '0'. It then writes inside the number
**					2) The width sort of "mallocs" a string with "width" number of spaces in it.It then writes the string from 1) inside
**				- If there is a '.', but no number afterwards --> no effect
**					
**					
**
** "0":			Fills in the extra spaces from the width specifier with '0' char
** 				- Ignored with no width, with '-' flag, and with precision present
**				- If the width is less than the necessary spaces to print the number - ignored
**				- Undefined behaviour with "%s", "%c" and "%p" type specifiers
**
** "-":			Instead of formatting the output string to the right, does it to the left
**				- Example: "printf("%-4s\n", "ha"); --> "ha  "
**				  (without the "-": "printf("%4s\n", "ha"); --> "  ha")
**				- Overrides the "0" flag
**				- Works with all the type specifiers: "cspdiuxX%"
**
** "*":			Instead of the number explicitly written in first printf argument, the width or precision
**				(depending on whether '*' is before orafter the '.' flag will be instead taken from the next printf argument)
**				- Example: "printf("%*.*s", 8, 3, "haha") ---> "     hah" (Width = 8, Precision = 3)
*/





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