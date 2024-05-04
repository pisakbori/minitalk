CC      		= cc 
CFLAGS			= -Wall -Werror -Wextra -I./libft
LIBFT_FLAGS		= -Llibft
LFLAGS			= $(LIBFT_FLAGS)
RM      		= rm -rf
SRC				=
OBJS			= $(SRC:.c=.o)
MINILIBX		= mlx/libmlx.a
LIBFT			= libft/libft.a
NAME			= minitalk

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) client server
	@./server & server_pid=$$! && ./client $$server_pid "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa 70"

client: $(LIBFT)
	@$(CC) $(CFLAGS) $(LFLAGS) client.c -o client $(OBJS) $(LIBFT)

server: $(LIBFT)
	@$(CC) $(CFLAGS) $(LFLAGS) server.c -o server $(OBJS) $(LIBFT)

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf client
	rm -rf server

re: fclean all

.PHONY: all clean bonus re fclean libft client server
