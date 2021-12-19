/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fldelena <fldelena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 18:20:18 by fldelena          #+#    #+#             */
/*   Updated: 2021/08/01 15:18:49 by fldelena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

t_param	*get_params(char **argv)
{
	t_param	*param;

	param = (t_param *)malloc(sizeof(t_param));
	param->numb_of_philos = ft_atopl(argv[1]);
	param->time_to_die = ft_atopl(argv[2]);
	param->time_to_eat = ft_atopl(argv[3]);
	param->time_to_sleep = ft_atopl(argv[4]);
	if (argv[5] == NULL)
		param->numb_of_times_each_philos_must_eat = -1;
	else
		param->numb_of_times_each_philos_must_eat = ft_atopl(argv[5]);
	if (param->numb_of_philos == 0 || param->time_to_die < 60
		|| param->time_to_eat < 60 || param->time_to_sleep < 60
		|| param->numb_of_times_each_philos_must_eat == 0
		|| param->numb_of_philos > 200)
	{
		free(param);
		return (NULL);
	}
	return (param);
}

pthread_mutex_t	*init_forks(t_param *param)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * param->numb_of_philos);
	if (forks == NULL)
		return (0);
	while (++i < param->numb_of_philos)
		pthread_mutex_init(&forks[i], 0);
	return (forks);
}

void	get_init_philo(t_philo	**philo, t_param *param)
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	int				i;

	i = -1;
	print = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(print, 0);
	forks = init_forks(param);
	while (++i < param->numb_of_philos)
	{
		philo[i]->id = i + 1;
		philo[i]->dead = 0;
		philo[i]->left_fork = i;
		philo[i]->righ_fork = i + 1;
		if (philo[i]->id == param->numb_of_philos)
			philo[i]->righ_fork = 0;
		philo[i]->forks = forks;
		philo[i]->param = param;
		philo[i]->print = print;
	}
}

t_philo	**init_philo(t_param *param)
{
	t_philo	**philo;
	int		i;

	i = -1;
	philo = malloc(sizeof(t_philo *) * param->numb_of_philos);
	if (philo == NULL)
		return (0);
	while (++i < param->numb_of_philos)
	{
		philo[i] = malloc (sizeof(t_philo));
		if (philo == NULL)
			return (NULL);
	}
	get_init_philo(philo, param);
	return (philo);
}
