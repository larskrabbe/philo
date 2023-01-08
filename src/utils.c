/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:12:37 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/08 16:50:33 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

/**
 * @brief print the input data
 * 
 * @param input input data struct
 */
void	print_input_strct(t_input *input)
{
	printf("%i\n", input->philosophers);
	//printf("%i\n", input->time_to_die);
	//printf("%i\n", input->time_to_eat);
	//printf("%i\n", input->time_to_sleep);
	//printf("%i\n", input->amount_to_eat);
	fflush(stdout);
}


void	print_waiter_info(t_waiter *waiter)
{
	if (waiter == NULL)
	{
		//printf("waiter == NULL\n");
		return ;
	}
	//printf("----waiter info----\n");
	//printf("death occured = %p\n", waiter->deat_occurred);
	//printf("max = %i\n", waiter->max);
	//printf("address of mutex_array%p\n", waiter->philo_mutex);
	//printf("address of priolist%p\n", waiter->prio_list);
	//printf("address of reqest_mutex%p\n", waiter->request_mutex);
}
