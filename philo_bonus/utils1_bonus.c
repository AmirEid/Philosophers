/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 15:52:14 by aeid              #+#    #+#             */
/*   Updated: 2024/05/22 18:12:16 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	check_death_full(int value, t_session *session)
{
	int	result;

	result = 0;
	pthread_mutex_lock(&session->mutex);
	result = value;
	pthread_mutex_unlock(&session->mutex);
	return (result);
}

void	writing_bitch_b(t_session *session, const char *message)
{
	long	curr_time;

	curr_time = 0;
	pthread_mutex_lock(&session->mutex);
	if (session->outcome != 0)
	{
		pthread_mutex_unlock(&session->mutex);
		return ;
	}
	pthread_mutex_unlock(&session->mutex);
	ft_management(WAIT, &session->write, session);
	curr_time = get_time_micro(session) - session->start_session;
	printf("%-5ld %d %s\n", curr_time / 1000, session->id_philo, message);
	ft_management(POST, &session->write, session);
}

static void	writing_sadly(t_session *session, const char *message)
{
	long	curr_time;

	curr_time = get_time_micro(session) - session->start_session;
	printf("%-5ld %d %s\n", curr_time / 1000, session->id_philo, message);
}

void	dying_philo(t_session *session)
{
	session->pid = malloc(sizeof(int) * session->num_philos);
	if (!session->pid)
		exit_message(session, "memory error");
	session->start_session = get_time_micro(session);
	session->id_philo = 1;
	session->pid[0] = fork();
	if (session->pid[0] == -1)
		error_free(session);
	if (session->pid[0] == 0)
	{
		writing_sadly(session, "has taken a fork");
		while ((get_time_micro(session)
				- session->start_session) < session->die)
			;
		writing_sadly(session, "died");
		free(session->pid);
		free(session);
		exit(0);
	}
}
