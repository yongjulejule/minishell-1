/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:17:58 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/04 00:52:05 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute_builtin(t_args *args, char ***ft_envp)
{
	int	**rdr_fds;

	rdr_fds = NULL;
	if (args->cnt == 1)
	{
		rdr_fds = backup_fd(args->cmd->rdr);
		if (rdr_fds)
			if (redirect_stream(&args->cmd[0]))
				return (retrive_fd(rdr_fds));
	}
	if (args->cmd->builtin == is_exprt || args->cmd->builtin == is_unset
		|| args->cmd->builtin == is_cd)
		args->cmd->exec_f.exec_env(args->cmd->params[0]
				, args->cmd->params, ft_envp);
	else
		args->cmd->exec_f.exec(args->cmd->params[0]
				, args->cmd->params, args->envp);
	if (rdr_fds)
		retrive_fd(rdr_fds);
}
