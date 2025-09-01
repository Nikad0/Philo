void	eat_routine(t_philo *philo)
{
	int	left;
	int	right;
	int	elapsed_time;

	left = philo->id - 1;
	right = (philo->id) % philo->data->n_philo;
	if (philo->id % 2 == 0)
	{
		take_fork(philo, left);
		take_fork(philo, right);
	}
	else if (philo->id % 2 != 0)
	{
		take_fork(philo, right);
		take_fork(philo, left);
	}
	elapsed_time = elapsed_time_ms(philo->start_time);
	gettimeofday(&philo->last_meal, NULL);
	print_philo_routine(philo->id, "is eating\n", philo->data);
	sleep_ms(philo, philo->data->t_eat);
	pthread_mutex_lock(philo->e_mutex);
	philo->e_count += 1;
	pthread_mutex_unlock(philo->e_mutex);
	put_fork(philo, left);
	put_fork(philo, right);
}

void	take_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&philo->fork_mutex[fork_id]);
	philo->fork_bool[fork_id] = false;
	print_philo_routine(philo->id, "has taken a fork\n", philo->data);
	pthread_mutex_unlock(&philo->fork_mutex[fork_id]);
}

void	put_fork(t_philo *philo, int fork_id)
{
	pthread_mutex_lock(&philo->fork_mutex[fork_id]);
	philo->fork_bool[fork_id] = true;
	pthread_mutex_unlock(&philo->fork_mutex[fork_id]);
}