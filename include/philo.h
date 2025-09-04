/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:07:58 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/04 20:39:51 by erbuffet         ###   ########lyon.fr   */
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

	bool				fork_flag;

	struct timeval		start_time;
	struct timeval		last_meal;

	pthread_mutex_t		e_mutex;
	pthread_mutex_t		fork_mutex;

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
int						init_philo(t_data *data);
int						init(int ac, char **av, t_data *data);

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
bool					check_death_flag(t_philo *philo);
bool					is_dead(t_philo *philo);
bool					check_fork_flag(t_philo *philo, int left, int right);

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
void					put_fork(t_philo *philo, int left, int right);
void					attribute_fork(t_philo *philo);

#endif