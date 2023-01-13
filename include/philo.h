/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkrabbe <lkrabbe@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 22:39:36 by lkrabbe           #+#    #+#             */
/*   Updated: 2023/01/12 09:32:02 by lkrabbe          ###   ########.fr       */
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

# define TOOK_L_FORK "has taken a fork"
# define TOOK_R_FORK "has taken a fork"
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
/**
 * @brief The diffrent mutexlocks that arent for forks
 * 
 *! @note last_lock needs to be at the lost position \
 *! its like a counter for the locks 
 *! its needed to malloc the correct size for the array of mutexes
 */
typedef enum e_mutex_locks{
	death_check,
	end,
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
	pthread_mutex_t	*fork_mutex;
	pthread_mutex_t	*mutex_arr;
	struct timeval	start_time;
	long			*death_check;
	int				*deat_occurred;
	int				*end;
}t_input;

/**
 * @brief structur for each thread to  get the start information
 * 
 */
typedef struct s_phil{
	t_input			*input;
	int				name;
	pthread_mutex_t	*l_fork_mutex;
	pthread_mutex_t	*r_fork_mutex;
	struct timeval	start_time;
	int				death_flag;
	long			*death_check;
	int				eat_count;
	int				(*check_fork)(struct s_phil*);
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
void			statemessage(char *str, t_phil *brain);
/**
 * @brief import the arg form the main in to the input struct
 *  or returns error if something is not  allowed
 * @todo everthing this is jst basic to test stuff
 * 
 */
int				transform_args(t_input *input, int argc, char *argv[]);

/**
 * @brief create the threads the the data from input
 * 
 */
int				setup(t_input *input, int count);

/**
 * @brief returns the current timestamp 
 * 
 * @param start_time the starting time from when the start counting
 * @return returns the tim in ms stored in a long
 */
long			get_time_stamp(struct timeval *start_time);

void			thinking_cycle(t_phil *brain);
/**
 * @brief gives you a pointer to the next arg separated by whitespace or \0
 * 
 * @param argv the pointer to the start of the arguments
 * @param argc the amount of args
 * 

 * @return returns a pointer to the start of the argument
 */
char			*get_next_arg(int argc, char *argv[]);

/**
 * @brief returns 1 or 0 depending if char is a whitespace char
 * 
 */
int				is_white_space(int a);

int				check_fork_odd(t_phil *phil);
int				check_fork_even(t_phil *phil);
int				wait_until(struct timeval *time);
void			time_plus_mili(struct timeval *time, suseconds_t add);
long			get_time_stamp(struct timeval *start_time);
void			*lifecycle(void *param);

void			eatmessage(char *str, t_phil *brain);

//?-----philo_setup.c------?//

void			philo_input(t_input *input, t_phil *brain, int count);

//?-----time.c------?//

void			milisleep(long long time);
int				dinner_for_one(t_input *input);
int				check_input(t_input *input);
pthread_mutex_t	*get_mutex_array(size_t len);
void			monitor(t_input *input);

#endif