/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ederbano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/03 08:34:46 by ederbano          #+#    #+#             */
/*   Updated: 2017/07/03 08:34:50 by ederbano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>

int main(void) {
	int i;

	i = 0;
	i = ft_printf("|%.3s|", "ABCDE");
	printf("\n(%d)", i);
	printf("\n------------------------------\n");
	   i = printf("|%.3s|", "ABCDE");
	printf("\n(%i)", i);
//	printf ("Decimals:%#x %ld\n", 1977, 650000L);
//	printf ("Preceding with blanks:%10d \n", 1977);
//	printf ("Preceding with zeros:%010d \n", 1977);
//	printf ("Some different radices:%d %x %o %#x %#o \n", 100, 100, 100, 100, 100);
//	printf ("floats:%#.4 50f\n ", a);
//	printf ("Width trick:%*d \n", 10, 10);
//	printf ("%s \n", "A string");
	return 0;
}
