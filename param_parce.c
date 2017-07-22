/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_parce.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/14 00:33:01 by ederbano          #+#    #+#             */
/*   Updated: 2017/07/14 00:33:03 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_parce_flags(char *str, t_arg *params, int *pos)
{
	int i;
	int f;

	f = 0;
	i = *pos;
	while (str[i] != params->spec && (str[i] == ' ' || str[i] == '0'
				|| str[i] == '+' || str[i] == '-' || str[i] == '#'))
	{
		if (ft_chk_flags(str[i], str[i - 1], params) == 1)
			f++;
		i++;
	}
	*pos = i;
	if (f > 0)
		return (1);
	return (0);
}

int	ft_parce_width(char *str, t_arg *params, int *cur_pos)
{
	char	*num;
	int		i;

	i = *cur_pos;
	if (!(ft_isdigit(str[i])) || str[i - 1] == '.')
		return (0);
	while (ft_isdigit(str[i]))
		i++;
	num = (char *)malloc(sizeof(char *) * (i - *cur_pos + 1));
	num[i - *cur_pos] = '\0';
	i = *cur_pos - 1;
	while (ft_isdigit(str[++i]))
		num[i - *cur_pos] = str[i];
	params->width = ft_atoi(num);
	*cur_pos = i;
	free(num);
	return (1);
}

int	ft_parce_prec(char *str, t_arg *params, int *cur_pos)
{
	char	*num;
	int		i;

	if (str[*cur_pos] != '.')
		return (0);
	(*cur_pos)++;
	i = *cur_pos;
	if (!(ft_isdigit(str[i])))
	{
		params->prec = 0;
		return (1);
	}
	while (ft_isdigit(str[i]))
		i++;
	num = (char *)malloc(sizeof(char ) * (i - *cur_pos + 1));
		i = *cur_pos - 1;
	while (ft_isdigit(str[++i]))
		num[i - *cur_pos] = str[i];
	num[i - *cur_pos] = '\0';
	params->prec = ft_atoi(num);
	*cur_pos = i;
	free (num);
	return (1);
}

int	ft_parce_len(char *str, t_arg *params, int *cur_pos)
{
	int i;

	i = *cur_pos;
	if (params->len > 0)
		return (0);
	if (str[i] == 'l' || str[i] == 'h' || str[i] == 'L' || str[i] == 'j' || str[i] == 'z')
	{
		if (str[i] == 'h')
		{
			params->len = 1 + 0 * (i++);
			if (str[i] == 'h')
				params->len = 2 + 0 * (i++);
		}
		else if (str[i] == 'l')
		{
			params->len = 3 + 0 * (i++);
			if (str[i] == 'l')
				params->len = 4 + 0 * (i++);
		}
		else if (str[i] == 'j')
			params->len = 5 + 0 * (i++);
		else if (str[i] == 'z') {
			params->len = 3 + 0 * (i++);
//			params->spec = 'u';
		}
		*cur_pos = i;
		return (1);
	}
	return (0);
}

int ft_alter_spec(char *str, t_arg *params)
{
	int i;

	i = 0;
	while(str[i] != '\0' && !(ft_isalpha(str[i])) && str[i] != '%')
		i++;
	params->spec = '!';
	params->sym = str[i];
	return(-1);
}

int	ft_parse(char *str, t_arg *params)
{
	int spec_pos;
	int cur_pos;
	int i[4];

	spec_pos = ft_find_spec(str, params);
	if (spec_pos < 0)
		spec_pos = ft_alter_spec(str, params);
	cur_pos = 0;
	i[0] = 1;
	while (i[0] > 0 || i[1] > 0 || i[2] > 0 || i[3] > 0)
	{
		i[0] = ft_parce_flags(str, params, &cur_pos);
		i[1] = ft_parce_width(str, params, &cur_pos);
		i[2] = ft_parce_prec(str, params, &cur_pos);
		i[3] = ft_parce_len(str, params, &cur_pos);
	}
	params->sym = str[cur_pos];
	if (params->sym == '\0')
		return (0);
	if (spec_pos < 0)
		return (cur_pos + 1);
	return (spec_pos);
}
