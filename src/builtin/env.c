/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:24:31 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/25 20:39:00 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	env(const char *path, char *const argv[], char *const envp[])
{
	int	idx;

	idx = 0;
	if (argv[1])
		is_error("env : ", argv[1], ": env in minishell takes no arguments\
				or options", EXIT_FAILURE);
	while (envp[idx])
		printf("%s\n", envp[idx++]);
	exit(EXIT_SUCCESS);
}
