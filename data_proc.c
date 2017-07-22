/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_proc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/07 11:15:55 by ederbano          #+#    #+#             */
/*   Updated: 2017/07/07 11:15:56 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_put_n_sym(char *sym, int num)
{
	if (num < 0)
		return ;
	while (num--)
		write(1, sym, 1);
}

int ft_proc_str(t_arg *params, char *str)
{
	int i;

	if (str == NULL)
		str = "(null)";
	if ((params->prec > (int)ft_strlen(str) || params->prec == -1))
		i = (int)ft_strlen(str);
	else
		i = params->prec;
	if (params->width == -1)
		ft_putstr(str, params->prec);
	else
	{
		if (params->right_al == 1)
		{
			ft_putstr(str, params->prec);
			ft_put_n_sym(" ", params->width - i);
		}
		else
		{
			if (params->pad_zeros == 1)
				ft_put_n_sym("0", params->width - i);
			else
				ft_put_n_sym(" ", params->width - i);
			ft_putstr(str, params->prec);
		}
		return (ft_ret_big(i, params->width, 0));
	}
	return (i);
}

int ft_proc_c(t_arg *params, char c)
{
	if (params->width == -1)
		ft_putchar(c);
	else
	{
		if (params->right_al == 1)
		{
			ft_putchar(c);
			ft_put_n_sym(" ", params->width - 1);
		}
		else
		{
			if (params->pad_zeros == 1)
				ft_put_n_sym("0", params->width - 1);
			else
				ft_put_n_sym(" ", params->width - 1);
			ft_putchar(c);
		}
		return (params->width);
	}
	return (1);
}

int ft_int_len (uintmax_t num, int prec)
{
	int  i;

	if (num == 0 && prec == 0)
		return (0);
	i = 0;
	if (num == 0)
		return (1);
	while (num > 0)
	{
		i++;
		num /= 10;
	}
	return (i);
}

void ft_putnbr_long(long long int num, int prec)
{
	char c;
	unsigned long long int x;

	if (prec == 0 && num == 0)
		return ;
	x = (unsigned long long int) num;
	if (x == 0)
		ft_putchar('0');
	if (num < 0)
	{
		x = num * -1;
		if (x > 0)
			ft_putchar('-');
	}
	if (x != 0) {
		c = x % 10 + 48;
		if (x / 10 > 0)
			ft_putnbr_long(x / 10, 1);
		ft_putchar(c);
	}
}

int	ft_data_proc(t_arg *params, va_list *args)
{
	if (params->len == 0)
		return (ft_data_proc_o(params, args));
	if (params->len == 1)
		return (ft_data_proc_h(params, args));
	if (params->len == 2)
		return (ft_data_proc_hh(params, args));
	if (params->len == 3)
		return (ft_data_proc_l(params, args));
	if (params->len == 4)
		return (ft_data_proc_l(params, args));
	if (params->len == 5)
		return (ft_data_proc_l(params, args));
	return (0);
}
