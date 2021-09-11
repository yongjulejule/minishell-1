/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:01 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/11 17:26:07 by yongjule         ###   ########.fr       */
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
		while (is_charset(cmdset[start], "\t\n\v\f\r "))
			start++;
		if (is_charset(cmdset[start], "'"))
			len = split_once(&cmdset[start], "'") + start + 1;
		else if (is_charset(cmdset[start], "\""))
			len = split_once(&cmdset[start], "\"") + start + 1;
		else
			len = split_once(&cmdset[start], "\t\n\v\f\r ") + start;
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
		while (is_charset(cmdset[start], "\t\n\v\f\r "))
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
	/* NOTE : can occur leak here */
	cmd->params = (char **)ft_calloc(sizeof(char *), size + 1);
	parse_param(cmdset, cmd);
}

void	get_params(t_args *args)
{
	int	idx;

	idx = 0;
	while (args->cmd[idx].params)
	{
		get_each_params(args->cmd[idx].params[0], &args->cmd[idx]);
		idx++;
	}
}
