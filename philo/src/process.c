/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fldelena <fldelena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 18:20:55 by fldelena          #+#    #+#             */
/*   Updated: 2021/08/01 14:35:31 by fldelena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	livelihood_normi(t_philo *philo)
{
	pthread_mutex_lock(&philo->forks[philo->left_fork]);
	pthread_mutex_lock(philo->print);
	printf(PR_FORK_L, get_time() - philo->start_of_meal, philo->id);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(&philo->forks[philo->righ_fork]);
	pthread_mutex_lock(philo->print);
	printf(PR_FORK_R, get_time() - philo->start_of_meal, philo->id);
	pthread_mutex_unlock(philo->print);
	pthread_mutex_lock(philo->print);
	printf(PR_EAT, get_time() - philo->start_of_meal, philo->id);
	pthread_mutex_unlock(philo->print);
}

void	livelihood(t_philo *philo)
{
	int	count;

	count = 0;
	if (philo->id % 2 == 0 && philo->id != 1)
		fix_usleep(philo->param->time_to_eat / 2);
	while (TRUE)
	{
		livelihood_normi(philo);
		fix_usleep(philo->param->time_to_eat);
		pthread_mutex_unlock(&philo->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->forks[philo->righ_fork]);
		philo->end_of_meal = get_time();
		pthread_mutex_lock(philo->print);
		printf(PR_SLEEP, get_time() - philo->start_of_meal, philo->id);
		pthread_mutex_unlock(philo->print);
		fix_usleep(philo->param->time_to_sleep);
		pthread_mutex_lock(philo->print);
		printf(PR_THINK, get_time() - philo->start_of_meal, philo->id);
		pthread_mutex_unlock(philo->print);
		if (philo->param->numb_of_times_each_philos_must_eat != -1
			&& philo->param->numb_of_times_each_philos_must_eat == ++count)
			break ;
	}
	philo->dead = 1;
}

void	ft_is_dead(t_philo **philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (TRUE)
	{
		if (philo[i]->dead == 1)
			philo[i]->dead = ++count;
		if (count == philo[i]->param->numb_of_philos)
			break ;
		if (!philo[i]->dead && (int)(get_time() - philo[i]->end_of_meal) >
		philo[i]->param->time_to_die)
		{
			pthread_mutex_lock(philo[i]->print);
			printf(PR_DEATH, get_time() - philo[i]->start_of_meal,
				philo[i]->id);
			break ;
		}
		if (i == philo[0]->param->numb_of_philos - 1)
			i = 0;
		else
			i++;
		usleep(500);
	}
}

void	clean_treads(pthread_t *process, int philos)
{
	int	i;

	i = 0;
	while (i < philos)
		pthread_detach(process[i++]);
	free(process);
}

int	start_process(t_all *all)
{
	pthread_t	*process;
	uint64_t	start_of_meal;
	int			i;

	i = -1;
	process = malloc (sizeof(pthread_t) * all->param->numb_of_philos);
	if (process == NULL)
	{
		ft_clean(all);
		return (0);
	}
	start_of_meal = get_time();
	while (++i < all->param->numb_of_philos)
	{
		all->philo[i]->start_of_meal = start_of_meal;
		all->philo[i]->end_of_meal = start_of_meal;
		pthread_create(&process[i], 0, (void *) livelihood, all->philo[i]);
	}
	ft_is_dead(all->philo);
	clean_treads(process, all->param->numb_of_philos);
	return (1);
}
