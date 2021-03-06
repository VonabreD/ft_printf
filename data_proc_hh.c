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

long int ft_hhproc_types(int i, t_arg *params)
{
	long int num;
	num = i % 256;
	while (num > 127|| num < -128)
	{
		if (num < -128)
			num = 128 + (num % 128);
		if (num > 127)
			num = -128 + (num % 128);
	};
	if ((params->spec == 'u' || params->spec == 'X' || params->spec == 'x' || params->spec == 'o') && num < 0)
		num = 256 + num;
	return (num);
}
int ft_hhproc_int(t_arg *params, int i)
{
	char zn;
	long int num;

	num = ft_hhproc_types(i, params);
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

int ft_hhproc_oct(t_arg *params, int i)
{
	long int num;
	char *res;
	int j;

	if (i == 0 && params->prec > 0)
		params->convert = 0;
	num = ft_hhproc_types(i, params);
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
		return (ft_ret_big(params->width, params->prec, j));
	return (ft_ret_big(params->width, params->prec, j));
}

int ft_hhproc_hex(t_arg *params, int i)
{
	long int num;
	char *res;
	int j;

	if (i == 0)
		params->convert = 0;
	num = ft_hhproc_types(i, params);
	if (params->convert == 1)
		params->width -= 2;
	res = ft_convert(num, 16, params->prec);
	j = (int)ft_strlen(res);
	if (params->spec == 'X')
		ft_upcase(res);
	if (params->right_al == 1)
		ft_pr_hex_f(params, res);
	else
		ft_pr_hex_s(params, res);
	free(res);
	if (params->convert == 1)
		return (ft_ret_big(params->width, params->prec, j));
	return (ft_ret_big(params->width, params->prec, j));
}

int	ft_data_proc_hh(t_arg *params, va_list *args)
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
		return (ft_hhproc_int(params, va_arg(*args, int)));
	if (params->spec == 'o')
		return (ft_hhproc_oct(params, va_arg(*args, int)));
	if (params->spec == 'x' || params->spec == 'X')
		return (ft_hhproc_hex(params, va_arg(*args, int)));
	return (0);
}


