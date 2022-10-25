/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createphilosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:58:05 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/25 19:32:56 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

void	*lifecycle(void *param)
{
	thinking_cycle(param);
	return (NULL);
}


void	create_philo(t_input *input, unsigned int count)
{
	pthread_t		pthread;
	t_philosophor	*brain;

	if (count <= input->philosophers)
	{
		brain = malloc(sizeof(t_philosophor));
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
