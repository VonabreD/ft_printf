/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 08:39:48 by ederbano          #+#    #+#             */
/*   Updated: 2017/07/03 08:39:48 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_find_spec(char *str, t_arg *params)
{
	int i;

	i = 0;
	while (str[i] != '\0' && str[i] != '%')
	{
		if (str[i] == 's' || str[i] == 'p' || str[i] == 'd' || str[i] == 'i' ||
			str[i] == 'o' || str[i] == 'u' || str[i] == 'x' || str[i] == 'c' ||
			str[i] == 'X')
		{
			params->spec = str[i];
			return (++i);
		}
		if (str[i] == 'S' || str[i] == 'D' || str[i] == 'O' || str[i] == 'U' ||
			str[i] == 'C')
		{
			params->spec = (char)(str[i] + 32);
			params->len = 3;
			return (++i);
		}
		i++;
	}
	return (-1);
}

int		ft_chk_flags(char c, char p, t_arg *params)
{
	if (c != params->spec && (c == ' ' || c == '0'
			|| c == '+' || c == '-' || c == '#'))
	{
		if (c == '#')
			params->convert = 1;
		if (c == '-')
			params->right_al = 1;
		if (c == '+')
			params->plus = 1;
		if (c == ' ')
			params->space = 1;
		if (c == '0')
		{
			if (p && (!(ft_isdigit(p)) || p == '0'))
				params->pad_zeros = 1;
			else
				params->pad_zeros = -1;
		}
		return (1);
	}
	return (0);
}

void	ft_clear_list(t_arg *params)
{
	params->spec = '\0';
	params->convert = -1;
	params->len = 0;
	params->pad_zeros = -1;
	params->plus = -1;
	params->right_al = -1;
	params->prec = -1;
	params->space = -1;
	params->width = -1;
}

int		ft_fprintf(const char *format, va_list *args)
{
	int		i;
	t_arg	params;
	int		num;

	num = 0;
	i = -1;
	while (format[++i] != '\0')
	{
		ft_clear_list(&params);
		if (format[i] != '%' && format[i] != '\0')
		{
			write(1, &format[i], 1);
			num++;
		}
		else {
			i += ft_parse((char *) &format[i + 1], &params);
			num += ft_data_proc(&params, args);
		}
	}
	return (num);
}

int		ft_printf(const char *format, ...)
{
	int		i;
	va_list	args;

	va_start(args, format);
	i = ft_fprintf(format, &args);
	va_end(args);
	return (i);
}
