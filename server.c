#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

typedef struct s
{
	unsigned char byte;
	int bits;
} character;

character next;

static void zerobit()
{
	next.bits++;
}

static void onebit()
{
	next.byte = next.byte | (1 << next.bits);
	next.bits++;
}

static void handler(int sig, siginfo_t *si, void *unused)
{
	if (sig == SIGUSR2)
	{
		onebit();
		kill(si->si_pid, SIGUSR2);
	}
	if (sig == SIGUSR1)
	{
		zerobit();
		kill(si->si_pid, SIGUSR1);
	}
	if (next.bits == 8)
	{
		next.bits = 0;
		write(1, &next.byte, 1);
		if (next.byte == '\0')
			write(1, "\n", 1);
		next.byte = 0;
	}
}

int main(void)
{
	int pid = getpid();
	printf("%d\n", pid);
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	next.byte = 0;
	next.bits = 0;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while(1)
		pause();
	return 0;
}
