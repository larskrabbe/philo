/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createphilosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:58:05 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/12 04:32:27 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

int	wait_until(struct timeval *time)
{
	if (get_time_stamp(time) < 0)
		return (1);
	else
		return (0);
}

void	*lifecycle(void *param)
{
	thinking_cycle(param);
	return (NULL);
}

int	free_brain(t_phil *brain)
{
	free(brain);
	return (-1);
}

int	setup(t_input *input, int count)
{
	pthread_t		pthread;
	t_phil			*brain;

	if (count < input->philosophers)
	{
		brain = malloc(sizeof(t_phil));
		if (brain == NULL)
			return (-1);
		philo_input(input, brain, count);
		count++;
		if (pthread_create(&pthread, NULL, &lifecycle, brain))
			return (free_brain(brain));
		if (setup(input, count) != 0)
		{
			pthread_detach(pthread);
			return (free_brain(brain));
		}
		if (pthread_join(pthread, NULL) != 0)
			return (free_brain(brain));
		free(brain);
	}
	else
		monitor(input);
	return (0);
}
