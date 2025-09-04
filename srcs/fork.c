/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:09:04 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/04 21:33:26 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *philo, int left, int right)
{
}

void	put_fork(t_philo *philo, int left, int right)
{
}

void	attribute_fork(t_philo *philo)
{
	int	left;
	int	right;

	left = philo->id - 1;                       // philo own fork
	right = (philo->id) % philo->data->n_philo; // next philo fork
}
