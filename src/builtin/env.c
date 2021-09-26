/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:24:31 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/26 09:50:54 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	env(const char *path, char *const argv[], char *const envp[])
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
