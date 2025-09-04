/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 03:28:23 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/04 20:49:13 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!memset(&data, 0, sizeof(t_data)))
		return (1);
	if (ac == 5 || ac == 6)
		if (init(ac, av, &data))
			return (1);
	return (0);
}
