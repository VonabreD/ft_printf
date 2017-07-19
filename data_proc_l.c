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

void ft_putlstr(wchar_t *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		ft_putlchar(str[i]);
		i++;
	}
}

int ft_strlen_l(wchar_t *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int ft_proc_lstr(t_arg *params, wchar_t *str)
{
	ssize_t i;

	i = (int)ft_strlen_l(str);
	if (params->width == -1)
		ft_putlstr(str);
	else
	{
		if (params->right_al == 1)
		{
			ft_putlstr(str);
			ft_put_n_sym(" ", params->width - i);
		}
		else
		{
			if (params->pad_zeros == 1)
				ft_put_n_sym("0", params->width - i);
			else
				ft_put_n_sym(" ", params->width - i);
			ft_putlstr(str);
		}
		return (0);
	}
	return (1);
}

int ft_count_bits(wchar_t c)
{
	int i;

	i = 0;

	if (c < 0)
		i++;
	while (c > 0)
	{
		c /= 2;
		i++;
	}
	return (i);
}

int ft_putlchar(wchar_t sym)
{
	unsigned int mask[4];
	unsigned int v;
	int size;
	int res;
	unsigned char octet;

	res = 0;
	size = ft_count_bits(sym);
	v = sym;
	mask[0] = 0;
	mask[1] = 49280;
	mask[2] = 14712960;
	mask[3] = 4034953344;
	if (size <= 7)
	{
		octet = sym;
		write(1, &octet, 1);
	}
	else  if (size <= 11)
	{
		unsigned char o2 = (v << 26) >> 26;
		unsigned char o1 = ((v >> 6) << 27) >> 27;

		octet = (mask[1] >> 8) | o1;
		write(1, &octet, 1);
		octet = ((mask[1] << 24) >> 24) | o2;
		write(1, &octet, 1);
	}
	else  if (size <= 16)
	{
		unsigned char o3 = (v << 26) >> 26;
		unsigned char o2 = ((v >> 6) << 26) >> 26;
		unsigned char o1 = ((v >> 12) << 28) >> 28;

		octet = (mask[2] >> 16) | o1;
		write(1, &octet, 1);
		octet = ((mask[2] << 16) >> 24) | o2;
		write(1, &octet, 1);
		octet = ((mask[2] << 24) >> 24) | o3;
		write(1, &octet, 1);
	}
	else
	{
		unsigned char o4 = (v << 26) >> 26;
		unsigned char o3 = ((v >> 6) << 26) >> 26;
		unsigned char o2 = ((v >> 12) << 26) >> 26;
		unsigned char o1 = ((v >> 18) << 29) >> 29;

		octet = (mask[3] >> 24) | o1;
		write(1, &octet, 1);
		octet = ((mask[3] << 8) >> 24) | o2;
		write(1, &octet, 1);
		octet = ((mask[3] << 16) >> 24) | o3;
		write(1, &octet, 1);
		octet = ((mask[3] << 24) >> 24) | o4;
		write(1, &octet, 1);
	}
	return (0);
}

int ft_proc_lc(t_arg *params, wchar_t c)
{

	if (params->width == -1)
		ft_putlchar(c);
	else
	{
		if (params->right_al == 1)
		{
			ft_putlchar(c);
			ft_put_n_sym(" ", params->width - 1);
		}
		else
		{
			if (params->pad_zeros == 1)
				ft_put_n_sym("0", params->width - 1);
			else
				ft_put_n_sym(" ", params->width - 1);
			ft_putlchar(c);
		}
		return (0);
	}
	return (1);
}

uintmax_t ft_lproc_types(intmax_t i, t_arg *params)
{
	uintmax_t num;

	num = 0;
	if (params->spec == 'u' || params->spec == 'x' || params->spec == 'X')
		num = i;
	else
	{
		if (i < 0)
			num = i * -1;
		else
			num = i;
	}
	return (num);
}

void ft_lputnbr_long(uintmax_t num)
{
	char c;
	uintmax_t x;

	x = num;
	if (x == 0)
		ft_putchar('0');
	if (x != 0) {
		c = x % 10 + 48;
		if (x / 10 > 0)
			ft_lputnbr_long(x / 10);
		ft_putchar(c);
	}
}

int ft_lpr_in_f(t_arg *params, long int num, char zn)
{
	if (zn != '\0')
		ft_putchar(zn);
	if (params->prec >= 0)
		ft_put_n_sym("0", params->prec - ft_int_len(num, params->prec));
	ft_lputnbr_long(num);
	if (params->prec > ft_int_len(num, params->prec))
		ft_put_n_sym(" ", params->width - params->prec);
	else
		ft_put_n_sym(" ", params->width - ft_int_len(num, params->prec));
	return (0);
}

int ft_lpr_in_s(t_arg *params, uintmax_t num, char zn)
{
	if (params->pad_zeros == 1 && params->prec < 0)
	{
		if (zn != '\0')
			ft_putchar(zn);
		ft_put_n_sym("0", params->width - ft_int_len(num, params->prec));
		ft_lputnbr_long(num);
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
		ft_lputnbr_long(num);
	}
	else
	{
		ft_put_n_sym(" ", params->width - ft_int_len(num, params->prec));
		if (zn != '\0')
			ft_putchar(zn);
		ft_lputnbr_long(num);
	}
	return (0);
}

int ft_lproc_int(t_arg *params, intmax_t i)
{
	char zn;
	uintmax_t num;

	num = ft_lproc_types(i, params);
	zn = '\0';
	if (params->space == 1 && params->spec != 'u')
		zn = ' ';
	if (params->plus == 1 && params->spec != 'u')
		zn = '+';
	if (i < 0 && params->spec != 'u')
	{
		zn = '-';
	}
	if (zn != '\0' && params->spec != 'u')
		params->width -=1;
	if (params->right_al == 1)
		ft_lpr_in_f(params, num, zn);
	else
		ft_lpr_in_s(params, num, zn);
	if (zn != '\0')
		return (ft_ret_big(params->width, params->prec, ft_int_len(num, params->prec)) + 1);
	return (ft_ret_big(params->width, params->prec, ft_int_len(num, params->prec)));
}

int ft_lproc_oct(t_arg *params, uintmax_t i)
{
	long int num;
	char *res;

	num = i;
	if (params->convert == 1 && params->prec <= 1)
		params->width -= 1;
	res = ft_convert(num, 8, params->prec);
	if (params->right_al == 1)
		ft_pr_oct_f(params, res);
	else
		ft_pr_oct_s(params, res);
	free(res);
	if (params->convert == 1 && params->prec <= 1)
		return (ft_ret_big(params->width, params->prec, (int)ft_strlen(res)) + 1);
	return (ft_ret_big(params->width, params->prec, (int)ft_strlen(res)));
}

int ft_lproc_hex(t_arg *params, uintmax_t i)
{
	long int num;
	char *res;

	num = ft_lproc_types(i, params);
	if (i == 0)
		params->convert = 0;
	if (params->convert == 1)
		params->width -= 2;
	res = ft_convert(num, 16, params->prec);
	if (params->spec == 'X')
		ft_upcase(res);
	if (params->right_al == 1)
		ft_pr_hex_f(params, res);
	else
		ft_pr_hex_s(params, res);
	free(res);
	if (params->convert == 1)
		return (ft_ret_big(params->width, params->prec, (int)ft_strlen(res)) + 2);
	return (ft_ret_big(params->width, params->prec, (int)ft_strlen(res)));
}

int	ft_data_proc_l(t_arg *params, va_list *args)
{
    if (params->spec == 'p')
        return (ft_proc_p(params, va_arg(*args, void *)));
	if (params->spec == 's')
		return (ft_proc_lstr(params, va_arg(*args, wchar_t *)));
	if (params->spec == 'c')
		return (ft_proc_lc(params, va_arg(*args, wchar_t )));
	if (params->spec == 'd' || params->spec == 'i' || params->spec == 'u')
		return (ft_lproc_int(params, va_arg(*args, intmax_t)));
	if (params->spec == 'o')
		return (ft_lproc_oct(params, va_arg(*args, uintmax_t)));
	if (params->spec == 'x' || params->spec == 'X')
		return (ft_lproc_hex(params, va_arg(*args, uintmax_t)));
	return (0);
}


