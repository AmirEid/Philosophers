/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 16:01:56 by aeid              #+#    #+#             */
/*   Updated: 2024/05/22 18:12:09 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	change_outcome(t_session *session, int outcome)
{
	ft_management(POST, &session->control, session);
	pthread_mutex_lock(&session->mutex);
	session->outcome = outcome;
	pthread_mutex_unlock(&session->mutex);
}

static int	check_meals(t_session *session)
{
	ft_management(WAIT, &session->control, session);
	if (session->target_meals && session->num_meals == session->target_meals)
	{
		change_outcome(session, 1);
		return (1);
	}
	ft_management(POST, &session->control, session);
	return (0);
}

static int	check_death(t_session *session)
{
	long	curr_time;

	curr_time = 0;
	ft_management(WAIT, &session->control, session);
	curr_time = get_time_micro(session) - session->last_meal;
	if (curr_time >= session->die)
	{
		writing_bitch_b(session, "died");
		change_outcome(session, 2);
		return (1);
	}
	ft_management(POST, &session->control, session);
	return (0);
}

void	*big_brother_watch(void *data)
{
	t_session	*session;

	session = (t_session *)data;
	while (1)
	{
		usleep(100);
		if (check_meals(session))
			break ;
		if (check_death(session))
			break ;
	}
	return (NULL);
}
