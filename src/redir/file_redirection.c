/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_redirection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:29 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/03 13:12:04 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static int	make_tmp_heredoc(t_rdr *rdr)
{
	int		fd[2];
	char	*line;

	sigint_n_sigquit_handler(signal_heredoc);
	if (pipe(fd) == -1)
		return (rdr_err(NULL, "heredoc :", strerror(errno), EXIT_FAILURE));
	kill(0, SIGUSR1);
	while (1)
	{
		line = readline("> ");
		rl_instream->_file = BACKUP_FD;
		if (!line || !ft_strcmp(rdr->limiter, line))
		{
			rdr->fd[1] = fd[PIPE_RD];
			free(line);
			line = NULL;
			close(fd[PIPE_WR]);
			return (EXIT_SUCCESS);
		}
		ft_putendl_fd(line, fd[PIPE_WR]);
		free(line);
		line = NULL;
	}
}

static int	rdr_read(t_rdr *rdr)
{
	int		fd;

	if (rdr->fd[0] > 254 || rdr->fd[0] < 0)
		return (rdr_err(ft_itoa(rdr->fd[0]), NULL,
				": bad file descriptor", EXIT_FAILURE));
	if (rdr->info == rd_heredoc)
	{
		make_tmp_heredoc(rdr);
		fd = rdr->fd[1];
	}
	else
		fd = open(rdr->file, O_RDONLY);
	if (fd < 0)
		return (rdr_err(strerror(errno), ": ", rdr->file, EXIT_FAILURE));
	if (dup2(fd, rdr->fd[0]) == -1)
		return (rdr_err(NULL, NULL, strerror(errno), EXIT_FAILURE));
	close(fd);
	return (EXIT_SUCCESS);
}

static int	rdr_write(t_rdr *rdr)
{
	int	fd;

	if (rdr->fd[0] > 254 || rdr->fd[0] < 0)
		return (rdr_err(ft_itoa(rdr->fd[0]), NULL,
				": bad file descriptor", EXIT_FAILURE));
	if (rdr->info == wr_to_file)
		fd = open(rdr->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	else if (rdr->info == wr_append)
		fd = open(rdr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
	{
		fd = open(rdr->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (fd < 0)
			return (rdr_err(strerror(errno), ": ", rdr->file, EXIT_FAILURE));
		if (dup2(fd, rdr->fd[0]) == -1)
			return (rdr_err(NULL, NULL, strerror(errno), EXIT_FAILURE));
		if (dup2(fd, rdr->fd[1]) == -1)
			return (rdr_err(NULL, NULL, strerror(errno), EXIT_FAILURE));
	}
	if (fd < 0)
		return (rdr_err(strerror(errno), ": ", rdr->file, EXIT_FAILURE));
	if (dup2(fd, rdr->fd[0]) == -1)
		return (rdr_err(NULL, NULL, strerror(errno), EXIT_FAILURE));
	close(fd);
	return (EXIT_SUCCESS);
}

static int	rdr_rdwr(t_rdr *rdr)
{
	int	fd;

	if (rdr->fd[0] > 254 || rdr->fd[0] < 0)
		return (rdr_err(ft_itoa(rdr->fd[0]), NULL,
				": bad file descriptor", EXIT_FAILURE));
	fd = open(rdr->file, O_RDWR | O_CREAT, 0644);
	if (fd < 0)
		return (rdr_err(strerror(errno), ": ", rdr->file, EXIT_FAILURE));
	if (dup2(fd, rdr->fd[0]) == -1)
		return (rdr_err(NULL, NULL, strerror(errno), EXIT_FAILURE));
	if (fd != rdr->fd[0])
		close(fd);
	return (EXIT_SUCCESS);
}

int	redirect_stream(t_cmd *cmd)
{
	int	flag;

	flag = EXIT_SUCCESS;
	while (!flag && cmd->rdr)
	{
		if (cmd->rdr->info < 2)
			flag = rdr_read(cmd->rdr);
		else if (cmd->rdr->info < 5)
			flag = rdr_write(cmd->rdr);
		else if (cmd->rdr->info == close_fd)
			close(cmd->rdr->fd[0]);
		else if (cmd->rdr->info == rdwr)
			flag = rdr_rdwr(cmd->rdr);
		else if (cmd->rdr->info == dup_fd)
		{
			if (cmd->rdr->fd[1] == -1)
				flag = rdr_err(cmd->rdr->file, ": ", "ambiguous redirection",
						EXIT_FAILURE);
			if (dup2(cmd->rdr->fd[1], cmd->rdr->fd[0]) == -1)
				flag = rdr_err(ft_itoa(cmd->rdr->fd[1]), NULL,
						": bad file descriptor", EXIT_FAILURE);
		}
		cmd->rdr = cmd->rdr->next;
	}
	return (flag);
}
