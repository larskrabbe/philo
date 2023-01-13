/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:05:09 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/12 04:28:43 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

void	philo_input(t_input *input, t_phil *brain, int count)
{
	long int	next_death;

	brain->input = input;
	brain->name = count + 1;
	brain->death_flag = FALSE;
	brain->l_fork_mutex = &input->fork_mutex[count];
	if (count == input->philosophers - 1)
		brain->r_fork_mutex = &input->fork_mutex[0];
	else
		brain->r_fork_mutex = &input->fork_mutex[count + 1];
	brain->start_time = input->start_time;
	if (brain->name % 2 == 1)
		brain->check_fork = &check_fork_odd;
	else
		brain->check_fork = &check_fork_even;
	brain->death_check = &input->death_check[count];
	next_death = (long)input->time_to_die;
	brain->eat_count = 0;
	*brain->death_check = next_death;
}

pthread_mutex_t	*get_mutex_array(size_t len)
{
	pthread_mutex_t	*ptr;
	size_t			i;

	i = 0;
	ptr = malloc(sizeof(pthread_mutex_t) * len);
	if (ptr == NULL)
		return (0);
	while (i < len)
	{
		if (pthread_mutex_init(&ptr[i], NULL))
			return (0);
		i++;
	}
	return (ptr);
}
