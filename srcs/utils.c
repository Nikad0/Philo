/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 03:28:20 by erbuffet          #+#    #+#             */
/*   Updated: 2025/08/23 21:34:22 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	is_number(const char *str)
{
	int	j;

	j = 0;
	if (!str || str[0] == '\0')
		return (false);
	while (str[j])
	{
		if (str[j] < '0' || str[j] > '9')
			return (false);
		j++;
	}
	return (true);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	nb;
	int	signe;

	i = 0;
	nb = 0;
	signe = 1;
	while ((nptr[i] >= '\t' && nptr[i] <= '\r') || (nptr[i] == ' '))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			signe *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + nptr[i] - 48;
		i++;
	}
	return (nb * signe);
}
