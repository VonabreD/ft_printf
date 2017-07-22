/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_proc_o.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 15:57:13 by ederbano          #+#    #+#             */
/*   Updated: 2017/07/10 15:57:14 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_pr_in_f(t_arg *params, long int num, char zn)
{
	if (zn != '\0')
		ft_putchar(zn);
	if (params->prec >= 0)
		ft_put_n_sym("0", params->prec - ft_int_len(num, params->prec));
	ft_putnbr_long(num, params->prec);
	if (params->prec > ft_int_len(num, params->prec))
		ft_put_n_sym(" ", params->width - params->prec);
	else
		ft_put_n_sym(" ", params->width - ft_int_len(num, params->prec));
	return (0);
}

int ft_pr_in_s(t_arg *params, long int num, char zn)
{
	if (params->pad_zeros == 1 && params->prec < 0)
	{
		if (zn != '\0')
			ft_putchar(zn);
		ft_put_n_sym("0", params->width - ft_int_len(num, params->prec));
		ft_putnbr_long(num, params->prec);
	}
	else if (params->prec >= 0)
	{
		if (params->prec > ft_int_len(num, params->prec))
			ft_put_n_sym(" ", params->width - params->prec);
		else
			ft_put_n_sym(" ", params->width - ft_int_len(num, params->prec));
		if (zn != '\0')
			ft_putchar(zn);
		ft_put_n_sym("0", params->prec - ft_int_len(num, params->prec));
		ft_putnbr_long(num, params->prec);
	}
	else
	{
		ft_put_n_sym(" ", params->width - ft_int_len(num, params->prec));
		if (zn != '\0')
			ft_putchar(zn);
		ft_putnbr_long(num, params->prec);
	}
	return (0);
}

int ft_proc_int(t_arg *params, int i)
{
	char zn;
	long long int num;

	num = (long long int)i;
	if (params->spec == 'u' && i < 0)
		num = 4294967296 + i;
	zn = '\0';
	if (params->space == 1 && params->spec != 'u')
		zn = ' ';
	if (params->plus == 1 && params->spec != 'u')
		zn = '+';
	if (num < 0 && params->spec != 'u')
	{
		zn = '-';
		num = -num;
	}
	if (zn != '\0' && params->spec != 'u')
		params->width -=1;
	if (params->right_al == 1)
		ft_pr_in_f(params, num, zn);
	else
		ft_pr_in_s(params, num, zn);
	if (zn != '\0')
		return (ft_ret_big(params->width, params->prec, ft_int_len(num, params->prec)) + 1);
	return (ft_ret_big(params->width, params->prec, ft_int_len(num, params->prec)));
}

int ft_pr_oct_s(t_arg *params, char *str)
{

	char sym;

	if (params->pad_zeros == 1)
		sym = '0';
	else
		sym = ' ';
	if (params->prec < 0)
	{
		ft_put_n_sym(&sym, params->width - (int)ft_strlen(str));
		if (params->convert == 1)
			ft_putchar('0');
		ft_putstr(str, (int) ft_strlen(str));
	}
	else
	{
		if ((size_t)params->prec > ft_strlen(str))
			ft_put_n_sym(" ", params->width - params->prec);
		else
			ft_put_n_sym(" ", params->width - (int)ft_strlen(str));
		if (params->convert == 1 && params->prec <= 1)
			ft_putchar('0');
		ft_put_n_sym("0", params->prec - ft_strlen(str));
		ft_putstr(str, (int) ft_strlen(str));
	}
	return (0);
}

int ft_pr_oct_f(t_arg *params, char *str)
{
	ssize_t i;

	i = ft_strlen(str);
	if (params->convert == 1 && params->prec <= 1)
		ft_putchar('0');
	if (params->prec >= 0)
		ft_put_n_sym("0", params->prec - i);
	ft_putstr(str, (int) ft_strlen(str));
	if (params->prec > i)
		ft_put_n_sym(" ", params->width - params->prec);
	else
		ft_put_n_sym(" ", params->width - i);
	return (0);
}

char *ft_convert(uintmax_t num, int base, int prec)
{
	char *str;
	char *tmp;
	int i[2];

	i[0] = 0;
	i[1] = 0;
	str = (char *)malloc(sizeof(char) * 300);

	if (num == 0)
		str[(i[0])++] = '0';
	if (num == 0 && prec == 0)
		str[(i[0])++] = '\0';
	while (num > 0)
	{
		str[(i[0])++] = num % base + 48;
		if (str[(i[0] - 1)] > 57)
			str[(i[0] - 1)] = str[i[0] - 1] +  39;
		num = num / base;
	}
	str[(i[0])] = '\0';
	tmp = (char *)malloc(sizeof(char) * (i[0] + 1));
	while (i[0]-- >= 0)
		tmp[(i[1])++] = str[i[0]];
	tmp[i[1]- 1] = '\0';
	free(str);
	return (tmp);
}

int ft_proc_oct(t_arg *params, int i)
{
	long long int num;
	char *res;
	int j;

	if (i == 0 && params->convert == 1)
		params->prec = 0;
	num = (long int)i;
	if (i < 0)
		num = 4294967296 + i;
	if (num < 0)
		num = -num;
	if (params->convert == 1 && params->prec <= 1)
		params->width -= 1;
	res = ft_convert(num, 8, params->prec);
	j = (int)ft_strlen(res);
	if (params->right_al == 1)
		ft_pr_oct_f(params, res);
	else
		ft_pr_oct_s(params, res);
	free(res);
	if (params->convert == 1 && params->prec <= 1)
		return (ft_ret_big(params->width, params->prec, j) + 1);
	return (ft_ret_big(params->width, params->prec, j));
}

int ft_pr_hex_s(t_arg *params, char *str)
{

	char sym;

	if (params->pad_zeros == 1)
		sym = '0';
	else
		sym = ' ';
	if (params->prec < 0)
	{
		if(params->pad_zeros == 1)
		{
			if (params->convert == 1) {
				ft_putchar('0');
				ft_putchar(params->spec);
			}
			ft_put_n_sym(&sym, params->width - (int) ft_strlen(str));
			ft_putstr(str, (int) ft_strlen(str));
		}
		else
		{
			ft_put_n_sym(&sym, params->width - (int) ft_strlen(str));
			if (params->convert == 1) {
				ft_putchar('0');
				ft_putchar(params->spec);
			}
			ft_putstr(str, (int) ft_strlen(str));
		}
	}
	else
	{
		if ((size_t)params->prec > ft_strlen(str))
			ft_put_n_sym(" ", params->width - params->prec);
		else
			ft_put_n_sym(" ", params->width - (int)ft_strlen(str));
		if (params->convert == 1)
		{
			ft_putchar('0');
			ft_putchar(params->spec);
		}
		ft_put_n_sym("0", params->prec - ft_strlen(str));
		ft_putstr(str,(int) ft_strlen(str));
	}
	return (0);
}

int ft_pr_hex_f(t_arg *params, char *str)
{
	ssize_t i;

	i = ft_strlen(str);
	if (params->convert == 1)
	{
		ft_putstr("0", 1);
		ft_putchar(params->spec);
	}
	if (params->prec >= 0)
		ft_put_n_sym("0", params->prec - i);
	ft_putstr(str,(int) ft_strlen(str));
	if (params->prec > i)
		ft_put_n_sym(" ", params->width - params->prec);
	else
		ft_put_n_sym(" ", params->width - i);
	return (0);
}

char *ft_upcase(char *str)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] > 96 && str[i] < 123)
			str[i] -= 32;
	}
	return (str);
}

int ft_proc_hex(t_arg *params, int i)
{
	long long int num;
	char *res;
	int j;


	num = i;
	if (i == 0)
		params->convert = 0;
	if (i < 0)
		num = 4294967296 + i;
	if (num < 0)
		num = -num;
	if (params->convert == 1)
		params->width -= 2;
	res = ft_convert(num, 16, params->prec);
	j = (int)ft_strlen(res);
	if (params->spec == 'X')
		 res = ft_upcase(res);
	if (params->right_al == 1)
		ft_pr_hex_f(params, res);
	else
		ft_pr_hex_s(params, res);
	free(res);
	if (params->convert == 1)
		return (ft_ret_big(params->width, params->prec, j) + 2);
	return (ft_ret_big(params->width, params->prec, j));
}

int ft_ret_big(int a, int b, int c)
{
	if (a > b)
	{
		if (a > c)
			return (a);
		return (c);
	}
	if (b > c)
		return (b);
	return (c);
}

int ft_proc_p(t_arg *params, void *a)
{
	long i;
	char *res;
	int j;

	i = (long) a;
	params->convert = 1;
	params->spec = 'x';
	if (params->convert == 1)
		params->width -= 2;
	res = ft_convert(i, 16, params->prec);
	j = (int)ft_strlen(res);
	if (params->right_al == 1)
		ft_pr_hex_f(params, res);
	else
		ft_pr_hex_s(params, res);
	free(res);
	if (params->prec == 0 && i == 0)
		return ((ft_ret_big(j, params->width, params->prec)) + 2);
	return ((ft_ret_big(j, params->width, params->prec)) + 2);

}

int	ft_data_proc_o(t_arg *params, va_list *args)
{
	if (params->spec == '!')
		return (ft_proc_c(params, params->sym));
	if (params->spec == 'p')
		return (ft_proc_p(params, va_arg(*args, void *)));
	if (params->spec == 's')
		return (ft_proc_str(params, va_arg(*args, char *)));
	if (params->spec == 'c')
		return (ft_proc_c(params, va_arg(*args, int )));
	if (params->spec == 'd' || params->spec == 'i' || params->spec == 'u')
		return (ft_proc_int(params, va_arg(*args, int)));
	if (params->spec == 'o')
		return (ft_proc_oct(params, va_arg(*args, int)));
	if (params->spec == 'x' || params->spec == 'X')
		return (ft_proc_hex(params, va_arg(*args, int)));
	return (0);
}


