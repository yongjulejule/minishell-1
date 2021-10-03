/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 13:45:32 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/03 13:56:01 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

void	destroy_pipe(int *pipe_fd)
{
	if (!pipe_fd)
		return ;
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	connect_pipe_fd(int *pipe_fd, int pipe_status)
{
	if (dup2(pipe_fd[pipe_status], pipe_status) == -1)
		is_error(NULL, "pipe: ", strerror(errno), EXIT_FAILURE);
	destroy_pipe(pipe_fd);
}

void	connect_pipestream(t_args *args, int idx)
{
	if (args->cnt > idx + 1)
		connect_pipe_fd(args->cmd[idx].pipe_fd, STDOUT_FILENO);
	if (idx > 0)
		connect_pipe_fd(args->cmd[idx - 1].pipe_fd, STDIN_FILENO);
}
