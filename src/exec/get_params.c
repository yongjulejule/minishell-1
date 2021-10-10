/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:01 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/10 14:21:44 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	count_params(char *cmdset)
{
	int	size;
	int	start;
	int	len;
	int	origin_size;

	start = 0;
	size = 0;
	origin_size = ft_strlen(cmdset);
	while (start < origin_size)
	{
		while (is_charset(cmdset[start], "\t\n "))
			start++;
		if (!cmdset[start])
			break ;
		size++;
		len = get_wspace_idx(&cmdset[start], "\t\n ", '\\') + start;
		start = len + 1;
	}
	return (size);
}

static void	sub_env_rm_qm_params(char **cmdset, t_args *args)
{
	if (ft_strchr(*cmdset, '$'))
	{
		sub_env(cmdset, args->envp);
		if (ft_strlen(*cmdset) == 1 && **cmdset == ' ')
			args->e_flag = 1;
	}
	if (ft_strchrset(*cmdset, "\"'"))
		rm_unnecessary_qm(cmdset);
}

static void	get_each_params(char **cmdset, t_args *args, int idx)
{
	int	start;
	int	len;
	int	size;
	int	p_idx;

	sub_env_rm_qm_params(&cmdset[idx], args);
	size = count_params(cmdset[idx]);
	args->cmd[idx].params = (char **)ft_calloc(size + 1, sizeof(char *));
	start = 0;
	p_idx = 0;
	while (p_idx < size)
	{
		while (is_charset(cmdset[idx][start], "\t\n "))
			start++;
		len = make_string(&cmdset[idx][start], &args->cmd[idx], p_idx, 1);
		start = len + start + 1;
		p_idx++;
	}
}

static void	sub_env_rm_qm_rdr(t_cmds *cmdlst, char **envp)
{
	if (ft_strchr(cmdlst->cmd, '$'))
		sub_env(&cmdlst->cmd, envp);
	if (ft_strchrset(cmdlst->cmd, "\"'"))
		rm_unnecessary_qm(&cmdlst->cmd);
}

void	get_params(t_args *args, char **cmds, t_cmds *cmdlst)
{
	int	idx;
	int	cur;

	cur = 0;
	idx = -1;
	while (cmds[++idx])
		get_each_params(cmds, args, idx);
	while (cmdlst && cmdlst->cmd[0] != ';')
	{
		if (cmdlst->cmd[0] != '|')
		{
			if (is_rdr(cmdlst->cmd))
			{
				sub_env_rm_qm_rdr(cmdlst, args->envp);
				get_rdr_info(cmdlst->cmd, &args->cmd[cur]);
			}
		}
		else
			cur++;
		cmdlst = cmdlst->next;
	}
}
