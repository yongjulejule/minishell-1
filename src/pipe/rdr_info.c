/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:23:05 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/19 16:48:14 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

char	*get_filename(const char *line)
{
	char	*file;
	char	*tmp;

	if (*line == '\0')
		return (NULL);
	tmp = ft_strtrim(line, " \n\t");
	if (tmp[0] == '\'')
		file = ft_substr(tmp, 1, split_once(&tmp[1], "'"));
	else if (tmp[0] == '"')
		file = ft_substr(tmp, 1, split_once(&tmp[1], "\""));
	else
		file = ft_substr(tmp, 0, split_once(&tmp[0], " \n\f"));
	free(tmp);
	tmp = NULL;
	return (file);
}

void	rdr_error(t_cmd *cmd)
{
	int	fd[2];

	fd[0] = -1;
	fd[1] = -1;
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(error, NULL, NULL, fd));
}

void	rdr_w_output_file(char *line, t_cmd *cmd)
{
	int		fd[2];
	char	*file;

	fd[0] = STDIN_FILENO;
	fd[1] = STDERR_FILENO;
	file = get_filename(&line[2]);
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(wr_output_to_file,
			file, NULL, fd));
}

void	get_rdr_info(char *rdrs, t_cmd *cmd)
{
	char	*line;

	line = rdrs;
	line = ft_strchrset(line, "<>&");
	if (!line)
		return ;
	if (line[0] == '<')
		rdr_read_info(rdrs, line, cmd);
	else if (line[0] == '>')
		rdr_write_info(rdrs, line, cmd);
	else
	{
		if (line[1] == '>')
			rdr_w_output_file(line, cmd);
		else
			rdr_error(cmd);
	}
}
