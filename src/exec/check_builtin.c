/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 09:00:21 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/30 14:21:43 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_builtin(t_cmd *cmd, char *cmds)
{
	int	is_builtin;

	is_builtin = 1;
	if (!ft_strcmp("echo", cmds))
		cmd->builtin = is_echo;
	else if (!ft_strcmp("cd", cmds))
		cmd->builtin = is_cd;
	else if (!ft_strcmp("pwd", cmds))
		cmd->builtin = is_pwd;
	else if (!ft_strcmp("export", cmds))
		cmd->builtin = is_exprt;
	else if (!ft_strcmp("unset", cmds))
		cmd->builtin = is_unset;
	else if (!ft_strcmp("env", cmds))
		cmd->builtin = is_env;
	else if (!ft_strcmp("exit", cmds))
		cmd->builtin = is_ext;
	else
	{
		cmd->builtin = notbuiltin;
		is_builtin = 0;
	}
	return (is_builtin);
}

void	update_builtin_func(t_cmd *cmd)
{
	if (cmd->builtin == is_echo)
		cmd->exec_f.exec = echo;
	else if (cmd->builtin == is_cd)
		cmd->exec_f.exec_env = cd;
	else if (cmd->builtin == is_pwd)
		cmd->exec_f.exec = pwd;
	else if (cmd->builtin == is_exprt)
		cmd->exec_f.exec_env = exprt;
	else if (cmd->builtin == is_unset)
		cmd->exec_f.exec_env = unset;
	else if (cmd->builtin == is_env)
		cmd->exec_f.exec = env;
	else if (cmd->builtin == is_ext)
		cmd->exec_f.exec = ext;
}
