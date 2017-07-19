/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 16:03:24 by ederbano          #+#    #+#             */
/*   Updated: 2017/01/11 16:08:00 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_atoi(const char *str)
{
	unsigned long int	n;
	int					minus;

	minus = 1;
	n = 0;
	while (*str == ' ' || *str == '\n' || *str == '\t' || *str == '\r' ||
			*str == '\v' || *str == '\f')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			minus = 44 - *str++;
		if (*str == '+' && minus != -1)
			str++;
	}
	while (*str >= '0' && *str <= '9')
		n = (*str++ - 48) + (n * 10);
	if (n >= 9223372036854775807 && minus == 1)
		return (-1);
	if (n > 9223372036854775807 && minus == -1)
		return (0);
	return (n * minus);
}
