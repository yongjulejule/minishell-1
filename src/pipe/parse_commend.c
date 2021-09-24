/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_commend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 12:30:42 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/24 10:17:23 by yongjule         ###   ########.fr       */
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
//
//static char	**update_cmd_structure(char **cmds, t_args *args)
//{
//	int		cur;
//	char	**tmp;
//
//	cur = 0;
//	tmp = (char **)ft_calloc(args->cnt + 1, sizeof(char *));
//	while (cmds[cur] && cmds[cur][0] != ';')
//	{
//		if (cmds[cur][0] != '|')
//		{
//			if (!is_rdr(cmds[cur]))
//			else
//			cur++;
//		}
//		cur++;
//	}
//}

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
//	cmds = update_cmd_structure(cmds, args);
	get_params(args, cmds);
	make_cmds(args);
}
