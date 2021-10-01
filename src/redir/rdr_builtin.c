/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rdr_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 11:35:47 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/01 13:54:00 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "redir.h"

static int	rdr_lst_size(t_rdr *rdr)
{
	int	size;

	size = 0;
	while (rdr)
	{
		size++;
		rdr = rdr->next;
	}
	return (size);
}

static void	dup_fd_to_backup(int **fd)
{
	struct stat	status;
	int			idx;

	idx = 0;
	while (fd[idx])
	{
		if (fstat(fd[idx][0], &status) != -1)
		{
			if (dup2(fd[idx][0], fd[idx][1]) == -1)
				is_error(NULL, NULL, "redirection error: cannot duplicate \
						fd: Too many open files", EXIT_FAILURE);
		}
		else
			fd[idx][1] = -1;
		idx++;
	}
}

static void	get_available_fd(int **fd)
{
	int			idx;
	int			avail_fd;
	struct stat	status;

	idx = 0;
	avail_fd = 254;
	while (fd[idx] && avail_fd)
	{
		if (fstat(avail_fd, &status) == -1)
		{
			if (errno == EBADF)
			{
				fd[idx][1] = avail_fd;
				idx++;
			}
		}
		avail_fd--;
	}
	if (!avail_fd)
		is_error(NULL, NULL, "redirection error: cannot duplicate \
				fd: Too many open files", EXIT_FAILURE);
}

int	**backup_fd(t_rdr *rdr)
{
	int	**fd;
	int	size;
	int	idx;

	size = rdr_lst_size(rdr);
	if (!size)
		return (NULL);
	fd = (int **)ft_calloc(size + 1, sizeof(int *));
	idx = 0;
	while (idx < size)
	{
		fd[idx] = (int *)ft_calloc(2, sizeof(int));
		fd[idx][0] = rdr->fd[0];
		rdr = rdr->next;
		idx++;
	}
	get_available_fd(fd);
	dup_fd_to_backup(fd);
	return (fd);
}

void	retrive_fd(int **fd)
{
	int	idx;

	idx = 0;
	while (fd[idx])
	{
		if (fd[idx][1] == -1)
			close(fd[idx][0]);
		else
		{
			if (dup2(fd[idx][1], fd[idx][0]) == -1)
				is_error(NULL, NULL, strerror(errno), EXIT_FAILURE);
			close(fd[idx][1]);
		}
		idx++;
	}
}
