/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:30:42 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/18 12:40:43 by yongjule         ###   ########.fr       */
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

static void	init_structure(char **cmds, t_args *args)
{
	int		cnt;
	int		cur;
	t_rdr	*rdr;

	cur = 0;
	cnt = 0;
	args->cmd = (t_cmd *)ft_calloc(args->cnt + 1, sizeof(t_cmd));
	while (cnt < args->cnt)
	{
		if (!ft_strcmp(cmds[cur], "|"))
			cur++;
		args->cmd[cnt].params = (char **)ft_calloc(args->cnt + 1, sizeof(char *));
		args->cmd[cnt].params[0] = cmds[cur];
		cnt++;
		cur++;
	}
}

void	build_structure(char **cmds, char **envp, t_args *args)
{
	int			idx;
	char		*tmp;

	init_structure(cmds, args);
	idx = 0;
	tmp = getenv("PATH");
	if (!tmp)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	args->env_path = ft_split(tmp, ':');
	args->envp = envp;
	get_params(args);
	make_cmds(args);
}
