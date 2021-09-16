/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rdr_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:23:05 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/16 09:23:33 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static int	get_rdr_from_append_info(t_cmd *cmd, const char *line)
{
	char	*tmp;

	tmp = ft_strnstr(cmd->params[0], "<<", ft_strlen(cmd->params[0]));
	if (!tmp)
		return (0);
	cmd->is_heredoc = 1;
	cmd->rdr_from = 1;
	tmp = ft_strtrim(&tmp[2], " \t\n");
	if (tmp[0] == '\'')
		cmd->limiter = ft_substr(tmp, 1, split_once(&tmp[1], "'"));
	else if (tmp[0] == '"')
		cmd->limiter = ft_substr(tmp, 1, split_once(&tmp[1], "\""));
	else
		cmd->limiter = ft_substr(tmp, 0, split_once(tmp, " \n\f"));
	if (!cmd->file[0])
		free(cmd->file[0]);
	cmd->file[0] = ft_strdup(".tmp.here_doc");
	free(tmp);
	tmp = NULL;
	return (1);
}

static int	get_rdr_from_info(t_cmd *cmd, const char *line)
{
	char	*tmp;

	tmp = ft_strnstr(cmd->params[0], "<", ft_strlen(cmd->params[0]));
	if (!tmp)
		return (0);
	cmd->is_heredoc = 0;
	cmd->rdr_from = 1;
	tmp = ft_strtrim(&tmp[1], " \t\n");
	if (tmp[1] == '\'')
		cmd->file[0] = ft_substr(tmp, 1, split_once(&tmp[1], "'"));
	else if (tmp[1] == '"')
		cmd->file[0] = ft_substr(tmp, 1, split_once(&tmp[1], "\""));
	else
		cmd->file[0] = ft_substr(tmp, 0, split_once(&tmp[0], " \n\f"));
	free(tmp);
	tmp = NULL;
	return (1);
}

static int	get_rdr_to_append_info(t_cmd *cmd, const char *line)
{
	char	*tmp;

	tmp = ft_strnstr(cmd->params[0], ">>", ft_strlen(cmd->params[0]) - 1);
	if (!tmp)
		return (0);
	cmd->is_append = 1;
	cmd->rdr_to = 1;
	tmp = ft_strtrim(&tmp[2], " \t\n");
	if (!cmd->file[1])
		free(cmd->file[1]);
	if (tmp[0] == '\'')
		cmd->file[1] = ft_substr(tmp, 1, split_once(&tmp[1], "'"));
	else if (tmp[0] == '"')
		cmd->file[1] = ft_substr(tmp, 1, split_once(&tmp[1], "\""));
	else
		cmd->file[1] = ft_substr(tmp, 0, split_once(tmp, " \n\f"));
	free(tmp);
	tmp = NULL;
	return (1);
}

static int	get_rdr_to_info(t_cmd *cmd, const char *line)
{
	char	*tmp;

	tmp = ft_strnstr(cmd->params[0], ">", ft_strlen(cmd->params[0]));
	if (!tmp)
		return (0);
	cmd->is_append = 0;
	cmd->rdr_to = 1;
	tmp = ft_strtrim(&tmp[1], " \t\n");
	if (tmp[1] == '\'')
		cmd->file[1] = ft_substr(tmp, 1, split_once(&tmp[1], "'"));
	else if (tmp[1] == '"')
		cmd->file[1] = ft_substr(tmp, 1, split_once(&tmp[1], "\""));
	else
		cmd->file[1] = ft_substr(tmp, 0, split_once(&tmp[0], " \n\f"));
	free(tmp);
	tmp = NULL;
	return (1);
}

void	get_rdr_info(t_cmd *cmd)
{
	char	*line;
	char	*rdr_to;
	char	*rdr_from;

	line = cmd->params[0];
	while (1)
	{
		if (ft_strchr(line, '>'))
		{
			line = ft_strchr(line, '>');
			if (line[1] == '>')
				get_rdr_from_append_info(cmd, line);
			else
				get_rdr_from_info(cmd, line);
		}
		else if (ft_strchr(line '<'))
		{
			line = ft_strchr(line, '<');
			if (line[1] == '<')
				get_rdr_to_append_info(cmd, line);
			else
				get_rdr_to_info(cmd, line);   
		}
		else
			break;
	}   
}
