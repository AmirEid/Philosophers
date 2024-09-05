/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 02:37:43 by amireid           #+#    #+#             */
/*   Updated: 2024/05/22 18:12:14 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_time_micro(t_session *session)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		error_free(session);
	return ((time.tv_sec * 1000000) + (time.tv_usec));
}

void	ft_usleep(t_session *session, long time, char *message)
{
	long	start;

	start = get_time_micro(session);
	writing_bitch_b(session, message);
	while (get_time_micro(session) - start < time)
		;
}

void	exit_message(t_session *session, char *error_message)
{
	printf("%s\n", error_message);
	free(session);
	exit(EXIT_FAILURE);
}

void	error_free(t_session *session)
{
	if (session->fork)
	{
		ft_management(CLOSE, &session->fork, session);
		management_unlink("/block_fork", session);
	}
	if (session->write)
	{
		ft_management(CLOSE, &session->write, session);
		management_unlink("/block_write", session);
	}
	if (session->control)
	{
		ft_management(CLOSE, &session->control, session);
		management_unlink("/block_sem", session);
	}
	free(session->pid);
	free(session);
	exit(EXIT_FAILURE);
}

void	wait_then_clean(t_session **session)
{
	int	i;
	int	status;

	i = -1;
	while (++i < (*session)->num_philos)
	{
		waitpid(-1, &status, 0);
		if (status == 1)
		{
			i = -1;
			while (++i < (*session)->num_philos)
			{
				if (kill((*session)->pid[i], SIGKILL) != 0)
					error_free(*session);
			}
		}
	}
	if ((*session)->num_philos != 1)
		free_parent(*session);
	free((*session)->pid);
	free(*session);
}
