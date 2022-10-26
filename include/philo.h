/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe < lkrabbe@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:39:36 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/10/26 13:30:52 by lkrabbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

//?-----------------THE_INCLUDES---------------?//

# include	<unistd.h>
# include	<stdio.h>
# include	<stdlib.h>
# include	<string.h>
# include	<sys/time.h>
# include	<pthread.h>

//?------------------THE_DEFINES---------------?//

# define TOOK_FORK "has taken a fork"
# define EATING  "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"
# define MAX_PHILOS 200

//?-------------------THE_ENUMS----------------?//

typedef enum e_state{
	thinking = 1,
	sleeping = 2,
	eating = 3,
	dead = 4,
}t_state;

typedef enum e_forkstate{
	on_table = 0,
	in_hand = 1,
}t_forkstate;

//?------------------THE_STRUCTS---------------?//
/**
 * @brief contain all the input from the arguments 
 * so each thread can read it form anywhere
 * 
 */
typedef struct s_input
{
	unsigned int	philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	amount_to_eat;
	int				*forks;
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	mutex;
	struct timeval	start_time;
}t_input;

/**
 * @brief structur for each thread to  get the start information
 * 
 */
typedef struct s_philosophor{
	t_input			*input;
	unsigned int	name;
	unsigned int	right_fork;
	unsigned int	state;
	long			energy;
}t_philosophor;


//?-----------------THE_PROTOTYPS--------------?//

/**
 * @brief prints messasg about new state of a philosopher with timestamp 
 * 
 * @param philosopher current philosopher
 * @param str string that contains the new state 
 *
 * @return nothing
 */
void	statemessage(int pilosopher, char *str, struct timeval *start_time, t_philosophor *brain);

/**
 * @brief import the arg form the main in to the input struct
 *  or returns error if something is not  allowed
 * @todo everthing this is jst basic to test stuff
 * 
 */
void	transform_args(t_input *input);

/**
 * @brief create the threads the the data from input
 * 
 */
void	create_philo(t_input *input, unsigned int count);

/**
 * @brief returns the current timestamp 
 * 
 * @param start_time the starting time from when the start counting
 * @return returns the tim in ms stored in a long
 */
long	get_time_stamp(struct timeval *start_time);

void	thinking_cycle(t_philosophor *brain);
void parsing(int argc,char *argv[]);

#endif