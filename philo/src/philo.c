/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fldelena <fldelena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/31 18:20:25 by fldelena          #+#    #+#             */
/*   Updated: 2021/07/31 18:20:46 by fldelena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_all	*all;

	if (argc < 5 || argc > 6)
		return (print_error(PR_ERR_INI, 1));
	all = (t_all *)malloc(sizeof(t_all));
	all->param = get_params(argv);
	if (all->param == NULL)
	{
		free (all);
		return (print_error(PR_ERR_ARG, 1));
	}
	all->philo = init_philo(all->param);
	if (all->philo == NULL)
	{
		free (all->param);
		free (all);
		return (print_error(PR_ERR, 1));
	}
	if (!start_process(all))
		return (print_error(PR_ERR, 1));
	ft_clean(all);
	return (0);
}
