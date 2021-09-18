/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_write.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@student.42seoul.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 18:12:10 by jun               #+#    #+#             */
/*   Updated: 2021/09/18 19:51:59 by jun              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	rdr_w_file(char *rdr, char *line, t_cmd *cmd)
{
}

static void	rdr_w_append(char *rdr, char *line, t_cmd *cmd)
{
}

static void	rdr_w_fd(char *rdr, char *line, t_cmd *cmd)
{
}

void	rdr_w_output_file(char *rdr, char *line, t_cmd *cmd)
{
}

void	rdr_write(char *rdr, char *line, t_cmd *cmd)
{
	if (line[1] == '\0')
		rdr_w_file(rdr, line, cmd);
	else if (line[1] == '>')
		rdr_w_append(rdr, line, cmd);
	else if (line[1] == '&')/* TODO : consider >&-*/
		rdr_w_fd(rdr, line, cmd);
	else
		rdr_w_file(rdr, line, cmd);
}
