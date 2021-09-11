/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_rdr_info.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:23:05 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/11 14:04:20 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	get_rdr_from_append_info(t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strrnstr(cmd->params[0], "<<", ft_strlen(cmd->params[0]));
	if (!tmp)
		return ;
	cmd->is_heredoc = 1;
	cmd->rdr_from = 1;
	tmp = ft_strtrim(&tmp[2], " \r\v\t\f\n");
	if (tmp[0] == '\'')
		cmd->limiter = ft_substr(tmp, 1, split_once(&tmp[1], "'"));
	else if (tmp[0] == '"')
		cmd->limiter = ft_substr(tmp, 1, split_once(&tmp[1], "\""));
	else
		cmd->limiter = ft_substr(tmp, 0, split_once(tmp, " \n\r\v\f\t"));
	if (!cmd->file[0])
		free(cmd->file[0]);
	cmd->file[0] = ft_strdup(".tmp.here_doc");
	free(tmp);
	tmp = NULL;
}

static void	get_rdr_from_info(t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strrnstr(cmd->params[0], "<", ft_strlen(cmd->params[0]));
	if (!tmp)
		return ;
	cmd->is_heredoc = 0;
	cmd->rdr_from = 1;
	tmp = ft_strtrim(&tmp[1], " \r\v\t\f\n");
	if (tmp[1] == '\'')
		cmd->file[0] = ft_substr(tmp, 1, split_once(&tmp[1], "'"));
	else if (tmp[1] == '"')
		cmd->file[0] = ft_substr(tmp, 1, split_once(&tmp[1], "\""));
	else
		cmd->file[0] = ft_substr(tmp, 0, split_once(&tmp[0], " \n\r\v\f\t"));
	free(tmp);
	tmp = NULL;
}

static void	get_rdr_to_append_info(t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strrnstr(cmd->params[0], ">>", ft_strlen(cmd->params[0]));
	if (!tmp)
		return ;
	cmd->is_append = 1;
	cmd->rdr_to = 1;
	tmp = ft_strtrim(&tmp[2], " \r\v\t\f\n");
	if (!cmd->file[1])
		free(cmd->file[1]);
	if (tmp[0] == '\'')
		cmd->file[1] = ft_substr(tmp, 1, split_once(&tmp[1], "'"));
	else if (tmp[0] == '"')
		cmd->file[1] = ft_substr(tmp, 1, split_once(&tmp[1], "\""));
	else
		cmd->file[1] = ft_substr(tmp, 0, split_once(tmp, " \n\r\v\f\t"));
	free(tmp);
	tmp = NULL;
}

static void	get_rdr_to_info(t_cmd *cmd)
{
	char	*tmp;

	tmp = ft_strrnstr(cmd->params[0], ">", ft_strlen(cmd->params[0]));
	if (!tmp)
		return ;
	cmd->is_append = 0;
	cmd->rdr_to = 1;
	tmp = ft_strtrim(&tmp[1], " \r\v\t\f\n");
	if (tmp[1] == '\'')
		cmd->file[1] = ft_substr(tmp, 1, split_once(&tmp[1], "'"));
	else if (tmp[1] == '"')
		cmd->file[1] = ft_substr(tmp, 1, split_once(&tmp[1], "\""));
	else
		cmd->file[1] = ft_substr(tmp, 0, split_once(&tmp[0], " \n\r\v\f\t"));
	free(tmp);
	tmp = NULL;
}

void	get_rdr_info(t_cmd *cmd)
{
	get_rdr_from_info(cmd);
	get_rdr_from_append_info(cmd);
	get_rdr_to_info(cmd);
	get_rdr_to_append_info(cmd);
}
