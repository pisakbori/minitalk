/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/03 11:38:07 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned char g_res;

void	handler(int signum)
{
	g_res = g_res << 1;
	if (signum == SIGUSR1)
	{
		write(1, "0", 1);
	}
	if (signum == SIGUSR2)
	{
		write(1, "1", 1);
		g_res = g_res + 1;
	}
}

// int	main(int argc, char const *argv[])
int	main(void)
{
	// struct sigaction	sa1;
	// struct sigaction	sa2;

	int	i;
	pid_t pid = getpid();
	printf("%d\n", pid);
	// sa1.sa_handler = sig_0;
	// sa1.sa_flags = SA_SIGINFO;
	// sa2.sa_handler = sig_1;
	// sa2.sa_flags = SA_SIGINFO;

	// if (sigaction(SIGUSR1, &sa1, NULL) == -1) 
	// {
	// 	perror("sigaction1");
	// 	return (EXIT_FAILURE);
	// }
	// if (sigaction(SIGUSR2, &sa2, NULL) == -1) 
	// {
	// 	perror("sigaction2");
	// 	return (EXIT_FAILURE);
	// }
	i = 8;
	g_res = 0;
	ft_printf("g_res at start: %d\n", g_res);
	signal(SIGUSR1, handler);
	signal(SIGUSR2, handler);
	usleep(100);
	while (i--)
	{
		pause();
	}
	write(1, "\n", 1);
	ft_printf("g_res in the end: %d\n", g_res);
	ft_printf("%c\n" ,g_res);
	return (0);
}