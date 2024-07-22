# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Client
CLIENT_NAME = client
CLIENT_SRCS = client.c ft_atoi.c
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

# Server
SERVER_NAME = server
SERVER_SRCS = server.c
SERVER_OBJS = $(SERVER_SRCS:.c=.o)

# Rules
all: $(CLIENT_NAME) $(SERVER_NAME)

$(CLIENT_NAME): $(CLIENT_OBJS)
	$(CC) $(CFLAGS) -o $(CLIENT_NAME) $(CLIENT_OBJS)

$(SERVER_NAME): $(SERVER_OBJS)
	$(CC) $(CFLAGS) -o $(SERVER_NAME) $(SERVER_OBJS)

clean:
	rm -f $(CLIENT_OBJS) $(SERVER_OBJS)

fclean: clean
	rm -f $(CLIENT_NAME) $(SERVER_NAME)

re: fclean all

# Dependencies
client.o: client.c client.h
ft_atoi.o: ft_atoi.c client.h
server.o: server.c

.PHONY: all clean fclean re

