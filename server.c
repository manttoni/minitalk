/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 13:06:13 by amaula            #+#    #+#             */
/*   Updated: 2024/07/22 13:20:39 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct s_server
{
	unsigned char	byte;
	int				bits;
	int				sender_pid;
}	t_server;

t_server	g_server;

static void	handle_bit(int bit)
{
	if (bit == 0)
		g_server.bits++;
	else if (bit == 1)
	{
		g_server.byte = g_server.byte | (1 << g_server.bits);
		g_server.bits++;
	}
}

static void	handler(int sig, siginfo_t *si, void *unused)
{
	(void) unused;
	if (g_server.sender_pid == 0)
		g_server.sender_pid = si->si_pid;
	if (g_server.sender_pid != si->si_pid)
		return ;
	if (sig == SIGUSR2)
		handle_bit(1);
	else if (sig == SIGUSR1)
		handle_bit(0);
	kill(g_server.sender_pid, SIGUSR1);
	if (g_server.bits == 8)
	{
		write(1, &g_server.byte, 1);
		if (g_server.byte == '\0')
		{
			write(1, "\n", 1);
			g_server.sender_pid = 0;
		}
		g_server.byte = 0;
		g_server.bits = 0;
	}
}

static void	set_sigaction(void)
{
	struct sigaction	sa;
	sigset_t			set;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigaddset(&set, SIGUSR2);
	sa.sa_mask = set;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

static void	init_server(void)
{
	g_server.byte = 0;
	g_server.bits = 0;
	g_server.sender_pid = 0;
}

int	main(void)
{
	init_server();
	set_sigaction();
	printf("%d\n", getpid());
	while (1)
		pause();
	return (0);
}
