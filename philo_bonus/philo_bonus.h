/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 18:53:05 by aeid              #+#    #+#             */
/*   Updated: 2024/05/22 17:56:58 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <fcntl.h>
# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/errno.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum s_sem_code
{
	CLOSE,
	WAIT,
	POST,
}					t_sem_code;

typedef struct s_session
{
	int				num_philos;
	int				id_philo;
	int				*pid;
	long			num_meals;
	long			start_session;
	long			die;
	long			eat;
	long			sleep;
	long			target_meals;
	long			last_meal;
	sem_t			*fork;
	sem_t			*write;
	sem_t			*control;
	pthread_t		big_brother;
	int				outcome;
	pthread_mutex_t	mutex;
	bool			flag;
}					t_session;

void				check_n_parse(t_session *session, char **argv, int argc);
void				exit_message(t_session *session, char *error_message);
void				management_open(sem_t **semaphore, const char *name,
						int value, t_session *ses);
void				ft_management(t_sem_code code, sem_t **semaphore,
						t_session *ses);
void				management_unlink(const char *name, t_session *ses);
long				get_time_micro(t_session *session);
void				error_free(t_session *session);
void				philosophical_headache_b(t_session *session);
void				wait_then_clean(t_session **session);
void				writing_bitch_b(t_session *session, const char *message);
void				ft_usleep(t_session *session, long time, char *message);
int					check_death_full(int value, t_session *session);
void				dying_philo(t_session *session);
void				*big_brother_watch(void *data);
void				free_process(t_session *session);
void				free_parent(t_session *session);
void				check_exit_status(t_session *session);
#endif