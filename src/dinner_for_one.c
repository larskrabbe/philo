/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_for_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 03:39:16 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/12 04:29:28 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

void	*lonely_life(void *param)
{
	t_phil	*brain;

	brain = param;
	while (wait_until(&brain->input->start_time))
		usleep(100);
	statemessage(TOOK_L_FORK, brain);
	milisleep(brain->input->time_to_die);
	statemessage(DEAD, brain);
	return (brain);
}

int	dinner_for_one(t_input *input)
{
	pthread_t		pthread;
	t_phil			*brain;

	brain = malloc(sizeof(t_phil));
	if (brain == NULL)
		return (-1);
	philo_input(input, brain, 0);
	if (pthread_create(&pthread, NULL, &lonely_life, brain) != 0)
	{
		free(brain);
		return (-1);
	}
	if (pthread_join(pthread, NULL) != 0)
		printf("join error\n");
	free(brain);
	return (0);
}
