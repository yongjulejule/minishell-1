/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 13:19:57 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/18 19:49:24 by jun              ###   ########.fr       */
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

typedef enum	e_info
{
	rd_from_file = 0,
	rd_from_fd,
	rd_heredoc,
	rd_close,
	wr_to_file,
	wr_to_fd,
	wr_append,
	wr_output_to_file,
	wr_close,
	rdwr,
	error,
}	t_info;

typedef struct s_rdr
{
	char			*file[2];
	t_info			info;
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

/*Check Validity*/

void	check_cmd_validity(t_args *args, t_cmd *cmd, char *param);

/*Redirecting*/

void	get_rdr_info(char *rdrs, t_cmd *cmd);
void	rdr_write(char *rdr, char *line, t_cmd *cmd);
void	rdr_read(char *rdr, char *line, t_cmd *cmd);
void	rdr_file_to_stdin(char *file, t_cmd *cmd);
void	rdr_stdout_to_file(char *file, t_cmd *cmd);
void	rdr_w_output_file(char *rdr, char *line, t_cmd *cmd);
void	rdr_error(t_cmd *cmd);
void	connect_pipe_fd(int *pipe_fd, int pipe_status);
void	destroy_pipe(int *pipe_fd);
t_rdr	*rdr_lst_newone(t_info info, char *limiter, char *file[2]);
void	rdr_lst_add_back(t_rdr **rdr, t_rdr *newnode);

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

/*Utils*/

int		split_once(char *str, char *charset);
int		make_string(char *cmdset, t_cmd *cmd, int p_idx);
void	free_strset(char **strset);

#endif
