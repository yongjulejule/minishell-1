/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:19:57 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/27 17:36:08 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REDIR_H
# define REDIR_H

/*Include Libraries*/

# include <sys/errno.h>
# include <fcntl.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "libft.h"
# include "builtin.h"
# include <readline/readline.h>

/*User Defines*/

# define PIPE_RD 0
# define PIPE_WR 1
# define X_ERR 126
# define CMD_ERR 127
# define E_ACCESS 13
# define E_NOCMD 2
# define BACKUP_FD 255

typedef struct	s_cmds
{
	char			*cmd;
	struct s_cmds	*next;
}	t_cmds;

typedef enum e_info
{
	rd_from_file = 0,
	rd_heredoc,
	wr_to_file,
	wr_append,
	wr_output_to_file,
	dup_fd,
	close_fd,
	rdwr,
	error,
}	t_info;

typedef enum e_builtin
{
	notbuiltin = 0,
	is_echo,
	is_cd,
	is_pwd,
	is_exprt,
	is_unset,
	is_env,
	is_ext,
}	t_builtin;

typedef struct s_rdr
{
	t_info			info;
	char			*file;
	int				fd[2];
	char			*limiter;
	struct s_rdr	*next;
}	t_rdr;

typedef struct s_cmd
{
	pid_t			pid;
	int				pipe_fd[2];
	t_builtin		builtin;
	int				(*exec)(const char*, char *const[], char *const[]);
	char			**params;
	t_rdr			*rdr;
}	t_cmd;

typedef struct s_args
{
	int				cnt;
	char			**env_path;
	char			**envp;
	t_cmd			*cmd;
}	t_args;

/*FUNCTIONS*/

/*Signal handler in redir*/

void	signal_heredoc(int sig);
void	sigint_n_sigquit_handler(void (*sigfunction));

/*Redirecting*/

void	get_rdr_info(char *rdrs, t_cmd *cmd);
void	rdr_write_info(char *rdr, char *line, t_cmd *cmd);
void	rdr_read_info(char *rdr, char *line, t_cmd *cmd);
void	rdr_w_output_file(char *line, t_cmd *cmd);
void	rdr_error(t_cmd *cmd);
void	connect_pipe_fd(int *pipe_fd, int pipe_status);
void	destroy_pipe(int *pipe_fd);
t_rdr	*rdr_lst_newone(t_info info, char *file, char *limiter, int *fd);
void	rdr_lst_add_back(t_rdr **rdr, t_rdr *newnode);
char	*get_filename(const char *line);
int		ft_atoi_fd(const char *str);
void	redirect_stream(t_cmd *cmd);
int		is_rdr(char *str);

/*Utils*/

int		split_once(char *str, char *charset);
char	*ft_substr_wo_chr(char *str, unsigned int start, size_t len, char c);
#endif
