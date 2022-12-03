/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 22:05:09 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 13:35:39 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"

/**
 * @brief join the philo pthreads together
 * 
 * @param pthread_array the array of pthread for pthread_create
 * @param max the max amount of pthread join
 * 
 * @return returns the amount total pthread that got joined
 */
int	join_philo(pthread_t *pthread_array, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (pthread_join(pthread_array[i], NULL))
			return (i);
		i++;
	}
	return (i);
}

/**
 * @brief start the philo_phtreads
 * 
 * @param philo_array the data-struct-array for each of the philo
 * @param pthread_array the array of pthread for pthread_create
 * @param max the max amount of pthread to start
 * 
 * @return the ammount pthread that got started
 */
int	start_philo(t_phil *philo_array, pthread_t *pthread_array, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		if (pthread_create(&pthread_array[i], NULL, \
		&philocycle, &philo_array[i]))
			return (i);
		i++;
	}
	return (i);
}

/**
 * @brief allocate the memory 
 * for the structurs that will be parssed to the philo pthread
 * and copy the data input data inside the structers
 * 
 * @param input input data that deteremed how many philo 
 * will be created. And the date that will copy inside of the structures
 *
 * @return returns the pointer to the start of the array 
 * or null if allocation failed
 */
t_phil	*create_philo(t_input *input)
{
	t_phil	*philo_array;
	int		i;

	i = 0;
	if (input->philosophers < 1)
		return (NULL);
	philo_array = malloc(sizeof(t_phil) * input->philosophers);
	if (philo_array == NULL)
		return (NULL);
	while (i < input->philosophers)
	{
		philo_array->input = *input;
		i++;
	}
	return (philo_array);
}
