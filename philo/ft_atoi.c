/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: timanish <timanish@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:15:03 by timanish          #+#    #+#             */
/*   Updated: 2025/03/18 16:34:00 by timanish         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	unsigned long long	re;
	int					sign;
	int					i;

	re = 0;
	sign = 1;
	i = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str ++;
	if (*str == '-')
		return (-1);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		re = re * 10 + str[i] - '0';
		i ++;
	}
	if (str[i] && (str[i] < '0' || str[i] > '9'))
		return (-1);
	return (re * sign);
}
