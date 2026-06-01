/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafzal <mafzal@student.42warsaw.pl>         +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/01 16:27:58 by mafzal            #+#    #+#             */
/*   Updated: 2026/06/01 22:10:00 by mafzal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;

# define RED "\033[31m"
# define GREEN "\033[32m"
# define YELLOW "\033[33m"
# define BLUE "\033[34m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define RESET "\033[0m"

# define DEBUG_MODE 0

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}						t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND
}						t_time_code;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKEN_FIRST_FORK,
	TAKEN_SECOND_FORK,
	DEAD
}						t_philo_status;

typedef struct s_fork
{
	int					fork_id;
	t_mutex				fork;
}						t_fork;

typedef struct s_philo
{
	int					ph_id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mutex				philo_mutex;
	t_table				*table;
}						t_philo;

typedef struct s_table
{
	long				num_philos;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				num_meals_required;
	long				simulation_start_time;
	long				simulation_end_time;
	long				thread_running_count;
	bool				all_thread_ready;
	bool				simulation_should_end;
	t_mutex				table_mutex;
	t_mutex				write_mutex;
	pthread_t			monitor;
	t_philo				*philos;
	t_fork				*forks;
}						t_table;

/* parsing.c */
int						is_space(char c);
int						is_digit(const char *str);
int						is_digit_space(const char *str);
long					ft_atol(const char *str);
void					parse_input(char **argv, t_table *table);
const char				*validate_input(const char *str);

/* safe helpers */
void					*safe_malloc(size_t size);
void					safe_mutex_handler(t_mutex *mutex, t_opcode opcode);
void					handler_mutex_error(int status, t_opcode opcode);
void					safe_thread_handler(pthread_t *thread,
							void *(*start_routine)(void *), void *data,
							t_opcode opcode);
void					handler_thread_error(int status, t_opcode opcode);

/* init.c */
void					philo_init(t_table *table);
void					data_init(t_table *table);
void					assign_forks(t_philo *philo, t_fork *forks, int index);

/* lock_unlock.c */
void					set_bool_value(t_mutex *mutex, bool *flag, bool value);
void					set_long_value(t_mutex *mutex, long *var, long value);
long					get_long_value(t_mutex *mutex, long *var);
bool					get_bool_value(t_mutex *mutex, bool *value);
bool					simulation_start(t_table *table);
bool					simulation_end(t_table *table);
void					wait_all_thread_ready(t_table *table);

/* dining.c / dining_utils.c */
void					*dinner_simulation(void *data);
void					dinner_start(t_table *table);
void					eating(t_philo *philo);
void					thinking(t_philo *philo, bool pre_simulation);
void					sleeping(t_philo *philo);
void					cleanup(t_table *table);

/* utils.c */
void					error_exit(const char *message);
long					get_time_in_ms(t_time_code time_code);
void					precision_usleep(long duration_in_ms, t_table *table);

/* write_mutex.c */
void					write_mutex(t_philo_status status, t_philo *philo,
							bool debug);
void					write_status_debug(t_philo_status status,
							t_philo *philo, long elasped_time);

/* syncro_utils.c */
void					increment_long(t_mutex *mutex, long *value);
bool					all_thread_running(t_mutex *mutex,
							long *thread_running_count, long num_philos);

/* monitor.c */
void					*monitor_dinner(void *data);
bool					philo_is_dead(t_philo *philo);

#endif
