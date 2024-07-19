#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct s_server
{
	unsigned char	byte;
	int		bits;
	int		sender_pid;
	sigset_t	set;
	sigset_t	oldset;
} t_server;

t_server server;

static void zerobit()
{
	server.bits++;
}

static void onebit()
{
	server.byte = server.byte | (1 << server.bits);
	server.bits++;
}

static void handler(int sig, siginfo_t *si, void* unused)
{
	(void) unused;
	if (server.sender_pid == 0)
		server.sender_pid = si->si_pid;
	if (server.sender_pid != si->si_pid)
		return ;
	if (sig == SIGUSR2)
		onebit();
	else if (sig == SIGUSR1)
		zerobit();
	kill(server.sender_pid, SIGUSR1);
	if (server.bits == 8)
	{
		write(1, &server.byte, 1);
		if (server.byte == '\0')
		{
			write(1, "\n", 1);
			server.sender_pid = 0;
		}
		server.byte = 0;
		server.bits = 0;
	}
}

static void set_sigaction()
{
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&server.set);
	sigaddset(&server.set, SIGUSR1);
	sigaddset(&server.set, SIGUSR2);
	sa.sa_mask = server.set;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

static void init_server()
{
	server.byte = 0;
	server.bits = 0;
	server.sender_pid = 0;
}

int main(void)
{
	init_server();
	set_sigaction();
	printf("%d\n", getpid());
	while(1)
		pause();
	return 0;
}
