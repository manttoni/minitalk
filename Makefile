all: client server
	cc -Wall -Wextra -Werror server.c -o server
	cc -Wall -Wextra -Werror client.c ft_atoi.c -o client

clean:
	rm -f client server

re:
	clean all
