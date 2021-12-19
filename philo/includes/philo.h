/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fldelena <fldelena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 18:21:05 by fldelena          #+#    #+#             */
/*   Updated: 2021/08/01 15:18:38 by fldelena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdio.h>
# define TRUE		1
# define PR_FORK_L	"%lld %i has taken a fork \n"
# define PR_FORK_R	"%lld %i has taken a fork \n"
# define PR_EAT		"%lld %i is eating \n"
# define PR_SLEEP	"%lld %i sleeping \n"
# define PR_THINK	"%lld %i is thinking \n"
# define PR_DEATH	"%lld %d died\n"
# define PR_ERR_ARG	"wrong args"
# define PR_ERR_INI	"incorrect number of arguments"
# define PR_ERR		"error"

typedef struct s_param
{
	int	numb_of_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	numb_of_times_each_philos_must_eat;
}			t_param;

typedef struct s_philo
{
	int				id;
	int				left_fork;
	int				righ_fork;
	uint64_t		start_of_meal;
	uint64_t		end_of_meal;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print;
	t_param			*param;
	int				dead;

}			t_philo;

typedef struct s_all
{
	t_param	*param;
	t_philo	**philo;
}			t_all;

t_param		*get_params(char **argv);
t_philo		**init_philo(t_param *param);
int			ft_atopl(char *str);
int			start_process(t_all *all);
int			print_error(char *str, int ret);
void		fix_usleep(uint64_t msec);
void		ft_clean(t_all *all);
uint64_t	get_time(void);

#endif
