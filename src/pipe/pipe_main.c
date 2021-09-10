/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@42student.42seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:22:10 by jun               #+#    #+#             */
/*   Updated: 2021/09/10 16:25:40 by jun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

int	pipe_main(int argc, char **argv, char **envp)
{
	t_args	*args;

	args = (t_args *)ft_calloc(1, sizeof(t_args));
	args->envp = envp;
	build_structure(argc, argv, envp, args);
	breed_process(args);
	return (EXIT_SUCCESS);
}
