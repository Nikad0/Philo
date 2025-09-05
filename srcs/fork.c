/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nikado <nikado@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 00:09:04 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/05 11:16:11 by nikado           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int take_fork(t_fork *fork)
{
    int success = 0;

    pthread_mutex_lock(&fork->mutex);
    if (fork->flag == true)
    {
        fork->flag = false;
        success = 1;
    }
    pthread_mutex_unlock(&fork->mutex);
    return success;
}

void put_fork(t_fork *fork)
{
    pthread_mutex_lock(&fork->mutex);
    fork->flag = true;
    pthread_mutex_unlock(&fork->mutex);
}

void	attribute_fork(t_data *data)
{
    int i = -1;
    while (++i < data->n_philo)
    {
        if (i % 2 == 0)
        {
            data->philo[i].left_fork  = &data->fork[i];
            data->philo[i].right_fork = &data->fork[(i + 1) % data->n_philo];
        }
        else
        {
            data->philo[i].left_fork  = &data->fork[(i + 1) % data->n_philo];
            data->philo[i].right_fork = &data->fork[i];
        }

    }
}