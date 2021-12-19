/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fldelena <fldelena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 18:21:01 by fldelena          #+#    #+#             */
/*   Updated: 2021/08/01 14:37:41 by fldelena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atopl(char *str)
{
	long long	dig;
	int			i;

	dig = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] > 47 && str[i] < 58)
			dig = dig * 10 + (str[i] - '0');
		else
			return (0);
		i++;
	}
	if (dig > 2147483647)
		return (0);
	return ((int)dig);
}

void	ft_clean(t_all *all)
{
	int				i;
	int				count;
	pthread_mutex_t	*forks;

	i = 0;
	count = all->param->numb_of_philos;
	forks = all->philo[i]->forks;
	while (i < all->param->numb_of_philos)
		pthread_mutex_destroy(&forks[i++]);
	pthread_mutex_destroy(all->philo[0]->print);
	free(all->philo[0]->print);
	free (forks);
	free (all->param);
	i = 0;
	while (i < count)
		free (all->philo[i++]);
	free (all->philo);
	free (all);
}

int	print_error(char *str, int ret)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write (2, str, i);
	write (2, "\n", 1);
	return (ret);
}

uint64_t	get_time(void)
{
	uint64_t				to_return;
	static struct timeval	time;

	if (gettimeofday(&time, 0) < 0)
		return (0);
	to_return = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (to_return);
}

void	fix_usleep(uint64_t msec)
{
	uint64_t	start;

	start = get_time();
	while (get_time() - start < msec)
		usleep(500);
}
