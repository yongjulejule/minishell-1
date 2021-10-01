/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:17:58 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/01 13:54:30 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	execute_builtin(t_args *args, char ***ft_envp)
{
	int	**rdr_fds;

	rdr_fds = backup_fd(args->cmd->rdr);
	if (rdr_fds)
		redirect_stream(&args->cmd[0]);
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
