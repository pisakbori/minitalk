/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpisak-l <bpisak-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:31:16 by bpisak-l          #+#    #+#             */
/*   Updated: 2024/05/01 15:57:20 by bpisak-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int globalVariable;

void sig_handler(int signum){
  printf("\nInside handler function, %d\n", signum);
//   signal(SIGINT, SIG_DFL);   // Re Register signal handler for default action
}

// int	main(int argc, char const *argv[])
int	main(void)
{
	pid_t pid = getpid();
	signal(SIGUSR1, sig_handler);
    printf("%d\n", pid);
	while (1)
	{
		pause();
	}
	return (0);
}
