/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 02:45:46 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/25 06:58:11 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

void	transform_args(t_input *input)
{
	input->philosophers = 12;
	input->time_to_die = 300;
	input->time_to_eat = 100;
	input->time_to_sleep = 100;
	input->amount_to_eat = 20;
	input->name = 0;
	input->forks = malloc(sizeof(int) * input->philosophers);
	memset(input->forks, 0, input->philosophers);
	gettimeofday(&input->start_time, NULL);
	pthread_mutex_init(input->mutex, NULL);
;

}
