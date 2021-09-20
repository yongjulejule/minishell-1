/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_read_info.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 18:11:59 by jun               #+#    #+#             */
/*   Updated: 2021/09/20 17:17:12 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	rdr_r_file(char *rdr, char *line, t_cmd *cmd)
{
	int		fd[2];
	char	*file;

	fd[1] = -1;
	if (line == rdr)
		fd[0] = 0;
	else
		fd[0] = ft_atoi_fd(rdr);
	file = get_filename(&line[1]);
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(rd_from_file, file, NULL, fd));
}

static void	rdr_r_heredoc(char *rdr, char *line, t_cmd *cmd)
{
	int			fd[2];
	static int	fileno = 10000;
	char		*tmp;
	char		*file;

	fd[1] = -1;
	if (line == rdr)
		fd[0] = 0;
	else
		fd[0] = ft_atoi_fd(rdr);
	tmp = ft_itoa(10000);
	file = ft_strjoin(".tmp.", tmp);
	free(tmp);
	tmp = get_filename(&line[2]);
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(rd_heredoc, file, tmp, fd));
	fileno++;
	if (fileno > 19999)
		fileno = 10000;
}

static void	rdr_r_dup_fd(char *rdr, char *line, t_cmd *cmd)
{
	int		fd[2];
	char	*file;
	t_info	info;

	fd[1] = -1;
	file = NULL;
	if (line == rdr)
		fd[0] = 0;
	else
		fd[0] = ft_atoi_fd(rdr);
	if (line[2] == '-')
		info = close_fd;
	else
	{
		if (ft_isdigit(line[2]))
			fd[1] = ft_atoi_fd(&line[2]);
		else
			file = get_filename(&line[2]);
		info = dup_fd;
	}
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(info, file, NULL, fd));
}

static void	rdr_r_w(char *rdr, char *line, t_cmd *cmd)
{
	int		fd[2];
	char	*file;

	fd[0] = -1;
	fd[1] = -1;
	if (line[2] == '&' || line[2] == '\0')
	{
		rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(error, NULL, NULL, fd));
		return ;
	}
	if (line == rdr)
		fd[0] = 0;
	else
		fd[0] = ft_atoi_fd(rdr);
	file = get_filename(&line[2]);
	rdr_lst_add_back(&cmd->rdr, rdr_lst_newone(rdwr, file, NULL, fd));
}

void	rdr_read_info(char *rdr, char *line, t_cmd *cmd)
{
	if (line[1] == '<')
		rdr_r_heredoc(rdr, line, cmd);
	else if (line[1] == '&')
		rdr_r_dup_fd(rdr, line, cmd);
	else if (line[1] == '>')
		rdr_r_w(rdr, line, cmd);
	else
		rdr_r_file(rdr, line, cmd);
}
