/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 18:11:59 by jun               #+#    #+#             */
/*   Updated: 2021/09/18 21:04:21 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	rdr_r_file(char *rdr, char *line, t_cmd *cmd)
{
	int	fd_to;

	fd_to = ft_atoi(rdr);
}

static void	rdr_r_heredoc(char *rdr, char *line, t_cmd *cmd)
{
}

static void	rdr_r_fd(char *rdr, char *line, t_cmd *cmd)
{
}

static void	rdr_r_w(char *rdr, char *line, t_cmd *cmd)
{
}

void	rdr_read(char *rdr, char *line, t_cmd *cmd)
{
	if (line[1] == '<')
		rdr_r_heredoc(rdr, line, cmd);
	else if (line[1] == '&')/* TODO : consider <&-*/
		rdr_r_fd(rdr, line, cmd);
	else if (line[1] == '>')
		rdr_r_w(rdr, line, cmd);
	else
		rdr_r_file(rdr, line, cmd);
}
