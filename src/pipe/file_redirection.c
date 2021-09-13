/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:29 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/11 18:24:26 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

void	destroy_pipe(int *pipe_fd)
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}

void	connect_pipe_fd(int *pipe_fd, int pipe_status)
{
	if (dup2(pipe_fd[pipe_status], pipe_status) == -1)
		is_error(NULL, "pipe: ", strerror(errno), EXIT_FAILURE);
	destroy_pipe(pipe_fd);
}

static void	make_tmp_heredoc(char *file, t_cmd *cmd)
{
	int		fd;
	int		size;
	char	*line;

	size = ft_strlen(cmd->limiter);
	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		is_error(NULL, "pipe: ", strerror(errno), EXIT_FAILURE);
	while (1)
	{
		ft_putstr_fd(">", 1);
		get_next_line(0, &line);
		if (!ft_memcmp(cmd->limiter, line, size))
		{
			free(line);
			line = NULL;
			close(fd);
			return ;
		}
		ft_putendl_fd(line, fd);
		free(line);
		line = NULL;
	}
}

void	rdr_file_to_stdin(char *file, t_cmd *cmd)
{
	int	fd;

	if (cmd->is_heredoc == 1)
		make_tmp_heredoc(file, cmd);
	fd = open(file, O_RDONLY);
	if (fd < 0)
		is_error(strerror(errno), ": ", file, EXIT_FAILURE);
	if (dup2(fd, STDIN_FILENO) == -1)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	close(fd);
	if (cmd->is_heredoc == 1)
		unlink(file);
	return ;
}

void	rdr_stdout_to_file(char *file, t_cmd *cmd)
{
	int	fd;

	if (cmd->is_heredoc != 1)
		fd = open(file, O_RDWR | O_TRUNC | O_CREAT, 0644);
	else
		fd = open(file, O_RDWR | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
		is_error(strerror(errno), ": ", file, EXIT_FAILURE);
	if (dup2(fd, STDOUT_FILENO) == -1)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	close(fd);
	return ;
}
