/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:08:21 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/02 17:13:58 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

//TO DELETE
#include <stdio.h>

#include <stdarg.h>
#include <stdlib.h>

typedef struct	s_str_with_flags_list
{
	char							*definer_str;
	//Malloc'd: before_point + after_point;
	char							*before_point;
	char							*after_point;
	
	char							*minus_flag;
	char							*star_before_point;
	int								zero_flag;
	char							*point_flag;
	int								precision_flag;
	int								width_flag;
	char							*star_after_point;
	char							type_flag;
	char							*text_to_print;
	char							*error;
}				t_list;

# define FD 1

int		ft_printf(const char *str, ...);
t_list	*ft_analyze_first_printf_argument(const char *str, va_list *v_list);

/*
** Functions used for processing the components in t_list (= flags data)
*/
int		ft_process_list(t_list *list, va_list *v_list);

/*
** Functions used in manipulations of t_lists (creating, reading etc.)
*/
t_list	*ft_lstnew(void);

/*
** Libft functions
*/
int		ft_isdigit(int c);
char	*ft_strchr(const char *str, int c);
int		ft_atoi_p(const char *str);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

#endif