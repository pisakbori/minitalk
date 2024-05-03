/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:23 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/03 11:37:11 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// int globalVariable;

void	send_char(char c, pid_t server_pid)
{
	char	bit;
	char	i;

	i = 8;
	ft_printf("sending char %d\n", c);
	while (i--)
	{
		bit = c & 0b10000000;
		ft_printf("bit: %d\n", !!(c & 0b10000000));
		// ft_printf("%d", !!(c & 0b10000000));
		if (!bit)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(100);
		c = c << 1;
	}
}


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

int	main(int argc, char const *argv[])
{
	pid_t	server_pid;
	char	*msg;

	msg = NULL;
	if (!args_valid(argc, argv, &msg))
		return (1);
	server_pid = (pid_t)ft_atoi(argv[1]);
	msg = ft_strdup("heya hey");
	send_char(msg[0], server_pid);
	free(msg);
	// kill(server_pid, SIGUSR1);
	return (0);
}
