/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 14:59:49 by ldelmas           #+#    #+#             */
/*   Updated: 2021/01/11 11:10:09 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "main.h"

void secondary_colors(char *str)
{
	printf(BOLDCYAN);
	if (str)
		printf("%s", str);
	//printf(BOLDBLACK);
}

void use_colors(char *str, char *s)
{
	if (str)
	{
		printf(BOLDBLUE); 
   		printf("\n------------------------------------------------------------------------------------------------------------------------------------\n\n");
		printf("%s", str);
	}
	if (s && str)
		printf("\n");
	secondary_colors(s);
}

void change_fdout(int *dpl, int *fd)
{
	*dpl = dup(1);
	close(1);
	*fd = open("test1.txt", O_RDWR);
	while (*fd != 1)
	{
		close(1);
		close(*fd);
		*fd = open("test1.txt", O_RDWR);
	}
}

void empty_file(FILE **file, char *name)
{
	fclose(*file);
	*file = fopen(name, "w");
	fclose(*file);
	*file = fopen(name, "w+");
}

void compare_files(FILE **file1, FILE **file2, int *dpl, int *fd, char *next_title, char *subtitle)
{	
	char		buf1[5000];
	char		buf2[5000];
	int			i;
	//int			fd;


	i = 0;
	while (i < 4999)
	{
		buf1[i] = '\0';
		buf2[i++] = '\0';
	}
	close(*fd);
	dup2(*dpl, 1);
	close(*dpl);
	(void)fd;

	rewind(*file1);
	rewind(*file2);
	fgets(buf1, sizeof buf1, *file1);
	fgets(buf2, sizeof buf2, *file2);

	//DELETE US
	// printf(COLOR_RED);
	// printf("\n%s", buf1);
	// printf(COLOR_GREEN);
	// printf("%s", buf2);
	//DELETE US
	i = 0;
	while (buf1[i] == buf2[i])
	{
		if (!buf1[i] && !buf2[i])
		{
			printf(COLOR_GREEN);
			printf("   [OK]\n");
			break ;
		}
		else
			i++;
	}
	if (buf1[i] != buf2[i])
	{
		printf(COLOR_RED);
		printf("   [KO]\n");
		printf("%s", buf1);
		printf(COLOR_GREEN);
		printf("%s", buf2);
	}
	if (next_title || subtitle)
		use_colors(next_title, subtitle);
	change_fdout(dpl, fd);
	empty_file(file1, "test1.txt");
	empty_file(file2, "test2.txt");
}

int main()
{
	char		*hello;
	unsigned	int u;

	FILE		*file1;
	FILE		*file2;
	int			fd;
	int			dpl;

	u = 2456789;
	hello = "coucou";

	file1 = fopen("test1.txt", "w+");
	file2 = fopen("test2.txt", "w+");
	change_fdout(&dpl, &fd);

while (1)
{
	use_colors("TEST : NO FLAGS -------- FORMATS '%sxXpd' :     ", (void*)0);
	ft_printf("%xCouco%%u %s ca %pva?%X  %d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%xCouco%%u %s ca %pva?%X  %d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '0' -------- FORMATS 'xXd' ", "VAL > 0");
	ft_printf("%012xCouco%%u %s ca %pva?%00X  %013d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%012xCouco%%u %s ca %pva?%00X  %013d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "NO VAL ");
	ft_printf("%0xCouco%%u %s ca %pva?%0X  %0d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%0xCouco%%u %s ca %pva?%0X  %0d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '-' -------- FORMATS 'xXd' ", "VAL > 0");
	ft_printf("%-12xCouco%%u %s ca %pva?%-2X  %-13d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%-12xCouco%%u %s ca %pva?%-2X  %-13d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "NO VAL ");
	ft_printf("%-xCouco%%u %s ca %pva?%-X  %-d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%-xCouco%%u %s ca %pva?%-X  %-d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '.' -------- FORMATS 'sxXd'", "VAL > 0");
	ft_printf("%.12xCouco%%u %.15s ca %pva?%.20X  %.13d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%.12xCouco%%u %.15s ca %pva?%.20X  %.13d\n", -245678, "Test2", hello, u, -123456);	
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "NO VAL ");
	ft_printf("%.xCouco%%u %.s ca %pva?%.X  %.d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%.xCouco%%u %.s ca %pva?%.X  %.d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG VAL -------- FORMATS 'sxXpd' :      ", (void*)0);
	ft_printf("%12xCouco%%u %15s ca %15pva?%15X  %13d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%12xCouco%%u %15s ca %15pva?%15X  %13d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '*' -------- FORMATS 'sxXpd' :      ", "* > 0");
	ft_printf("%*xCouco%%u %*s ca %*pva?%*X  %*d\n", 12, -245678, 15, "Test2", 15, hello, 15, u, 13, -123456);
	fprintf(file2, "%*xCouco%%u %*s ca %*pva?%*X  %*d\n", 12, -245678, 15, "Test2", 15, hello, 15, u, 13, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("%*xCouco%%u %*s ca %*pva?%*X  %*d\n", -12, -245678, -15, "Test2", -15, hello, -15, u, -13, -123456);
	fprintf(file2, "%*xCouco%%u %*s ca %*pva?%*X  %*d\n", -12, -245678, -15, "Test2", -15, hello, -15, u, -13, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* = 0");
	ft_printf("%*xCouco%%u %*s ca %*pva?%*X  %*d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0, -123456);
	fprintf(file2, "%*xCouco%%u %*s ca %*pva?%*X  %*d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0, -123456);
	
	
	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '*.*' -------- FORMATS 'sxXd' :    ", "*1 > 0 & *2 > 0");
	ft_printf("%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 12, 12, -245678, 20, 15, "Test2", 25, hello, 12, 25 ,u, 15, 20, -123456);
	fprintf(file2, "%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 12, 12, -245678, 20, 15, "Test2", 25, hello, 12, 25 ,u, 15, 20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 < 0");
	ft_printf("%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", -12, -12, -245678, -20, -15, "Test2", -25, hello, -12,  -25 ,u, -15, -20, -123456);
	fprintf(file2, "%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", -12, -12, -245678, -20, -15, "Test2", -25, hello, -12,  -25 ,u, -15, -20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 > 0 & *2 < 0");
	ft_printf("%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 12, -12, -245678, 20, -15, "Test2", -25, hello, 12,  -25 ,u, 15, -20, -123456);
	fprintf(file2, "%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 12, -12, -245678, 20, -15, "Test2", -25, hello, 12,  -25 ,u, 15, -20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 > 0");
	ft_printf("%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", -12, 12, -245678, -20, 15, "Test2", -25, hello, -12,  25 ,u, -15, 20, -123456);
	fprintf(file2, "%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", -12, 12, -245678, -20, 15, "Test2", -25, hello, -12,  25 ,u, -15, 20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 = 0");
	ft_printf("%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 0, 0, -245678, 0, 0, "Test2", 0, hello, 0, 0,u, 0, 0, -123456);
	fprintf(file2, "%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 0, 0, -245678, 0, 0, "Test2", 0, hello, 0, 0,u, 0, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 > 0 & *2 = 0");
	ft_printf("%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 25, 0, -245678, 5, 0, "Test2", 0, hello, 12, 0,u, 1, 0, -123456);
	fprintf(file2, "%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 25, 0, -245678, 5, 0, "Test2", 0, hello, 12, 0,u, 1, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 = 0");
	ft_printf("%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", -25, 0, -245678, -5, 0, "Test2", 0, hello, -12, 0,u, -1, 0, -123456);
	fprintf(file2, "%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", -25, 0, -245678, -5, 0, "Test2", 0, hello, -12, 0,u, -1, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 > 0");
	ft_printf("%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 0, 30, -245678, 0, 25, "Test2", 0, hello, 0, 2, u, 0, 10, -123456);
	fprintf(file2, "%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 0, 30, -245678, 0, 25, "Test2", 0, hello, 0, 2, u, 0, 10, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 < 0");
	ft_printf("%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 0, -30, -245678, 0, -25, "Test2", 0, hello, 0, -2, u, 0, -10, -123456);
	fprintf(file2, "%*.*xCouco%%u %*.*s ca %*pva?%*.*X  %*.*d\n", 0, -30, -245678, 0, -25, "Test2", 0, hello, 0, -2, u, 0, -10, -123456);
	
	
	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '*.' -------- FORMATS 'sxXd' :", "* > 0");
	ft_printf("%*.xCouco%%u %*.s ca %*pva?%*.X  %*.d\n", 15, -245678, 6, "Test2", 25, hello, 25 ,u, 12,  -123456);
	fprintf(file2, "%*.xCouco%%u %*.s ca %*pva?%*.X  %*.d\n", 15, -245678, 6, "Test2", 25, hello, 25 ,u, 12,  -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("%*.xCouco%%u %*.s ca %*pva?%*.X  %*.d\n",-15, -245678, -6, "Test2", -25, hello, -25 ,u, -12,  -123456);
	fprintf(file2, "%*.xCouco%%u %*.s ca %*pva?%*.X  %*.d\n",-15, -245678, -6, "Test2", -25, hello, -25 ,u, -12,  -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* = 0");
	ft_printf("%*.xCouco%%u %*.s ca %*pva?%*.X  %*.d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0,  -123456);
	fprintf(file2, "%*.xCouco%%u %*.s ca %*pva?%*.X  %*.d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0,  -123456);
	
	
	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '.*' -------- FORMATS 'sxXd' :", "* > 0");
	ft_printf("%.*xCouco%%u %.*s ca %*pva?%.*X  %.*d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	fprintf(file2, "%.*xCouco%%u %.*s ca %*pva?%.*X  %.*d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	

	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("%.*xCouco%%u %.*s ca %*pva?%.*X  %.*d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	fprintf(file2, "%.*xCouco%%u %.*s ca %*pva?%.*X  %.*d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* = 0");
	ft_printf("%.*xCouco%%u %.*s ca %*pva?%.*X  %.*d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0, -123456);
	fprintf(file2, "%.*xCouco%%u %.*s ca %*pva?%.*X  %.*d\n", 0, -245678, 0, "Test2", 0, hello, 0 , u, 0, -123456);

	
	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS 'VAL.' -------- FORMATS 'sxXd' :   ", (void*)0);
	ft_printf("%15.xCouco%%u %6.s ca %25pva?%25.X  %12.d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%15.xCouco%%u %6.s ca %25pva?%25.X  %12.d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS 'VAL.VAL' -------- FORMATS 'sxXd' :", (void*)0);
	ft_printf("%15.5xCouco%%u %6.12s ca %25pva?%25.5X  %12.20d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%15.5xCouco%%u %6.12s ca %25pva?%25.5X  %12.20d\n", -245678, "Test2", hello, u, -123456);

	
	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS 'VAL.0' -------- FORMATS 'sxXd' :  ", (void*)0);
	ft_printf("%15.0xCouco%%u %6.0s ca %pva?%25.0X  %12.0d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%15.0xCouco%%u %6.0s ca %pva?%25.0X  %12.0d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '0.VAL' -------- FORMATS 'xXd' :   ", (void*)0);
	ft_printf("%0.15xCouco%%u %.6s ca %pva?%0.25X  %0.12d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%0.15xCouco%%u %.6s ca %pva?%0.25X  %0.12d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '0.' -------- FORMATS 'xXd' :      ", (void*)0);
	ft_printf("%0.xCouco%%u %.s ca %pva?%0.X  %0.d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%0.xCouco%%u %.s ca %pva?%0.X  %0.d\n", -245678, "Test2", hello, u, -123456);

	
	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '.0' -------- FORMATS 'sxXd' :", "0 ALONE ");
	ft_printf("%.0xCouco%%u %.0s ca %pva?%.0X  %.0d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%.0xCouco%%u %.0s ca %pva?%.0X  %.0d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "MULTIS 0");
	ft_printf("%.00000000000xCouco%%u %.000000000s ca %pva?%.00000000X  %.00000000d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%.00000000000xCouco%%u %.000000000s ca %pva?%.00000000X  %.00000000d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '0VAL.' -------- FORMATS 'xXd' :   ", (void*)0);
	ft_printf("%0.xCouco%%u %.s ca %pva?%0.X  %0.d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%0.xCouco%%u %.s ca %pva?%0.X  %0.d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '0VAL.VAL' -------- FORMATS 'xXd' :", "0 ALONE ");
	ft_printf("%015.15xCouco%%u %.6s ca %pva?%025.5X  %012.25d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%015.15xCouco%%u %.6s ca %pva?%025.5X  %012.25d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "MULTIS 0");
	ft_printf("%00000000015.15xCouco%%u %.6s ca %pva?%000000025.5X  %00000012.25d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%00000000015.15xCouco%%u %.6s ca %pva?%000000025.5X  %00000012.25d\n", -245678, "Test2", hello, u, -123456);

	
	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '0VAL.0VAL' -------- FORMATS 'xXd' :", "1st & 2nd 0 ALONE ");
	ft_printf("%015.015xCouco%%u %.6s ca %pva?%025.05X  %012.025d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%015.015xCouco%%u %.6s ca %pva?%025.05X  %012.025d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "1st MULTIS 0      ");
	ft_printf("%00000015.015xCouco%%u %.6s ca %pva?%00000025.05X  %00012.025d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%00000015.015xCouco%%u %.6s ca %pva?%00000025.05X  %00012.025d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "2nd MULTIS 0      ");
	ft_printf("%015.00000015xCouco%%u %.6s ca %pva?%25.0000005X  %012.00025d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%015.00000015xCouco%%u %.6s ca %pva?%025.0000005X  %012.00025d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "1st & 2nd MULTIS 0");
	ft_printf("%00000015.00000015xCouco%%u %.6s ca %pva?%00000025.0000005X  %0012.00025d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%00000015.00000015xCouco%%u %.6s ca %pva?%00000025.0000005X  %0012.00025d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '0.0' -------- FORMATS 'xXd' :", "1st & 2nd 0 ALONE ");
	ft_printf("%0.0xCouco%%u %.0s ca %pva?%0.0X  %0.0d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%0.0xCouco%%u %.0s ca %pva?%0.0X  %0.0d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "1st MULTIS 0      ");
	ft_printf("%000000.0xCouco%%u %.0s ca %pva?%000000.0X  %000.0d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%000000.0xCouco%%u %.0s ca %pva?%000000.0X  %000.0d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "2nd MULTIS 0      ");
	ft_printf("%0.000000xCouco%%u %.0s ca %pva?%0.0000000X  %0.000d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%0.000000xCouco%%u %.0s ca %pva?%0.000000X  %0.000d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "1st & 2nd MULTIS 0");
	ft_printf("%000000.000000xCouco%%u %.0s ca %pva?%000000.000000X  %00.000d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%000000.000000xCouco%%u %.0s ca %pva?%000000.000000X  %00.000d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '0*.*' -------- FORMATS 'xXd' :", "*1 > 0 & *2 > 0");
	ft_printf("%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 12, 12, -245678, 20, 15, "Test2", 25, hello, 12, 25 ,u, 15, 20, -123456);
	fprintf(file2, "%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 12, 12, -245678, 20, 15, "Test2", 25, hello, 12, 25 ,u, 15, 20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 < 0");
	ft_printf("%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", -12, -12, -245678, -20, -15, "Test2", -25, hello, -12,  -25 ,u, -15, -20, -123456);
	fprintf(file2, "%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", -12, -12, -245678, -20, -15, "Test2", -25, hello, -12,  -25 ,u, -15, -20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 > 0 & *2 < 0");
	ft_printf("%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 12, -12, -245678, 20, -15, "Test2", -25, hello, 12,  -25 ,u, 15, -20, -123456);
	fprintf(file2, "%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 12, -12, -245678, 20, -15, "Test2", -25, hello, 12,  -25 ,u, 15, -20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 > 0");
	ft_printf("%0*.*xCouco%%u %0*.*s ca %*pva?%0*.*X  %0*.*d\n", -12, 12, -245678, -20, 15, "Test2", -25, hello, -12,  25 ,u, -15, 20, -123456);
	fprintf(file2, "%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", -12, 12, -245678, -20, 15, "Test2", -25, hello, -12,  25 ,u, -15, 20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 = 0");
	ft_printf("%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 0, 0, -245678, 0, 0, "Test2", 0, hello, 0, 0,u, 0, 0, -123456);
	fprintf(file2, "%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 0, 0, -245678, 0, 0, "Test2", 0, hello, 0, 0,u, 0, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 > 0 & *2 = 0");
	ft_printf("%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 25, 0, -245678, 5, 0, "Test2", 0, hello, 12, 0,u, 1, 0, -123456);
	fprintf(file2, "%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 25, 0, -245678, 5, 0, "Test2", 0, hello, 12, 0,u, 1, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 = 0");
	ft_printf("%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", -25, 0, -245678, -5, 0, "Test2", 0, hello, -12, 0,u, -1, 0, -123456);
	fprintf(file2, "%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", -25, 0, -245678, -5, 0, "Test2", 0, hello, -12, 0,u, -1, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 > 0");
	ft_printf("%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 0, 30, -245678, 0, 25, "Test2", 0, hello, 0, 2, u, 0, 10, -123456);
	fprintf(file2, "%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 0, 30, -245678, 0, 25, "Test2", 0, hello, 0, 2, u, 0, 10, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 < 0");
	ft_printf("%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 0, -30, -245678, 0, -25, "Test2", 0, hello, 0, -2, u, 0, -10, -123456);
	fprintf(file2, "%0*.*xCouco%%u %*.*s ca %*pva?%0*.*X  %0*.*d\n", 0, -30, -245678, 0, -25, "Test2", 0, hello, 0, -2, u, 0, -10, -123456);


	
	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '0.*' -------- FORMATS 'xXd' :", "* > 0");
	ft_printf("%0.*xCouco%%u %.*s ca %*pva?%0.*X  %0.*d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	fprintf(file2, "%0.*xCouco%%u %.*s ca %*pva?%0.*X  %0.*d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("%0.*xCouco%%u %.*s ca %*pva?%0.*X  %0.*d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	fprintf(file2, "%0.*xCouco%%u %.*s ca %*pva?%0.*X  %0.*d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* = 0");
	ft_printf("%0.*xCouco%%u %.*s ca %*pva?%0.*X  %0.*d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0, -123456);
	fprintf(file2, "%0.*xCouco%%u %.*s ca %*pva?%0.*X  %0.*d\n", 0, -245678, 0, "Test2", 0, hello, 0 , u, 0, -123456);

	
	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '0*.' -------- FORMATS 'xXd' :", "* > 0");
	ft_printf("%0*.xCouco%%u %.*s ca %*pva?%0*.X  %0*.d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	fprintf(file2, "%0*.xCouco%%u %.*s ca %*pva?%0*.X  %0*.d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("%0*.xCouco%%u %.*s ca %*pva?%0*.X  %0*.d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	fprintf(file2, "%0*.xCouco%%u %.*s ca %*pva?%0*.X  %0*.d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* = 0");
	ft_printf("%0*.xCouco%%u %.*s ca %*pva?%0*.X  %0*.d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0, -123456);
	fprintf(file2, "%0*.xCouco%%u %.*s ca %*pva?%0*.X  %0*.d\n", 0, -245678, 0, "Test2", 0, hello, 0 , u, 0, -123456);	
	
	
	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '0*.0VAL' -------- FORMATS 'xXd' :", "* > 0");
	ft_printf("%0*.025xCouco%%u %.*s ca %*pva?%0*.030X  %0*.05d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	fprintf(file2, "%0*.025xCouco%%u %.*s ca %*pva?%0*.030X  %0*.05d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("%0*.025xCouco%%u %.*s ca %*pva?%0*.030X  %0*.05d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	fprintf(file2, "%0*.025xCouco%%u %.*s ca %*pva?%0*.030X  %0*.05d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* = 0");
	ft_printf("%0*.025xCouco%%u %.*s ca %*pva?%0*.030X  %0*.05d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0, -123456);
	fprintf(file2, "%0*.025xCouco%%u %.*s ca %*pva?%0*.030X  %0*.05d\n", 0, -245678, 0, "Test2", 0, hello, 0 , u, 0, -123456);	
	

	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-.VAL' -------- FORMATS 'xXd' :", "- ALONE ");
	ft_printf("%-.15xCouco%%u %.6s ca %pva?%-.25X  %-.12d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%-.15xCouco%%u %.6s ca %pva?%-.25X  %-.12d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "MULTIS -");
	ft_printf("%------.15xCouco%%u %.6s ca %pva?%---.25X  %------.12d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%------.15xCouco%%u %.6s ca %pva?%---.25X  %-------.12d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-VAL.' -------- FORMATS 'xXd' :   ", (void*)0);
	ft_printf("%-15.xCouco%%u %.6s ca %pva?%-25.X  %-12.d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%-15.xCouco%%u %.6s ca %pva?%-25.X  %-12.d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-.' -------- FORMATS 'xXd' :      ", (void*)0);
	ft_printf("%-.xCouco%%u %.s ca %pva?%-.X  %-.d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%-.xCouco%%u %.s ca %pva?%-.X  %-.d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-VAL.VAL' -------- FORMATS 'xXd' :", "- ALONE ");
	ft_printf("%-15.15xCouco%%u %.6s ca %pva?%-25.5X  %-12.25d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%-15.15xCouco%%u %.6s ca %pva?%-25.5X  %-12.25d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "MULTIS -");
	ft_printf("%-------15.15xCouco%%u %.6s ca %pva?%-------25.5X  %--------12.25d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%-------.15xCouco%%u %.6s ca %pva?%-------25.5X  %-------12.25d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-VAL.0VAL' -------- FORMATS 'xXd' :", "- ALONE & 0 ALONE  ");
	ft_printf("%-15.015xCouco%%u %.6s ca %pva?%-25.05X  %-12.025d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%-15.015xCouco%%u %.6s ca %pva?%-25.05X  %-12.025d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "MULTIS - & 0 ALONE ");
	ft_printf("%-------15.015xCouco%%u %.6s ca %pva?%-------25.05X  %--------12.025d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%-------.015xCouco%%u %.6s ca %pva?%-------25.05X  %-------12.025d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "- ALONE & MULTIS 0 ");
	ft_printf("%-15.000015xCouco%%u %.6s ca %pva?%-25.00005X  %-12.000025d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%-.000015xCouco%%u %.6s ca %pva?%-25.00005X  %-12.000025d\n", -245678, "Test2", hello, u, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "MULTIS - & MULTIS 0");
	ft_printf("%-------15.000015xCouco%%u %.6s ca %pva?%-------25.00005X  %--------12.000025d\n", -245678, "Test2", hello, u, -123456);
	fprintf(file2, "%-------.000015xCouco%%u %.6s ca %pva?%-------25.00005X  %-------12.000025d\n", -245678, "Test2", hello, u, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-.*' -------- FORMATS 'xXd' :", "* > 0");
	ft_printf("%-.*xCouco%%u %.*s ca %*pva?%-.*X  %-.*d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	fprintf(file2, "%-.*xCouco%%u %.*s ca %*pva?%-.*X  %-.*d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("%-.*xCouco%%u %.*s ca %*pva?%-.*X  %-.*d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	fprintf(file2, "%-.*xCouco%%u %.*s ca %*pva?%-.*X  %-.*d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* = 0");
	ft_printf("%-.*xCouco%%u %.*s ca %*pva?%-.*X  %-.*d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0, -123456);
	fprintf(file2, "%-.*xCouco%%u %.*s ca %*pva?%-.*X  %-.*d\n", 0, -245678, 0, "Test2", 0, hello, 0 , u, 0, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-*.' -------- FORMATS 'xXd' :", "* > 0");
	ft_printf("%-*.xCouco%%u %.*s ca %*pva?%-*.X  %-*.d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	fprintf(file2, "%-*.xCouco%%u %.*s ca %*pva?%-*.X  %-*.d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("%-*.xCouco%%u %.*s ca %*pva?%-*.X  %-*.d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	fprintf(file2, "%-*.xCouco%%u %.*s ca %*pva?%-*.X  %-*.d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* = 0");
	ft_printf("%-*.xCouco%%u %.*s ca %*pva?%-*.X  %-*.d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0, -123456);
	fprintf(file2, "%-*.xCouco%%u %.*s ca %*pva?%-*.X  %-*.d\n", 0, -245678, 0, "Test2", 0, hello, 0 , u, 0, -123456);


	//SOMETHING WENT WRONG
	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-*.*' -------- FORMATS 'xXd' :", "*1 > 0 & *2 > 0");
	ft_printf("%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 12, 12, -245678, 20, 15, "Test2", 25, hello, 12, 25 ,u, 15, 20, -123456);
	fprintf(file2, "%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 12, 12, -245678, 20, 15, "Test2", 25, hello, 12, 25 ,u, 15, 20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 < 0");
	ft_printf("%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", -12, -12, -245678, -20, -15, "Test2", -25, hello, -12,  -25 ,u, -15, -20, -123456);
	fprintf(file2, "%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", -12, -12, -245678, -20, -15, "Test2", -25, hello, -12,  -25 ,u, -15, -20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 > 0 & *2 < 0");
	ft_printf("%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 12, -12, -245678, 20, -15, "Test2", -25, hello, 12,  -25 ,u, 15, -20, -123456);
	fprintf(file2, "%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 12, -12, -245678, 20, -15, "Test2", -25, hello, 12,  -25 ,u, 15, -20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 > 0");
	ft_printf("%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", -12, 12, -245678, -20, 15, "Test2", -25, hello, -12,  25 ,u, -15, 20, -123456);
	fprintf(file2, "%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", -12, 12, -245678, -20, 15, "Test2", -25, hello, -12,  25 ,u, -15, 20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 = 0");
	ft_printf("%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 0, 0, -245678, 0, 0, "Test2", 0, hello, 0, 0,u, 0, 0, -123456);
	fprintf(file2, "%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 0, 0, -245678, 0, 0, "Test2", 0, hello, 0, 0,u, 0, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 > 0 & *2 = 0");
	ft_printf("%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 25, 0, -245678, 5, 0, "Test2", 0, hello, 12, 0,u, 1, 0, -123456);
	fprintf(file2, "%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 25, 0, -245678, 5, 0, "Test2", 0, hello, 12, 0,u, 1, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 = 0");
	ft_printf("%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", -25, 0, -245678, -5, 0, "Test2", 0, hello, -12, 0,u, -1, 0, -123456);
	fprintf(file2, "%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", -25, 0, -245678, -5, 0, "Test2", 0, hello, -12, 0,u, -1, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 > 0");
	ft_printf("%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 0, 30, -245678, 0, 25, "Test2", 0, hello, 0, 2, u, 0, 10, -123456);
	fprintf(file2, "%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 0, 30, -245678, 0, 25, "Test2", 0, hello, 0, 2, u, 0, 10, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 < 0");
	ft_printf("%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 0, -30, -245678, 0, -25, "Test2", 0, hello, 0, -2, u, 0, -10, -123456);
	fprintf(file2, "%-*.*xCouco%%u %*.*s ca %*pva?%-*.*X  %-*.*d\n", 0, -30, -245678, 0, -25, "Test2", 0, hello, 0, -2, u, 0, -10, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-*.*' -------- FORMATS 'xXd' ------- MULTIS '-' :", "*1 > 0 & *2 > 0");
	ft_printf("%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 12, 12, -245678, 20, 15, "Test2", 25, hello, 12, 25 ,u, 15, 20, -123456);
	fprintf(file2, "%------*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 12, 12, -245678, 20, 15, "Test2", 25, hello, 12, 25 ,u, 15, 20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 < 0");
	ft_printf("%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", -12, -12, -245678, -20, -15, "Test2", -25, hello, -12,  -25 ,u, -15, -20, -123456);
	fprintf(file2, "%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", -12, -12, -245678, -20, -15, "Test2", -25, hello, -12,  -25 ,u, -15, -20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 > 0 & *2 < 0");
	ft_printf("%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 12, -12, -245678, 20, -15, "Test2", -25, hello, 12,  -25 ,u, 15, -20, -123456);
	fprintf(file2, "%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 12, -12, -245678, 20, -15, "Test2", -25, hello, 12,  -25 ,u, 15, -20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 > 0");
	ft_printf("%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", -12, 12, -245678, -20, 15, "Test2", -25, hello, -12,  25 ,u, -15, 20, -123456);
	fprintf(file2, "%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", -12, 12, -245678, -20, 15, "Test2", -25, hello, -12,  25 ,u, -15, 20, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 = 0");
	ft_printf("%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 0, 0, -245678, 0, 0, "Test2", 0, hello, 0, 0,u, 0, 0, -123456);
	fprintf(file2, "%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 0, 0, -245678, 0, 0, "Test2", 0, hello, 0, 0,u, 0, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 > 0 & *2 = 0");
	ft_printf("%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 25, 0, -245678, 5, 0, "Test2", 0, hello, 12, 0,u, 1, 0, -123456);
	fprintf(file2, "%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 25, 0, -245678, 5, 0, "Test2", 0, hello, 12, 0,u, 1, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 < 0 & *2 = 0");
	ft_printf("%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", -25, 0, -245678, -5, 0, "Test2", 0, hello, -12, 0,u, -1, 0, -123456);
	fprintf(file2, "%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", -25, 0, -245678, -5, 0, "Test2", 0, hello, -12, 0,u, -1, 0, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 > 0");
	ft_printf("%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 0, 30, -245678, 0, 25, "Test2", 0, hello, 0, 2, u, 0, 10, -123456);
	fprintf(file2, "%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 0, 30, -245678, 0, 25, "Test2", 0, hello, 0, 2, u, 0, 10, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "*1 = 0 & *2 < 0");
	ft_printf("%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 0, -30, -245678, 0, -25, "Test2", 0, hello, 0, -2, u, 0, -10, -123456);
	fprintf(file2, "%-----*.*xCouco%%u %*.*s ca %*pva?%-----*.*X  %-----*.*d\n", 0, -30, -245678, 0, -25, "Test2", 0, hello, 0, -2, u, 0, -10, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-*.VAL' -------- FORMATS 'xXd' :", "* > 0");
	ft_printf("%-*.15xCouco%%u %.*s ca %*pva?%-*.30X  %-*.12d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	fprintf(file2, "%-*.15xCouco%%u %.*s ca %*pva?%-*.30X  %-*.12d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("%-*.15xCouco%%u %.*s ca %*pva?%-*.30X  %-*.12d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	fprintf(file2, "%-*.15xCouco%%u %.*s ca %*pva?%-*.30X  %-*.12d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* = 0");
	ft_printf("%-*.15xCouco%%u %.*s ca %*pva?%-*.30X  %-*.12d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0, -123456);
	fprintf(file2, "%-*.15xCouco%%u %.*s ca %*pva?%-*.30X  %-*.12d\n", 0, -245678, 0, "Test2", 0, hello, 0 , u, 0, -123456);	


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-*.0VAL' -------- FORMATS 'xXd' :", "* > 0");
	ft_printf("%-*.015xCouco%%u %.*s ca %*pva?%-*.030X  %-*.012d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	fprintf(file2, "%-*.015xCouco%%u %.*s ca %*pva?%-*.030X  %-*.012d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("%-*.015xCouco%%u %.*s ca %*pva?%-*.030X  %-*.012d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	fprintf(file2, "%-*.015xCouco%%u %.*s ca %*pva?%-*.030X  %-*.012d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* = 0");
	ft_printf("%-*.015xCouco%%u %.*s ca %*pva?%-*.030X  %-*.012d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0, -123456);
	fprintf(file2, "%-*.015xCouco%%u %.*s ca %*pva?%-*.030X  %-*.012d\n", 0, -245678, 0, "Test2", 0, hello, 0 , u, 0, -123456);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS '-VAL.*' -------- FORMATS 'xXd' :", "* > 0");
	ft_printf("%-15.*xCouco%%u %.*s ca %*pva?%-30.*X  %-*.12d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	fprintf(file2, "%-15.*xCouco%%u %.*s ca %*pva?%-30.*X  %-12.*d\n", 25, -245678, 20, "Test2", 25, hello, 25 ,u, 12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("%-15.*xCouco%%u %.*s ca %*pva?%-30.*X  %-12.*d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	fprintf(file2, "%-15.*xCouco%%u %.*s ca %*pva?%-30.*X  %-12.*d\n", -25, -245678, -20, "Test2", -25, hello, -25 ,u, -12, -123456);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* = 0");
	ft_printf("%-15.*xCouco%%u %.*s ca %*pva?%-30.*X  %-12.*d\n", 0, -245678, 0, "Test2", 0, hello, 0, u, 0, -123456);
	fprintf(file2, "%-15.*xCouco%%u %.*s ca %*pva?%-30.*X  %-12.*d\n", 0, -245678, 0, "Test2", 0, hello, 0 , u, 0, -123456);	


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS multiples'-' -------- FORMATS 'd' :", (void*)0);
	ft_printf("COUCOU%-----*d C'EST MOI QUI%--*.*d TE DIT %--30.*dCOUCOU\n", 25, -256, 15, 30, -256, 15,-256);
	fprintf(file2, "COUCOU%-----*d C'EST MOI QUI%--*.*d TE DIT %--30.*dCOUCOU\n", 25, -256, 15, 30, -256, 15,-256);
	

	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAGS multiples'0' -------- FORMATS 'd' :", (void*)0);
	ft_printf("COUCOU%00000*d C'EST MOI QUI%00*.*d TE DIT %0030.*dCOUCOU\n", 25, -256, 15, 30, -256, 15,-256);
	fprintf(file2, "COUCOU%00000*d C'EST MOI QUI%00*.*d TE DIT %0030.*dCOUCOU\n", 25, -256, 15, 30, -256, 15,-256);
	

	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '.0' -------- FORMATS 'd' :", "d = 0");
	ft_printf("%.0d COUCOU %.0d RECOUCOU %.d  RERECOUCOU %.*d\n", -245678, 0, 0, -0, -256);
	fprintf(file2, "%.0d COUCOU %.0d RECOUCOU %.d  RERECOUCOU %.*d\n", -245678, 0, 0, -0, -256);
	

	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '-0' -------- FORMATS 'd' :", "d = 0");
	ft_printf("%-0d COUCOU %-0d RECOUCOU %-d  RERECOUCOU %-*d\n", -245678, 0, 0, -0, -256);
	fprintf(file2, "%-*d COUCOU %-*d RECOUCOU %-d  RERECOUCOU %-*d\n", 0, -245678, 0, 0, 0, -0, -256);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG 'VAL' -------- FORMATS '%c' :       ", (void*)0);
	ft_printf("COUCOU %25c RECOUCOU %15% HELLO\n", 'X');
	fprintf(file2, "COUCOU %25c RECOUCOU %15% HELLO\n", 'X');


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '*' -------- FORMATS '%c' :       ", "* > 0");
	ft_printf("COUCOU %*c RECOUCOU %*% HELLO\n", 25, 'X', 15);
	fprintf(file2, "COUCOU %*c RECOUCOU %*% HELLO\n", 25, 'X', 15);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("COUCOU %*c RECOUCOU %*% HELLO\n", -25, 'X', -15);
	fprintf(file2, "COUCOU %*c RECOUCOU %*% HELLO\n", -25, 'X', -15);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '-' -------- FORMATS '%c' :       ", "- ALONE ");
	ft_printf("COUCOU %-c RECOUCOU %-% HELLO\n", 'X');
	fprintf(file2, "COUCOU %-c RECOUCOU %-% HELLO\n", 'X');
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "MULTIS -");
	ft_printf("COUCOU %------c RECOUCOU %----% HELLO\n", 'X');
	fprintf(file2, "COUCOU %------c RECOUCOU %----% HELLO\n", 'X');


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '-VAL' -------- FORMATS '%c' :       ", "- ALONE ");
	ft_printf("COUCOU %-25c RECOUCOU %-15% HELLO\n", 'X');
	fprintf(file2, "COUCOU %-25c RECOUCOU %-15% HELLO\n", 'X');
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "MULTIS -");
	ft_printf("COUCOU %------25c RECOUCOU %----15% HELLO\n", 'X');
	fprintf(file2, "COUCOU %------25c RECOUCOU %----15% HELLO\n", 'X');


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '-*' -------- FORMATS '%c' :       ", "* > 0");
	ft_printf("COUCOU %-*c RECOUCOU %-*% HELLO\n", 25, 'X', 15);
	fprintf(file2, "COUCOU %-*c RECOUCOU %-*% HELLO\n", 25, 'X', 15);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("COUCOU %-*c RECOUCOU %-*% HELLO\n", -25, 'X', -15);
	fprintf(file2, "COUCOU %-*c RECOUCOU %-*% HELLO\n", -25, 'X', -15);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '.' -------- FORMATS '%c' :         ", (void*)0);
	ft_printf("COUCOU %.c RECOUCOU %.% HELLO\n", 'X');
	fprintf(file2, "COUCOU %.c RECOUCOU %.% HELLO\n", 'X');


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG 'VAL.' -------- FORMATS '%c' :      ", (void*)0);
	ft_printf("COUCOU %25.c RECOUCOU %15.% HELLO\n", 'X');
	fprintf(file2, "COUCOU %25.c RECOUCOU %15.% HELLO\n", 'X');


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '*.' -------- FORMATS '%c' :       ", "* > 0");
	ft_printf("COUCOU %*.c RECOUCOU %*.% HELLO\n", 25, 'X', 15);
	fprintf(file2, "COUCOU %*.c RECOUCOU %*.% HELLO\n", 25, 'X', 15);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* < 0");
	ft_printf("COUCOU %*.c RECOUCOU %*.% HELLO\n", -25, 'X', -15);
	fprintf(file2, "COUCOU %*.c RECOUCOU %*.% HELLO\n", -25, 'X', -15);


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '-.' -------- FORMATS '%c' :       ", "- ALONE ");
	ft_printf("COUCOU %-.c RECOUCOU %-.% HELLO\n", 'X');
	fprintf(file2, "COUCOU %-.c RECOUCOU %-.% HELLO\n", 'X');
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "MULTIS -");
	ft_printf("COUCOU %------.c RECOUCOU %----.% HELLO\n", 'X');
	fprintf(file2, "COUCOU %------.c RECOUCOU %----.% HELLO\n", 'X');


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '-VAL.' -------- FORMATS '%c' :       ", "- ALONE ");
	ft_printf("COUCOU %-25.c RECOUCOU %-15.% HELLO\n", 'X');
	fprintf(file2, "COUCOU %-25.c RECOUCOU %-15.% HELLO\n", 'X');
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "MULTIS -");
	ft_printf("COUCOU %------25.c RECOUCOU %----15.% HELLO\n", 'X');
	fprintf(file2, "COUCOU %------25.c RECOUCOU %----15.% HELLO\n", 'X');


	compare_files(&file1, &file2, &dpl, &fd, "TEST : FLAG '-*.' -------- FORMATS '%c' :       ", "* > 0 & - ALONE ");
	ft_printf("COUCOU %-*.c RECOUCOU %-*.% HELLO\n", 25, 'X', 15);
	fprintf(file2, "COUCOU %-*.c RECOUCOU %-*.% HELLO\n", 25, 'X', 15);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* > 0 & - ALONE ");
	ft_printf("COUCOU %-*.c RECOUCOU %-*.% HELLO\n", -25, 'X', -15);
	fprintf(file2, "COUCOU %-*.c RECOUCOU %-*.% HELLO\n", -25, 'X', -15);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* > 0 & MULTIS -");
	ft_printf("COUCOU %-----*.c RECOUCOU %----*.% HELLO\n", 25, 'X', 15);
	fprintf(file2, "COUCOU %------*.c RECOUCOU %----*.% HELLO\n", 25, 'X', 15);
	compare_files(&file1, &file2, &dpl, &fd, (void*)0, "* > 0 & MULTIS -");
	ft_printf("COUCOU %-----*.c RECOUCOU %----*.% HELLO\n", -25, 'X', -15);
	fprintf(file2, "COUCOU %-----*.c RECOUCOU %----*.% HELLO\n", -25, 'X', -15);

	compare_files(&file1, &file2, &dpl, &fd, "TEST : NO FLAGS -------- FORMATS 's' = null :   ", (void*)0);
	ft_printf("COUCOU %s comment vas-tu en cette %s journée? Il fait %s", (void*)0, "horrible", (void*)0);
	fprintf(file2, "COUCOU %s comment vas-tu en cette %s journée? Il fait %s", (void*)0, "horrible", (void*)0);

	compare_files(&file1, &file2, &dpl, &fd, (void*)0, (void*)0);
	
	close(fd);
	dup2(dpl, 1);
	close(dpl);
	fclose(file1);
	fclose(file2);
	}
}
