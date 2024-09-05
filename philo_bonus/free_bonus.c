/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:51:51 by aeid              #+#    #+#             */
/*   Updated: 2024/05/22 18:12:03 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	free_parent(t_session *session)
{
	ft_management(CLOSE, &session->fork, session);
	ft_management(CLOSE, &session->write, session);
	ft_management(CLOSE, &session->control, session);
	management_unlink("/block_fork", session);
	management_unlink("/block_write", session);
	management_unlink("/block_control", session);
}

void	check_exit_status(t_session *session)
{
	if (session->flag)
	{
		free_process(session);
		exit(0);
	}
	else
	{
		free_process(session);
		exit(1);
	}
}

void	free_process(t_session *session)
{
	pthread_mutex_destroy(&session->mutex);
	ft_management(CLOSE, &session->fork, session);
	ft_management(CLOSE, &session->write, session);
	ft_management(CLOSE, &session->control, session);
	free(session->pid);
	free(session);
}
