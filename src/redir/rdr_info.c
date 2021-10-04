/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:23:05 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/04 14:41:08 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

char	*get_filename(const char *line)
{
	char	*file;
	char	*tmp;

	if (!line || !*line)
		return (ft_strdup(""));
	tmp = ft_strtrim(line, " \n\t");
	if (!ft_strcmp(tmp, "''") || !ft_strcmp(tmp, "\"\""))
		file = ft_strdup("");
	else if (tmp[0] == '\'')
		file = ft_substr_wo_chr(tmp, 1,
				get_quote_len(&tmp[1], "'", '\0'), '\0');
	else if (tmp[0] == '"')
		file = ft_substr_wo_chr(tmp, 1,
				get_quote_len(&tmp[1], "\"", '\\'), '\\');
	else
		file = ft_substr_wo_chr(tmp, 0,
				get_wspace_len(&tmp[0], " \n\f", '\\'), '\\');
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

	fd[0] = STDOUT_FILENO;
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
