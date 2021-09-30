/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:01 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/30 09:17:33 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static	int	count_params(char *cmdset)
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
		size++;
		while (is_charset(cmdset[start], "\t\n "))
			start++;
		if (is_charset(cmdset[start], "'"))
			len = split_once(&cmdset[start + 1], "'", '\\') + start + 1;
		else if (is_charset(cmdset[start], "\""))
			len = split_once(&cmdset[start + 1], "\"", '\\') + start + 1;
		else
			len = split_once(&cmdset[start], "\t\n ", '\\') + start;
		start = len + 1;
	}
	return (size);
}

static	void	parse_param(char *cmdset, t_cmd *cmd)
{
	int	start;
	int	len;
	int	size;
	int	p_idx;

	size = count_params(cmdset);
	start = 0;
	p_idx = 0;
	while (p_idx < size)
	{
		while (is_charset(cmdset[start], "\t\n "))
			start++;
		len = make_string(&cmdset[start], cmd, p_idx);
		start = len + start + 1;
		p_idx++;
	}
}

static	void	get_each_params(char *cmdset, t_cmd *cmd)
{
	int	size;

	size = count_params(cmdset);
	cmd->params = (char **)ft_calloc(size + 1, sizeof(char *));
	parse_param(cmdset, cmd);
}

int	is_rdr(char *str)
{
	if (!str)
		return (0);
	while (ft_isdigit(*str))
		str++;
	if (is_charset(*str, "<>&"))
		return (1);
	else
		return (0);
}

void	get_params(t_args *args, char **cmds, t_cmds *cmdlst)
{
	int		idx;
	int		cur;

	cur = 0;
	idx = 0;
	while (cmds[idx])
	{
		get_each_params(cmds[idx], &args->cmd[idx]);
		idx++;
	}
	while (cmdlst && cmdlst->cmd[0] != ';')
	{
		if (cmdlst->cmd[0] != '|')
		{
			if (is_rdr(cmdlst->cmd))
				get_rdr_info(cmdlst->cmd, &args->cmd[cur]);
		}
		else
			cur++;
		cmdlst = cmdlst->next;
	}
}
