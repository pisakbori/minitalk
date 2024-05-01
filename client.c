/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:23 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/01 15:55:58 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

// int globalVariable;

int main(int argc, char const *argv[])
{
	pid_t	server_pid;
	char	*msg;

	if (argc != 3)
	{
		ft_printf("Correct usage: ./client <server pid> <message string>\n");
		return (1);
	}
	server_pid = ft_atoi(argv[1]);
	msg = ft_strdup(argv[2]);
	free(msg);
	kill(server_pid, SIGUSR1);
	return (0);
}
