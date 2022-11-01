/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createphilosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:58:05 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/30 02:10:23 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

int	wait_until(struct timeval *start_time)
{
	if (get_time_stamp(start_time) < 0)
		return (1);
	else
		return (0);
}

void	*lifecycle(void *param)
{
	while (wait_until(&((t_phil *)param)->input->start_time))
		usleep(10);
	// set here a start time using  0.1 sleep and cheking for curring time equel starttime + 1 *ms per ~50  philosopher
	statemessage("is created", &((t_phil *)param)->input->start_time, (t_phil *)param);
	usleep (2000);
	thinking_cycle(param);
	statemessage("is return", &((t_phil *)param)->input->start_time, (t_phil *)param);
	return (NULL);
}


void	create_philo(t_input *input, int count)
{
	pthread_t		pthread;
	t_phil			*brain;

	if (count <= input->philosophers)
	{
		brain = malloc(sizeof(t_phil));
		if (brain == NULL)
			return ;// error
		brain->input = input;
		brain->name = count;
		brain->right_fork = count + 1;
		if (brain->right_fork >= input->philosophers)
			brain->right_fork = 1;
		brain->energy = input->time_to_die;
		count++;
		pthread_create(&pthread, NULL, &lifecycle, brain);
		create_philo(input, count);
		if (pthread_join(pthread, NULL) != 0)
			printf("join error\n");
		free(brain);
	}
}
