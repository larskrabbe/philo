/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe < lkrabbe@student.42heilbronn.d    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:39:36 by lkrabbe           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/10/27 05:35:27 by lkrabbe          ###   ########.fr       */
=======
/*   Updated: 2022/10/26 13:30:52 by lkrabbe          ###   ########.fr       */
>>>>>>> 38b02daa9c1d717c692eadf28a82a2d785898789
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
	int				philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				amount_to_eat;
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
	int				name;
	int				right_fork;
	int				state;
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
void	statemessage(int pilosopher, char *str, \
struct timeval *start_time, t_philosophor *brain);

/**
 * @brief import the arg form the main in to the input struct
 *  or returns error if something is not  allowed
 * @todo everthing this is jst basic to test stuff
 * 
 */
void	transform_args(t_input *input, int argc, char *argv[]);

/**
 * @brief create the threads the the data from input
 * 
 */
void	create_philo(t_input *input, int count);

/**
 * @brief returns the current timestamp 
 * 
 * @param start_time the starting time from when the start counting
 * @return returns the tim in ms stored in a long
 */
long	get_time_stamp(struct timeval *start_time);

void	thinking_cycle(t_philosophor *brain);
<<<<<<< HEAD
/**
 * @brief gives you a pointer to the next arg separated by whitespace or \0
 * 
 * @param argv the pointer to the start of the arguments
 * @param argc the amount of args
 * 
 * @return returns a pointer to the start of the argument
 */
char	*get_next_arg(int argc, char *argv[]);

/**
 * @brief returns 1 or 0 depending if char is a whitespace char
 * 
 */
int		is_white_space(int a);
=======
void parsing(int argc,char *argv[]);
>>>>>>> 38b02daa9c1d717c692eadf28a82a2d785898789

#endif