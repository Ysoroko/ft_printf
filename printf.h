/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:08:21 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/05 15:29:19 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

//TO DELETE BEFORE SUBMITTING
#include <stdio.h>

#include <stdarg.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_str_with_flags_list
{
	char							*definer_str;
	//Malloc'd: before_point + after_point;
	char							*before_dot;
	char							*after_dot;
	
	char							*minus_flag;
	char							*star_before_point;
	int								zero_flag;
	char							*point_flag;
	int								precision;
	int								width;
	char							*star_after_point;
	char							type_flag;
	char							*text_to_print;
}				t_list;

# define FD 1
# define TYPE_CHARS "cspdiuxX%"
# define ACCEPTED_CHARS "0123456789cspdiuxX%.-*"

int		ft_printf(const char *str, ...);
t_list	*ft_analyze_first_printf_argument(const char *str, va_list *v_list);

/*
** Functions used for processing the components in t_list (= flags data)
*/
int		ft_process_list(t_list *list, va_list *v_list);
int		ft_atoi_p(const char *str);

/*
** Functions used in manipulations of t_lists (creating, reading etc.)
*/
t_list	*ft_lstnew(void);

/*
** Printf Utils
*/
char	*ft_char_alloc(int n_chars, char c);
int		ft_str_has_char_from_charset(char *str, char *charset);
int		ft_str_has_other_chars(char *str, char *charset);
int		ft_number_of_c_char_in_str(char *str, char c);
int		ft_too_many_flag_chars_in_str(char *all, char *bef, char *aft);

/*
** Printf Utils 2
*/
int		ft_wrong_order_of_flags(char *before_dot, char *after_dot);

/*
** Libft functions
*/
int		ft_isdigit(int c);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

//TO DELETE
void	ft_print_t_list(t_list *list);

#endif