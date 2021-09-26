/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   connect_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 13:45:32 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/26 14:48:59 by yongjule         ###   ########.fr       */
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
