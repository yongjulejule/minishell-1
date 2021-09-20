/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:19:57 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/20 19:12:53 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPE_H
# define PIPE_H

/*Include Libraries*/

# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"
# include "get_next_line.h"
# include <readline/readline.h>

/*User Defines*/

# define PIPE_RD 0
# define PIPE_WR 1
# define X_ERR 126
# define CMD_ERR 127
# define E_ACCESS 13
# define E_NOCMD 2
# define BACKUP_FD 255

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

/*Signal handler in pipe*/

void	signal_handle_wo_rl_prompt(int signal);
void	signal_exit(int signal);
void	sigint_n_sigquit_handler(void (*sigfunction));
void	reset_signal(int sig);

/*Check Validity*/

void	check_cmd_validity(t_args *args, t_cmd *cmd, char *param);

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

/*Preprocessing*/

void	build_structure(char **cmds, char **envp, t_args *args);
void	get_params(t_args *args, char **cmds);
void	breed_process(t_args *args);

/*
** Handle exit code
*/

int		wstatus(int status);
int		wifexited(int status);
int		wifsignaled(int status);
int		wexitstatus(int status);
int		wtermsig(int status);
void	wait_process(t_args *args);
int		get_exit_status(int status);

/*Utils*/

int		split_once(char *str, char *charset);
int		make_string(char *cmdset, t_cmd *cmd, int p_idx);
void	free_strset(char **strset);

#endif
