/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:23:05 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/19 08:50:22 by yongjule         ###   ########.fr       */
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

/* NOTE : line is charactor set which is after rdr symbol*/

char	*get_filename(const char *line)
{
	char	*file;
	char	*tmp;

	if (*line == '\0')
		return (NULL);
	tmp = ft_strtrim(line, " \n\t");
	if (tmp[0] == '\'')
		file = ft_substr(tmp, 1, split_once(&tmp[1], "'"));
	else if (file[0] == '"')
		file = ft_substr(tmp, 1, split_once(&tmp[1], "\""));
	else
		file = ft_substr(tmp, 0, split_once(&tmp[0], " \n\f"));
	free(tmp);
	tmp = NULL;
	return (file);
}

void	rdr_error(t_cmd *cmd, char *err_msg)
{
	char *str[3];

	str[0] = NULL;
	str[1] = NULL;
	str[2] = err_msg;
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(error, NULL, str));
}

void	get_rdr_info(char *rdrs, t_cmd *cmd)
{
	char	*line;

	line = rdrs;
	line = ft_strchrset(line, "<>&");
	if (!line)
		break ;
	if (line[0] == '<') /* rdr_read */
		rdr_read(rdr, line, cmd);
	else if (line[0] == '>') /* rdr_write */
		rdr_write(rdr, line, cmd);
	else /*if (line[0] == '&')*/
	{
		if (line[1] == '>')
			rdr_w_output_file(rdr, line, cmd);
		else
			rdr_error(cmd);
	}
}
