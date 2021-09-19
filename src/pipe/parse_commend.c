/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:30:42 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/19 16:51:46 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	make_cmds(t_args *args)
{
	int	cmd_idx;

	cmd_idx = 0;
	while (args->cmd[cmd_idx].params)
	{
		check_cmd_validity(args, &args->cmd[cmd_idx],
			args->cmd[cmd_idx].params[0]);
		cmd_idx++;
	}
}

void	build_structure(char **cmds, char **envp, t_args *args)
{
	int			idx;
	char		*tmp;

	idx = 0;
	tmp = getenv("PATH");
	if (!tmp)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	args->env_path = ft_split(tmp, ':');
	args->envp = envp;
	get_params(args, cmds);
	make_cmds(args);
}
