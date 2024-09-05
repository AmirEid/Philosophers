/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 11:05:21 by amireid           #+#    #+#             */
/*   Updated: 2024/05/22 18:12:00 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	check_eaten_meals(t_session *session)
{
	if (!(session->num_meals % 2) && session->id_philo % 2
		&& session->num_meals > 0)
		usleep(10);
	if (session->num_meals % 2 && !(session->id_philo % 2)
		&& session->num_meals > 0)
		usleep(10);
}

static void	eating(t_session *session)
{
	ft_management(WAIT, &session->fork, session);
	writing_bitch_b(session, "has taken a fork");
	ft_management(WAIT, &session->fork, session);
	writing_bitch_b(session, "has taken a fork");
	ft_usleep(session, session->eat, "is eating");
	ft_management(POST, &session->fork, session);
	ft_management(POST, &session->fork, session);
}

static int	check_flag(t_session *session)
{
	pthread_mutex_lock(&session->mutex);
	if (session->outcome == 1)
	{
		session->flag = true;
		pthread_mutex_unlock(&session->mutex);
		return (1);
	}
	if (session->outcome == 2)
	{
		pthread_mutex_unlock(&session->mutex);
		return (1);
	}
	pthread_mutex_unlock(&session->mutex);
	return (0);
}

static void	start_session(t_session *session)
{
	if (pthread_mutex_init(&session->mutex, NULL) != 0)
		error_free(session);
	if (pthread_create(&session->big_brother, NULL, big_brother_watch, session))
		error_free(session);
	if (session->id_philo % 2)
		usleep(1000);
	while (1)
	{
		eating(session);
		ft_management(WAIT, &session->control, session);
		session->last_meal = get_time_micro(session);
		session->num_meals++;
		ft_management(POST, &session->control, session);
		if (check_flag(session))
			break ;
		ft_usleep(session, session->sleep, "is sleeping");
		writing_bitch_b(session, "is thinking");
		check_eaten_meals(session);
	}
	pthread_join(session->big_brother, NULL);
	check_exit_status(session);
}

void	philosophical_headache_b(t_session *session)
{
	int	i;

	i = -1;
	if (session->target_meals == 0)
		error_free(session);
	else if (session->num_philos == 1)
		dying_philo(session);
	else
	{
		session->start_session = get_time_micro(session);
		while (++i < session->num_philos)
		{
			session->pid[i] = fork();
			if (session->pid[i] == -1)
				error_free(session);
			if (session->pid[i] == 0)
			{
				session->id_philo = i + 1;
				session->last_meal = get_time_micro(session);
				start_session(session);
			}
		}
	}
}
