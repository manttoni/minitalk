#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int confirm;

static void confirmation()
{
	confirm = 1;
}

static void send_char(char c, int pid)
{
	for (int i = 0; i < 8; ++i)
	{
		if (c & 1)
		{
			kill(pid, SIGUSR2);
		}
		else
		{
			kill(pid, SIGUSR1);
		}
		pause();
		confirm = 0;
		c = c >> 1;
	}
}

int main(int argc, char **argv)
{
	confirm = 0;
	int pid = atoi(argv[1]);
	char *message = argv[2];
	signal(SIGUSR1, confirmation);
	signal(SIGUSR2, confirmation);
	while (*message)
	{
		send_char(*message, pid);
		message++;
	}
	send_char('\0', pid);
}
