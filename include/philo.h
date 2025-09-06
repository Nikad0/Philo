/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erbuffet <erbuffet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/27 00:07:58 by erbuffet          #+#    #+#             */
/*   Updated: 2025/09/06 13:46:46 by erbuffet         ###   ########lyon.fr   */
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
typedef struct s_fork	t_fork;

struct					s_philo
{
	int					id;
	int					e_count;

	struct timeval		start_time;
	struct timeval		last_meal;

	t_fork				*left_fork;
	t_fork				*right_fork;

	pthread_mutex_t		e_mutex;

	t_data				*data;
	t_fork				*fork;
};

struct					s_fork
{
	int					fork_id;
	bool				flag;
	pthread_mutex_t		mutex;

	t_data				*data;
	t_philo				*philo;
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
	t_fork				*fork;
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
void					attribute_fork(t_data *data);
int						take_fork(t_fork *fork);
void					put_fork(t_fork *fork);

#endif
// oui oui