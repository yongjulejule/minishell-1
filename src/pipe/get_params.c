/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:01 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/20 09:14:46 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static	int	count_params(char *cmdset)
{
	int	size;
	int	start;
	int	len;

	start = 0;
	size = 0;
	while (cmdset[start] != '\0')
	{
		size++;
		while (is_charset(cmdset[start], "\t\n "))
			start++;
		if (is_charset(cmdset[start], "'"))
			len = split_once(&cmdset[start], "'") + start + 1;
		else if (is_charset(cmdset[start], "\""))
			len = split_once(&cmdset[start], "\"") + start + 1;
		else
			len = split_once(&cmdset[start], "\t\n ") + start;
		start = len;
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
	cmd->params = (char **)ft_calloc(sizeof(char *), size + 1);
	parse_param(cmdset, cmd);
}

static int	is_rdr(char *str)
{
	if (!str)
		return (0);
	while (ft_isdigit(*str))
		str++;
	if (is_charset(*str, "<>&-"))
		return (1);
	else
		return (0);
}

void	get_params(t_args *args, char **cmds)
{
	int		idx;
	int		cur;

	cur = 0;
	idx = 0;
	while (cmds[idx] && cmds[idx][0] != ';')
	{
		if (cmds[idx][0] != '|')
		{
			if (!is_rdr(cmds[idx]))
				get_each_params(cmds[idx], &args->cmd[cur]);
			else
			{
				if (cur)
					cur--;
				get_rdr_info(cmds[idx], &args->cmd[cur]);
			}
			cur++;
		}
		idx++;
	}
}
