/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/28 13:01:39 by ederbano          #+#    #+#             */
/*   Updated: 2017/01/09 10:08:53 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr(char const *s, int prec)
{
	char	*ptr;
	int		i;

	if (!s)
		return ;
	i = -1;
	if (prec < 0)
		prec = ft_strlen(s);
	ptr = (char *)s;
	while (ptr[++i] && prec-- > 0 )
		ft_putchar(ptr[i]);
}
