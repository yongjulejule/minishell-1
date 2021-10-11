/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:23:05 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/11 19:42:37 by yongjule         ###   ########.fr       */
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
	file = ft_substr_wo_chr(tmp, 0,
			get_wspace_len(&tmp[0], " \n\t", '\\', 0), '\\');
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
	fd[1] = -1;
	file = get_filename(&line[2]);
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(wr_to_file, file, NULL, fd));
	fd[0] = STDERR_FILENO;
	file = get_filename(&line[2]);
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(wr_to_file, file, NULL, fd));
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
