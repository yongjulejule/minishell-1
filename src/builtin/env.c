/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 13:24:31 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/24 13:43:38 by yongjule         ###   ########.fr       */
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
