/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:39:36 by lkrabbe           #+#    #+#             */
/*   Updated: 2022/11/06 21:11:00 by lkrabbe          ###   ########.fr       */
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

# define TOOK_L_FORK "has taken a the left fork"
# define TOOK_R_FORK "has taken a the right fork"
# define EATING  "is eating"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DEAD "died"
# ifndef FALSE
#  define FALSE 0
# endif
# ifndef TRUE
#  define TRUE 1
# endif
# ifndef INT32_MAX
#  define INT32_MAX 2147483647
# endif
//?-------------------THE_ENUMS----------------?//

typedef enum e_state{
	thinking = 1,
	sleeping = 2,
	eating = 3,
	dead = 4,
}t_state;

/**
 * @brief The diffrent mutexlocks that arent for forks
 * 
 *! @note last_lock needs to be at the lost position \
 *! its like a counter for the locks 
 *! its needed to malloc the correct size for the array of mutexes
 */
typedef enum e_mutex_locks{
	start_check = 0,
	death_check,
	print_check,
	last_lock,
}t_mutex_locks;

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
	pthread_mutex_t	*mutex_arr;
	struct timeval	start_time;
	int				*deat_occurred;
}t_input;

/**
 * @brief structur for each thread to  get the start information
 * 
 */
typedef struct s_phil{
	t_input			*input;
	int				name;
	int				right_fork;
	int				state;
	long			energy;
	struct timeval	start_time;
	struct timeval	death_time;
	int				death_flag;
}t_phil;

//?-----------------THE_PROTOTYPS--------------?//

/**
 * @brief prints messasg about new state of a philosopher with timestamp 
 * 
 * @param brain current philosopher
 * @param str string that contains the new state 
 *
 * @return nothing
 */
void	statemessage(char *str, t_phil *brain);
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

void	thinking_cycle(t_phil *brain);
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

#endif