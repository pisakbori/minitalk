/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/03 15:02:15 by bpisak-l         ###   ########.fr       */
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
	if (signum == SIGUSR2)
		g_res = g_res + 1;
}

void set_client_pid_form_signal()
{
	struct sigaction	sa1;

	sa1.__sigaction_u.__sa_sigaction = set_client_pid;
	sa1.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa1, NULL);
	pause();
	sigemptyset(&sa1.sa_mask);
	sa1.sa_handler = SIG_DFL;
	sigaction(SIGUSR1, &sa1, NULL);
	// if (sigaction(SIGUSR1, &sa1, NULL) < 0)
	// {
	// 	perror("sigaction");
	// 	return (EXIT_FAILURE);
	// }
}

int	init_connection()
{
	pid_t				client_pid;

	set_client_pid_form_signal();
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	usleep(100);
	client_pid = g_res;
	kill(client_pid, SIGUSR1);
	return (client_pid);
}

void	confirm_received(pid_t	client_pid)
{
	ft_printf("received from client %d: %c\n", client_pid, g_res);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	usleep(1000);
	kill(client_pid, SIGUSR1);
}

// int	main(int argc, char const *argv[])
int	main(void)
{
	int					i;
	pid_t				pid;
	pid_t				client_pid;

	pid = getpid();
	printf("%d\n", pid);
	//loop here forever for waiting for msg from different clients
	client_pid = init_connection();
	while (g_res) //end of string
	{
		i = 8;
		g_res = 0;
		while (i--)
		{
			pause();
		}
		confirm_received(client_pid);
	}
	return (0);
}
