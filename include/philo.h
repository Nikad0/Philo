/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:07:58 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/01 09:14:44 by erbuffet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_data	t_data;

struct					s_philo
{
	int					id;
	int					e_count;

	struct timeval		start_time;
	struct timeval		last_meal;

	bool				*fork_bool;

	pthread_mutex_t		*fork_mutex;
	pthread_mutex_t		*e_mutex;

	t_data				*data;
};

struct					s_data
{
	int					n_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					n_eat;

	bool				death_flag;

	pthread_t			*thread;

	pthread_mutex_t		print_mutex;
	pthread_mutex_t		meal_mutex;
	pthread_mutex_t		death_mutex;

	t_philo				*philo;
};

/*#####################################*/
/*#########      MAIN.C     ###########*/
/*#####################################*/
int						main(int ac, char **av);

/*#####################################*/
/*#########      INITS.C     ##########*/
/*#####################################*/
int						init_mutex(t_data *data);
int						init_thread(t_data *data);
int						init_philo(int ac, char **av, t_data *data);

/*#####################################*/
/*#########      ROUTINE.C     ########*/
/*#####################################*/
void					eat_routine(t_philo *philo);
void					think_routine(t_philo *philo);
void					sleep_routine(t_philo *philo);
void					*start_routine(void *arg);

/*#####################################*/
/*#########      MONITORING.C  ########*/
/*#####################################*/
bool					is_dead(t_philo *philo);

/*#####################################*/
/*#########      EXIT_PHILO.C  ########*/
/*#####################################*/
void					clean(t_data *data, int index);

/*#####################################*/
/*#########      UTILS.C     ##########*/
/*#####################################*/
int						ft_atoi(const char *nptr);
bool					is_number(const char *str);

/*#####################################*/
/*#########  MUTEX_UTILS.C   ##########*/
/*#####################################*/
void					sleep_ms(t_philo *philo, int time);
long long				elapsed_time_ms(struct timeval start);
void					print_philo_routine(int philo_id, char *routine,
							t_data *data);

/*#####################################*/
/*#########     FORK.C       ##########*/
/*#####################################*/
void					take_fork(t_philo *philo, int left, int right);
void					put_fork(t_philo *philo, int left, int right);
void					attribute_fork(t_philo *philo);

#endif