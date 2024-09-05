/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:53:05 by aeid              #+#    #+#             */
/*   Updated: 2024/05/15 22:36:01 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
//define all the error messages and the limits of time //
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_session	t_session;

typedef struct s_fork
{
	int						id_fork;
	pthread_mutex_t			fork;
}							t_fork;

typedef struct s_philo
{
	int						id_philo;
	long					num_meals;
	long					time_since_meal;
	long					die;
	long					eat;
	long					sleep;
	long					target;
	long					start;
	t_fork					*fork_one;
	t_fork					*fork_two;
	pthread_t				id_thread;
	t_session				*session;
	pthread_mutex_t			philos_mutex;
	pthread_t				big_brother;
}							t_philo;

struct						s_session
{
	long					nbr_philo;
	long					time_to_die;
	long					time_to_eat;
	long					time_to_sleep;
	long					target_meals;
	long					start;
	bool					the_end;
	bool					flag_start;
	bool					end_session;
	pthread_mutex_t			session_mutex;
	pthread_mutex_t			writing_mutex;
	pthread_mutex_t			end_all;
	t_fork					*forks;
	t_philo					*philos;
};

void						exit_message(char *error_message);
void						check_n_parse(t_session *session, char **argv,
								int argc);
void						initialize_kraken(t_session *session);
void						philosophical_headache(t_session *session);
void						error_free(char *error_message, t_session *session);
void						cleaning_lady(t_session *session);
long						get_time_micro(t_session *session);
bool						check_if_all_ready(t_session *session);
bool						check_if_simulation_ended(t_session *session);
void						writing_bitch(t_philo *philo, char *message);
void						ft_usleep(t_session *session, long time,
								t_philo *philo, char *message);
void						check_eaten_meals(t_philo *philo);
void						*big_brother_watch(void *data);
void						set_mutex(pthread_mutex_t *mutex, bool *dest,
								bool value);
void						get_time_safe(pthread_mutex_t *mutex, long *time,
								t_session *session, long start);
void						*mr_lonely(void *data);
void						join_thread(pthread_t *thread, t_session *session);
#endif