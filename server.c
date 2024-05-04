/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/04 14:51:25 by bpisak-l         ###   ########.fr       */
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

void	set_client_pid_form_signal(void)
{
	struct sigaction	sa1;

	sa1.__sigaction_u.__sa_sigaction = set_client_pid;
	sa1.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa1, NULL);
	pause();
	sigemptyset(&sa1.sa_mask);
	sa1.sa_handler = SIG_DFL;
	sigaction(SIGUSR1, &sa1, NULL);
}

int	init_connection()
{
	pid_t	client_pid;

	set_client_pid_form_signal();
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	client_pid = g_res;
	kill(client_pid, SIGUSR1);
	return (client_pid);
}

void	approve_send_next_bit(pid_t	client_pid)
{
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
	while(1)
	{
		client_pid = init_connection();
		while (g_res) //end of string
		{
			i = 8;
			g_res = 0;
			while (i--)
			{
				pause();
				approve_send_next_bit(client_pid);
			}
			ft_printf("%c", g_res);
		}
		ft_printf("\n");
	}
	return (0);
}
