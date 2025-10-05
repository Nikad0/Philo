/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 03:28:23 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/30 21:40:43 by erbuffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (!memset(&data, 0, sizeof(t_data)))
		return (1);
	if (ac == 5 || ac == 6)
	{
		if (init(ac, av, &data))
			return (0);
		printf("error\n");
		return (1);
	}
	printf("error\n");
	return (1);
}
