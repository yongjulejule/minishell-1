/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@42student.42seoul.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:29 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/20 17:08:08 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static void	make_tmp_heredoc(t_rdr *rdr)
{
	int		fd;
	char	*line;

	fd = open(rdr->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd < 0)
		is_error(strerror(errno), ": ", rdr->file, EXIT_FAILURE);
	/* NOTE :  if redirection is <<a <<b <<c, work not properly */
	while (1)
	{
		ft_putstr_fd(">", STDERR_FILENO);
		get_next_line(STDIN_FILENO, &line);
		if (!ft_strcmp(rdr->limiter, line))
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

static void	rdr_read(t_rdr *rdr)
{
	int		fd;

	if (rdr->fd[0] > 255 || rdr->fd[0] < 0)
		is_error(ft_itoa(rdr->fd[0]), NULL,
			": bad file descriptor", EXIT_FAILURE);
	if (rdr->info == rd_heredoc)
		make_tmp_heredoc(rdr);
	fd = open(rdr->file, O_RDONLY);
	if (fd < 0)
		is_error(strerror(errno), ": ", rdr->file, EXIT_FAILURE);
	if (dup2(fd, rdr->fd[0]) == -1)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	close(fd);
	if (rdr->info == rd_heredoc)
		unlink(rdr->file);
}

static void	rdr_write(t_rdr *rdr)
{
	int	fd;

	if (rdr->fd[0] > 255 || rdr->fd[0] < 0)
		is_error(ft_itoa(rdr->fd[0]), NULL,
			": bad file descriptor", EXIT_FAILURE);
	if (rdr->info == wr_to_file)
		fd = open(rdr->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (rdr->info == wr_append)
		fd = open(rdr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		if (dup2(STDERR_FILENO, rdr->fd[0]) == -1)
			is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
		fd = STDOUT_FILENO;
	}
	if (fd < 0)
		is_error(strerror(errno), ": ", rdr->file, EXIT_FAILURE);
	if (dup2(fd, rdr->fd[0]) == -1)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	close(fd);
}

static void	rdr_rdwr(t_rdr *rdr)
{
	int	fd;

	if (rdr->fd[0] > 255 || rdr->fd[0] < 0)
		is_error(ft_itoa(rdr->fd[0]), NULL,
			": bad file descriptor", EXIT_FAILURE);
	fd = open(rdr->file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		is_error(strerror(errno), ": ", rdr->file, EXIT_FAILURE);
	if (dup2(fd, rdr->fd[0]) == -1)
		is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
	if (fd != rdr->fd[0])
		close(fd);
}

void	redirect_stream(t_cmd *cmd)
{
	t_rdr	*rdr;

	rdr = cmd->rdr;
	while (rdr)
	{
		fprintf(stderr, "rdrinfo %d\n", rdr->info);
	fprintf(stderr, "file : %s, rdr->fd[0] = %d, rdr->fd[1] = %d\n", rdr->file, rdr->fd[0], rdr->fd[1]);
		if (rdr->info < 2)
			rdr_read(rdr);
		else if (rdr->info < 5)
			rdr_write(rdr);
		else if (rdr->info == close_fd)
			close(rdr->fd[0]);
		else if (rdr->info == rdwr)
			rdr_rdwr(rdr);
		else if (rdr->info == dup_fd)
		{
			if (rdr->fd[1] == -1)
				is_error(rdr->file, ": ", "ambiguous redirection", EXIT_FAILURE);
			if (dup2(rdr->fd[1], rdr->fd[0]) == -1)
				is_error(ft_itoa(rdr->fd[1]), NULL,
					": bad file descriptor", EXIT_FAILURE);
		}
		rdr = rdr->next;
	}
//	while(1);
}
