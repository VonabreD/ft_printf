//
// Created by Evgeniy Derbanov on 7/14/17.
//

#ifndef FT_PRINTF_FT_PRINTF_H
#define FT_PRINTF_FT_PRINTF_H

#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>

typedef struct s_arg{
	char sym;
	char spec;
	int pad_zeros;
	int space;
	int plus;
	int right_al;
	int prec;
	int convert;
	int len;
	int width;
} t_arg;

int ft_ret_big(int a, int b, int c);
int	ft_isalpha(int ch);
int	ft_isdigit(int ch);
void	ft_putchar(char c);
void	ft_putstr(char const *s, int prec);
size_t	ft_strlen(const char *s);
int	ft_atoi(const char *str);
int ft_proc_p(t_arg *params, void *a);
int ft_parce_flags(char *str, t_arg *params, int *pos);
int ft_parce_width(char *str, t_arg *params, int *cur_pos);
int ft_parce_prec(char *str, t_arg *params, int *cur_pos);
int ft_parce_len(char *str, t_arg *params, int *cur_pos);
int ft_parse(char *str, t_arg *params);


int	ft_find_spec(char *str, t_arg *params);
int ft_chk_flags(char c, char p, t_arg *params);
void ft_clear_list(t_arg *params);
int ft_fprintf(const char *format, va_list *args);
int ft_printf(const char *format, ...);
/* *************************************************** */

void ft_put_n_sym(char *sym, int num);
int ft_proc_str(t_arg *params, char *str);
int ft_proc_c(t_arg *params, char c);
int ft_int_len (uintmax_t num, int prec);
void ft_putnbr_long(long long int num, int prec);
int	ft_data_proc(t_arg *params, va_list *args);

int	ft_data_proc_h(t_arg *params, va_list *args);
int ft_hproc_hex(t_arg *params, int i);
int ft_hproc_oct(t_arg *params, int i);
int ft_hproc_int(t_arg *params, int i);
long int ft_hproc_types(int i, t_arg *params);

int ft_pr_in_f(t_arg *params, long int num, char zn);
int ft_pr_in_s(t_arg *params, long int num, char zn);
int ft_hproc_int(t_arg *params, int i);
int ft_hproc_oct(t_arg *params, int i);
int ft_proc_int(t_arg *params, int i);
int ft_pr_oct_s(t_arg *params, char *str);
int ft_pr_oct_f(t_arg *params, char *str);
char *ft_convert(uintmax_t num, int base, int prec);
int ft_proc_oct(t_arg *params, int i);
int ft_pr_hex_s(t_arg *params, char *str);
int ft_pr_hex_f(t_arg *params, char *str);
char *ft_upcase(char *str);
int ft_proc_hex(t_arg *params, int i);
int	ft_data_proc_o(t_arg *params, va_list *args);

int	ft_data_proc_hh(t_arg *params, va_list *args);
int ft_hhproc_hex(t_arg *params, int i);
int ft_hhproc_oct(t_arg *params, int i);
int ft_hhproc_int(t_arg *params, int i);
long int ft_hhproc_types(int i, t_arg *params);

void ft_putlstr(wchar_t *str);
int ft_strlen_l(wchar_t *str);
int ft_proc_lstr(t_arg *params, wchar_t *str);
int ft_count_bits(wchar_t c);
int ft_putlchar(wchar_t sym);
int ft_proc_lc(t_arg *params, wchar_t c);
uintmax_t ft_lproc_types(intmax_t i, t_arg *params);
void ft_lputnbr_long(uintmax_t num);
int ft_lpr_in_f(t_arg *params, long int num, char zn);
int ft_lpr_in_s(t_arg *params, uintmax_t num, char zn);
int ft_lproc_int(t_arg *params, intmax_t i);
int ft_lproc_oct(t_arg *params, uintmax_t i);
int ft_lproc_hex(t_arg *params, uintmax_t i);
int	ft_data_proc_l(t_arg *params, va_list *args);


#endif //FT_PRINTF_FT_PRINTF_H
