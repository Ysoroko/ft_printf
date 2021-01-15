/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:08:21 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/15 16:06:50 by ysoroko          ###   ########.fr       */
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
	char				*definer_str;
	//Malloc'd: before_point;
	char				*before_dot;
	char				*after_dot;
	char				*minus_flag;
	char				*star_before_point;
	int					zero_flag;
	int					precision;
	int					width;
	char				*star_after_point;
	char				type_flag;
	int					chars_printed;
	char				*text_to_print;
}				t_list;

# define FD 1
# define TYPE_CHARS "cspdiuxX%"
# define ACCEPTED_CHARS "0123456789cspdiuxX%.-*"
# define BASE_10 "0123456789"
# define BASE_LX "0123456789abcdef"
# define BASE_UX "0123456789ABCDEF"

int		ft_printf(const char *str, ...);

/*
** Main Printf Functions
*/

int		ft_process_list(t_list *list, va_list *v_list);
int		ft_analyze_first_printf_argument(const char *str, va_list *v_list);

/*
** Error Checking Functions
*/

int		ft_wrong_order_of_flags(char *before_dot, char *after_dot);
int		ft_check_for_errors(t_list *list);
int		ft_too_many_flag_chars_in_str(char *all, char *bef, char *aft);
void	ft_check_flags_for_special_combo(t_list *list);

/*
** Libft Utils
*/

int		ft_isdigit(int c);
char	*ft_strchr(const char *str, int c);
size_t	ft_strlen(const char *str);
void	ft_putstr_fd(char *s, int fd);
void	ft_putchar_fd(char c, int fd);

char	*ft_itoa(int n);
char	*ft_strdup(const char *src);
char	*ft_strjoin(char const *pref, char const *suff);
char	*ft_uitoa_base(unsigned int n, char *base);
char	*ft_ultoa_base(unsigned long n, char *base);

int		ft_strcmp(char *s1, char *s2);
int		ft_count_n_digits(char *str);

/*
** Next Arg To Str Functions
*/

char	*ft_c_type_next_arg_to_str(va_list *v_l);
char	*ft_percent_type_next_arg_to_str(void);
char	*ft_s_type_next_arg_to_str(va_list *v_l, t_list *list);
char	*ft_p_type_next_arg_to_str(va_list *v_l, t_list *list);

char	*ft_d_or_i_type_next_arg_to_str(va_list *v_l, t_list *list);
char	*ft_u_type_next_arg_to_str(va_list *v_l, t_list *list);
char	*ft_lowercase_x_type_next_arg_to_str(va_list *v_l, t_list *list);
char	*ft_uppercase_x_type_next_arg_to_str(va_list *v_l, t_list *list);

char	*ft_process_minus_flag(char *str_rec, char *str_to_insert, t_list *list);
char	*ft_width_and_zero_to_str(t_list *list);
char	*ft_precision_to_str(char *str_to_format, t_list *list);
char	*ft_precision_s_type_to_str(char *str_to_format, t_list *list);
char	*ft_width_prec_zero_minus(char *str, t_list *list);

/*
** Printf Utils
*/

char	*ft_char_alloc(int n_chars, char c);
int		ft_str_has_other_chars(char *str, char *charset);
int		ft_number_of_c_char_in_str(char *str, char c);
int		ft_atoi_p(const char *str);
t_list	*ft_lstnew(void);
int		ft_free(char **ptr1, char **ptr2, t_list **list);
char	*ft_replace_alloc(char **str_to_replace, char *replace_by);


//TO DELETE
void	ft_print_t_list(t_list *list);

#endif