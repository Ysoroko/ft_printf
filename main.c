/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 09:01:27 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/14 10:47:27 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* 
** PRINTF ARGUMENTS STRUCTURE
** %[flags][width][.precision][length]specifier
*/

//!!!!!!!!!!!!!!!!!!!!!printf("%020.8%") works (with 'c' it doesn't!!!);
int main()
{
	int		a = 12;
	int		b = 0;
	char	c = 'a';
	int		d = 2147483647;
	int		e = -2147483648;
	int		f = 42;
	int		g = 25;
	int		h = 4200;
	int		i = 8;
	int		j = -12;
	int		k = 123456789;
	int		l = 0;
	int		m = -12345678;
	char	*n = "abcdefghijklmnop";
	char	*o = "-a";
	char	*p = "-12";
	char	*q = "0";
	char	*r = "%%";
	char	*s = "-2147483648";
	char	*t = "0x12345678";
	char	*u = "-0";

	char *str = "JE SUIS UN STRING";
	str = 0;


	//'	\0' char issue
	printf("\nP: |%d|\n\n",printf("P: |%1c|", 0));
	ft_printf("F: |%d|\n\n",ft_printf("F: |%1c|\n", 0));


	/*
	PRINT(" --- Return : %d\n", PRINT("%c, %-c, %12c, %-3c, %-1c, %1c, %-2c, %-4c, %5c, %3c, %-*c, %-*c, %*c, %*c", 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0, 0, 0, 0, 0));
	PRINT(" --- Return : %d\n", PRINT("(null)"));
	ft_printf("F: |%p|\n", str);
	printf("P: |%p|\n", str);
	*/
	
	return (0);
}



/* 
** PRINTF ARGUMENTS STRUCTURE
** %[flags][width][.precision][length]specifier
*/

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
** %% = only a '%' char is printed (warning, printf("%020.8%") != printf("%020.8c", 'c'))
*/  


/*
** FLAGS:
**
** "Width":		Specifies how many spaces are needed for the printed string. (= number before the '.' flag)
**				- By default, the character is formatted to the right (Ex: printf("%5s\n", "ha") --> "   ha")
**				- If the width is too little to print, it's ignored ("Ex: printf("%2s\n", "haha"); --> "haha")
**				- Works with all the formats "cspdiuxX% "
**				- Several widths separated by other flags --> error
**				- Format = Unsigned int
**
**
** "Precision":	Specifies the precision for the numbers (= number after '.' if it's present)
**				- Undefined behaviour with: "%cp"
**				- With "%s" string format specifier, sets the number of chars from the string that will be printed
				  (Ex: printf("%4.2s\n", "ahah") --> "  ah")
				  if precision is bigger than the needed string->only prints the string(all the chars)
				  if precision is less than the needed string -> prints only [precision] chars from the string
				  if precision is '0' -> prints an empty string ""
**				- With "%diUxX" format specifiers, it sets the number of chars in the output string
**				  Unlike with "%s", it will always print at least the number itself, even if the precision is too little
**				  If the precision is bigger than the space needed to print the number, it will fill the rest of it (left) with '0'.
**				- In combination with WIDTH: 
**					1) The precision sort of "callocs" a string with "precision" number of '0'. It then writes inside the number
**					2) The width sort of "mallocs" a string with "width" number of spaces in it.It then writes the string from 1) inside
**				- If there is a '.', but no number afterwards --> no effect
**				- If a precision of 0 is used with a '0' in diUxX -> prints nothing
**				- If a precision is used with '-' flag -> '-' flag is ignored
**				- If precision > width, only precision is printed
**				- FORMAT = UNSIGNED INT
**
** "0":			Fills in the extra spaces from the width specifier with '0' char
** 				- Ignored with no width, with '-' flag, and with precision present
**				- If the width is less than the necessary spaces to print the number - ignored
**				- Undefined behaviour with "%s", "%c" and "%p" type specifiers
**				- Multiple "0" --> no problem
**				- '0' after the point -> ignored only when there is no '*', otherwise --> error
**
** "-":			Instead of formatting the output string to the right, does it to the left
**				- Example: "printf("%-4s\n", "ha"); --> "ha  "
**				  (without the "-": "printf("%4s\n", "ha"); --> "  ha")
**				- Overrides the "0" flag
**				- Works with all the type specifiers: "cspdiuxX%"
**				- "-" after the "." --> error
**				- Multiple "-" before the "." --> no problem
**
** "*":			Instead of the number explicitly written in first printf argument, the width or precision
**				(depending on whether '*' is before orafter the '.' flag will be instead taken from the next printf argument)
**				- Example: "printf("%*.*s", 8, 3, "haha") ---> "     hah" (Width = 8, Precision = 3)
**				- Multiple "*" before/after '.' --> error
**				- Both "*" and the width/precision int are present --> error
**				- '0' or '-' cannot be after '*' --> error
*/
