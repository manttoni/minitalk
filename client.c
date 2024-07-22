/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:29:44 by amaula            #+#    #+#             */
/*   Updated: 2024/07/22 13:40:00 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "client.h"

volatile sig_atomic_t	g_confirm;

static void	confirmation(int signum)
{
	if (signum == SIGUSR1)
		g_confirm = 1;
}

static void	send_char(char c, int pid)
{
	int	sig;
	int	bits;

	bits = 8;
	while (bits-- > 0)
	{
		if (c & 1)
			sig = SIGUSR2;
		else
			sig = SIGUSR1;
		while (!g_confirm)
		{
			kill(pid, sig);
			usleep(1000);
		}
		g_confirm = 0;
		c = c >> 1;
	}
}

int	main(int argc, char **argv)
{
	int		pid;
	char	*message;

	if (argc != 3)
		return (1);
	g_confirm = 0;
	pid = ft_atoi(argv[1]);
	message = argv[2];
	signal(SIGUSR1, confirmation);
	while (*message)
	{
		send_char(*message, pid);
		message++;
	}
	send_char('\0', pid);
}
