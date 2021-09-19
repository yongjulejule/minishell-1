/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 18:12:10 by jun               #+#    #+#             */
/*   Updated: 2021/09/19 11:47:36 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	rdr_w_file(char *rdr, char *line, t_cmd *cmd)
{
	int		fd[2];
	char	*file;

	fd[1] = -1;
	if (line == rdr)
		fd[0] = 1;
	else
		fd[0] = ft_atoi_fd(rdr);
	file = get_filename(&line[1]);
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(wr_to_file, file, NULL, fd));
}

static void	rdr_w_append(char *rdr, char *line, t_cmd *cmd)
{
	int		fd[2];
	char	*file;

	fd[1] = -1;
	if (line == rdr)
		fd[0] = 1;
	else
		fd[0] = ft_atoi_fd(rdr);
	file = get_filename(&line[1]);
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(wr_append, file, NULL, fd));
}

static void	rdr_w_fd(char *rdr, char *line, t_cmd *cmd)
{
	int		fd[2];
	char	*file;
	t_info	info;

	info = wr_dup_fd;
	fd[1] = -1;
	if (line == rdr)
		fd[0] = 1;
	else
		fd[0] = ft_atoi_fd(rdr);
	file = &line[2];
	while (ft_isdigit(*file))
		file++;
	if (*file == '\0')
		fd[1] = ft_atoi_fd(&line[2]);
	else
	{
		file = get_filename(&line[2]);
		info = wr_to_file;
	}
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(info, file, NULL, fd));
}

static void	rdr_close(char *rdr, char *line, t_cmd *cmd)
{
	int	fd[2];

	fd[1] = -1;
	if (line == rdr)
		fd[0] = 1;
	else
		fd[0] = ft_atoi_fd(rdr);
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(close_fd, NULL, NULL, fd));
}

void	rdr_write(char *rdr, char *line, t_cmd *cmd)
{
	if (line[1] == '\0')
		rdr_w_file(rdr, line, cmd);
	else if (line[1] == '>')
		rdr_w_append(rdr, line, cmd);
	else if (line[1] == '&')
	{
		if (line[2] == '-')
			rdr_close(rdr, line, cmd);
		else if (line[2] == '\0' || line[2] == '&')
			rdr_error(cmd);
		else
			rdr_w_fd(rdr, line, cmd);
	}
	else
		rdr_w_file(rdr, line, cmd);
}
