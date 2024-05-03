/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:23 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/03 15:01:41 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// int globalVariable;

int	args_valid(int argc, char const *argv[], char **msg)
{
	if (argc != 3)
	{
		// ft_printf("Correct usage: ./client <server pid> <message string>\n");
		// return (0);
		return (1);
	}
	*msg = ft_strdup(argv[2]);
	return (1);
}

void	send_char(char c, pid_t server_pid)
{
	char	bit;
	char	i;

	i = 8;
	ft_printf("sending char %d\n", c);
	while (i--)
	{
		bit = c & 0b10000000;
		if (bit)
			kill(server_pid, SIGUSR2);
		else
			kill(server_pid, SIGUSR1);
		usleep(100);
		c = c << 1;
	}
	ft_printf("char sent\n");
}

void	handler(int signum)
{
	ft_printf("signal from server %d\n", signum);
	(void)signum;
}

int	main(int argc, char const *argv[])
{
	pid_t	server_pid;
	pid_t	own_pid;
	char	*msg;
	int		i;

	own_pid = getpid();
	ft_printf("client pid %d\n", own_pid);
	msg = NULL;
	if (!args_valid(argc, argv, &msg))
		return (1);
	server_pid = (pid_t)ft_atoi(argv[1]);
	kill(server_pid, SIGUSR1);
	signal(SIGUSR1, handler);
	pause();
	msg = ft_strdup("heya hey");
	i = -1;
	while (msg[++i])
	{
		signal(SIGUSR1, handler);
		usleep(100);
		send_char(msg[i], server_pid);
		ft_printf("after usleep, waiting for confirm from srv\n");
		pause();
		ft_printf("after pause\n");
	}
	ft_printf("before sending null terminator\n");
	send_char(0, server_pid);
	free(msg);
	// kill(server_pid, SIGUSR1);
	return (0);
}
