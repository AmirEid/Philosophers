/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeid <aeid@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:21:53 by aeid              #+#    #+#             */
/*   Updated: 2024/05/22 18:07:31 by aeid             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_valid_input(char *str)
{
	int	i;

	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+')
		i++;
	if (str[i] == '-')
		exit_message("We don't accept negativity");
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i])
		exit_message("seriously??");
}

static long	ft_atol(char *str)
{
	long	number;
	int		i;

	i = -1;
	number = 0;
	while (str[++i])
		number = (number * 10) + (str[i] - '0');
	return (number);
}

static void	more_checks(t_session *session)
{
	session->flag_start = false;
	if (session->nbr_philo == 0)
		exit_message("No philosophers, no wisdom!");
	if (session->nbr_philo > 200)
		exit_message("Too much wisdom for today!");
	if (session->time_to_die < 60000 || session->time_to_eat < 60000
		|| session->time_to_sleep < 60000)
		exit_message("What the hell man!, try more than 59ms");
}

void	check_n_parse(t_session *session, char **argv, int argc)
{
	int		i;
	long	str[5];

	i = 0;
	while (argv[++i])
	{
		check_valid_input(argv[i]);
		str[i - 1] = ft_atol(argv[i]);
		if (str[i - 1] > INT_MAX)
			exit_message("It is too big, smartass!");
	}
	session->nbr_philo = str[0];
	session->time_to_die = str[1] * 1000;
	session->time_to_eat = str[2] * 1000;
	session->time_to_sleep = str[3] * 1000;
	if (argc == 6)
		session->target_meals = str[4];
	else
	{
		session->target_meals = -1;
		str[4] = 0;
	}
	more_checks(session);
}
