CC				= cc 
CFLAGS			= -Wall -Werror -Wextra -I./libft
LIBFT_FLAGS		= -Llibft
LFLAGS			= $(LIBFT_FLAGS)
RM				= rm -rf
MINILIBX		= mlx/libmlx.a
LIBFT			= libft/libft.a
NAME			= minitalk
TEST_MSG		= @./server & server_pid=$$! && ./client $$server_pid "$$(cat msg.txt)" && kill $$server_pid;

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) client server

test: $(NAME)
	$(TEST_MSG)

client: $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) client.c -o client $(LIBFT)

server: $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) server.c -o server $(LIBFT)

$(LIBFT):
	make -C libft

bonus: $(OBJS) $(LIBFT) client server

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf client
	rm -rf server

re: fclean all

.PHONY: all clean bonus re fclean libft client server test
