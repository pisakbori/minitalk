/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/07 18:35:12 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned int	g_res;

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
	usleep(35);
	pause();
	kill(g_res, SIGUSR1);
	pause();
	sigemptyset(&sa1.sa_mask);
	sa1.sa_handler = SIG_DFL;
	sigaction(SIGUSR1, &sa1, NULL);
}

int	init_connection(void)
{
	pid_t	client_pid;

	set_client_pid_form_signal();
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	usleep(35);
	client_pid = g_res;
	ft_printf("%d : ", client_pid);
	kill(client_pid, SIGUSR1);
	return (client_pid);
}

int	main(void)
{
	int				i;
	pid_t			pid;
	pid_t			client_pid;

	pid = getpid();
	ft_printf("%d\n", pid);
	while (1)
	{
		client_pid = init_connection();
		while (g_res)
		{
			i = 8;
			g_res = 0;
			while (i--)
			{
				pause();
				usleep(70);
				kill(client_pid, SIGUSR1);
			}
			write(1, &g_res, 1);
		}
		kill(client_pid, SIGUSR2);
		ft_printf("\n");
	}
	return (0);
}
