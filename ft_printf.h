/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysoroko <ysoroko@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:08:21 by ysoroko           #+#    #+#             */
/*   Updated: 2021/01/15 19:13:24 by ysoroko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct	s_str_with_flags_list
{
	char				*definer_str;
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

# ifndef FD
#  define FD 1
# endif

# ifndef TYPE_CHARS
#  define TYPE_CHARS "cspdiuxX%"
# endif

# ifndef ACCEPTED_CHARS
#  define ACCEPTED_CHARS "0123456789cspdiuxX%.-*"
# endif

# ifndef BASE_10
#  define BASE_10 "0123456789"
# endif

# ifndef BASE_LX
#  define BASE_LX "0123456789abcdef"
# endif

# ifndef BASE_UX
#  define BASE_UX "0123456789ABCDEF"
# endif

/*
** Main Printf Functions
*/

int				ft_printf(const char *str, ...);
int				ft_process_list(t_list *list, va_list *v_list);
int				ft_analyze_first_arg(const char *str, va_list *v_list);

/*
** Error Checking Functions
*/

void			ft_check_flags_for_special_combo(t_list *list);

/*
** Libft Utils
*/

int				ft_isdigit(int c);
char			*ft_strchr(const char *str, int c);
size_t			ft_strlen(const char *str);
void			ft_putstr_fd(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
char			*ft_itoa(int n);
char			*ft_strdup(const char *src);
char			*ft_strjoin(char const *pref, char const *suff);
char			*ft_uitoa_base(unsigned int n, char *base);
char			*ft_ultoa_base(unsigned long n, char *base);
int				ft_strcmp(char *s1, char *s2);
int				ft_count_n_digits(char *str);

/*
** Next Arg To Str Functions
*/

char			*ft_c_to_str(va_list *v_l);
char			*ft_percent_to_str(void);
char			*ft_s_to_str(va_list *v_l, t_list *list);
char			*ft_p_to_str(va_list *v_l, t_list *list);
char			*ft_d_or_i_to_str(va_list *v_l, t_list *list);
char			*ft_u_to_str(va_list *v_l, t_list *list);
char			*ft_lowercase_x_to_str(va_list *v_l, t_list *list);
char			*ft_uppercase_x_to_str(va_list *v_l, t_list *list);
char			*ft_minus_flag(char *w_str, char *p_str, t_list *list);
char			*ft_width_and_zero_to_str(t_list *list);
char			*ft_precision_to_str(char *str_to_format, t_list *list);
char			*ft_precision_s_type_to_str(char *str_to_format, t_list *list);
char			*ft_width_prec_zero_minus(char *str, t_list *list);

/*
** Ft_printf Utils
*/

char			*ft_char_alloc(int n_chars, char c);
int				ft_str_has_other_chars(char *str, char *charset);
int				ft_number_of_c_char_in_str(char *str, char c);
int				ft_atoi_p(const char *str);
t_list			*ft_lstnew(void);
int				ft_free(char **ptr1, char **ptr2, t_list **list);
char			*ft_replace_alloc(char **str_to_replace, char *replace_by);
void			ft_check_if_zero_flag_is_ignored(t_list *list);

#endif
