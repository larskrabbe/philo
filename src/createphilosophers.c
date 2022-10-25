/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createphilosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:58:05 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/25 07:08:29 by lkrabbe          ###   ########.fr       */
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
		brain->input = *input;
		brain->name = count;
		brain->energy = input->time_to_die;
		count++;
		pthread_create(&pthread, NULL, &lifecycle, brain);
		create_philo(input, count);
		free(brain);
		if (pthread_join(pthread, NULL) != 0)
			printf("join error\n");
	}
}
