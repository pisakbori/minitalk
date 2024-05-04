/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:23 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/04 14:56:00 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// int g_var;

int	args_valid(int argc, char const *argv[], char **msg)
{
	if (argc != 3)
		return (1);
	*msg = ft_strdup(argv[2]);
	return (1);
}

void	send_char(char c, pid_t server_pid)
{
	char	bit;
	char	i;

	i = 8;
	while (i--)
	{
		bit = c & 0b10000000;
		pause();
		if (bit)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		c = c << 1;
	}
}

void	handler(int signum)
{
	// g_var = signum;
	(void)signum;
	usleep(35);
}

int	main(int argc, char const *argv[])
{
	pid_t	server_pid;
	pid_t	own_pid;
	char	*msg;
	int		i;

	usleep(100); // if starts at same time as server..?
	signal(SIGUSR1, handler);
	own_pid = getpid();
	msg = NULL;
	if (!args_valid(argc, argv, &msg))
		return (1);
	server_pid = (pid_t)ft_atoi(argv[1]);
	kill(server_pid, SIGUSR1);
	msg = ft_strdup("yaheya heyaheya heyaheya heyaheyaa heyaheya heyaheya heyaheyayaheya heyaheya heyaheya heyaheya heyaheya heyaheya heyaheyayaheya heyaheya heyaheya a heyaheya heyaheya heyaheyayaheya heyaheya heyaheya heyaheya heyaheya heyaheya heyaheyaa heyaheya heyaheya heyaheyayaheya heyaheya heyaheya heyaheya heyaheya heyaheya heyaheyaa heyaheya heyaheya heyaheyayaheya heyaheya heyaheya heyaheya heyaheya heyaheya heyaheyaa heyaheya heyaheya heyaheyayaheya heyaheya heyaheya heyaheyaheya 8\n");
	i = -1;
	while (msg[++i])
		send_char(msg[i], server_pid);
	send_char(0, server_pid);
	free(msg);
	return (0);
}
