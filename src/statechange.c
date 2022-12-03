/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   statechange.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 23:29:03 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/12/03 12:22:05 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"../include/philo.h"


/**
 * @brief prints the current timestamp 
 * and the philophor that change the state with the new state
 * 
 * @param philosopher the philosopher who change state
 * @param str the new state
 */
void	statemessage(char *str, t_phil *brain)
{
	// pthread_mutex_lock(&brain->input->mutex_arr[death_check]);
	// if (*brain->input->deat_occurred == TRUE)
		brain->death_occured = TRUE;
	// pthread_mutex_unlock(&brain->input->mutex_arr[death_check]);
	// if (brain->death_flag == TRUE)
	// 	return ;
	printf(" %i %s\n", brain->name, str);
}