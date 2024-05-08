/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:23 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/08 13:13:45 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned int	g_server_exists;

void	validate_pid(pid_t pid, const char *arg)
{
	if (ft_strncmp(ft_itoa(pid), arg, ft_strlen(arg)) || pid <= 0)
	{
		write(2, "Invalid server pid.\n", 20);
		exit (1);
	}
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
	if (signum == SIGUSR2)
		ft_printf("(Seen)\n");
	else
	{
		g_server_exists = 1;
		usleep(40);
	}
}

void	finalize(pid_t	server_pid)
{
	send_char(0, server_pid);
	signal(SIGUSR1, SIG_IGN);
	signal(SIGUSR2, handler);
	pause();
}

int	main(int argc, char const *argv[])
{
	pid_t	server_pid;
	int		i;

	g_server_exists = 0;
	if (argc != 3)
	{
		write(2, "Correct usage: ./client <server_pid> <message_string>\n", 54);
		return (1);
	}
	signal(SIGUSR1, handler);
	server_pid = (pid_t)ft_atoi(argv[1]);
	validate_pid(server_pid, argv[1]);
	kill(server_pid, SIGUSR1);
	usleep(100);
	if (!g_server_exists)
	{
		write(2, "Error: Server is not available.\n", 30);
		return (1);
	}
	kill(server_pid, SIGUSR1);
	i = -1;
	while (argv[2][++i])
		send_char(argv[2][i], server_pid);
	finalize(server_pid);
	return (0);
}
