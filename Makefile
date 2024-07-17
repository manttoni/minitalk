all:
	cc -Wall -Wextra -Werror server.c -o server
	cc -Wall -Wextra -Werror client.c -o client
