/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/03 13:26:37 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned int g_res;

void	set_client_pid(int signum, siginfo_t *info, void *ptr)
{
	(void) ptr;
	(void) signum;
	g_res = info->si_pid;
}

void	handler(int signum)
{
	g_res = g_res << 1;
	// if (signum == SIGUSR1)
	// {
	// 	write(1, "0", 1);
	// }
	if (signum == SIGUSR2)
	{
		// write(1, "1", 1);
		g_res = g_res + 1;
	}
}

// int	main(int argc, char const *argv[])
int	main(void)
{
	struct sigaction	sa1;
	int					i;
	pid_t				pid;
	pid_t				client_pid;

	pid = getpid();
	printf("%d\n", pid);
	sa1.__sigaction_u.__sa_sigaction = set_client_pid;
	sa1.sa_flags = SA_SIGINFO;
	i = 8;
	g_res = 0;
	sigaction(SIGUSR1, &sa1, NULL);
	pause();
	sigemptyset(&sa1.sa_mask);
	sa1.sa_handler = SIG_DFL;
	if (sigaction(SIGUSR1, &sa1, NULL) < 0)
	{
		perror("sigaction");
		return (EXIT_FAILURE);
	}
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	usleep(100);
	kill(g_res, SIGUSR1);
	client_pid = g_res;
	g_res = 0;
	while (i--)
	{
		pause();
	}
	ft_printf("received from client %d: %c\n", client_pid, g_res);
	return (0);
}
