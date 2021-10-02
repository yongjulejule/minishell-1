/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 14:30:15 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/02 20:16:40 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*Include Libraries*/

# include <sys/errno.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <stdio.h>
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
# define FMT_ERR 2

typedef struct s_cmds
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

typedef union u_exec_f
{
	int		(*exec)(const char *, char *const [], char *const []);
	int		(*exec_env)(const char *, char *const [], char ***const);
}	t_exec_f_u;

typedef struct s_cmd
{
	pid_t			pid;
	int				pipe_fd[2];
	t_builtin		builtin;
	t_exec_f_u		exec_f;
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
void	signal_heredoc(int sig);
void	sigint_n_sigquit_handler(void (*sigfunction));
void	reset_signal(int sig);
void	multi_shell_erase_newline(int sig);
void	ignore_signal(int sig);
void	no_newline_for_sigquit(int sig);
char	*ft_get_envp(char **ft_envp, char *var);

/*Check Validity*/

void	check_cmd_validity(t_args *args, t_cmd *cmd, char *param);

/*Check Builtin*/

int		check_builtin(t_cmd *cmd, char *cmds);
void	update_builtin_func(t_cmd *cmd);

/*Redirecting*/

void	get_rdr_info(char *rdrs, t_cmd *cmd);
void	connect_pipe_fd(int *pipe_fd, int pipe_status);
void	destroy_pipe(int *pipe_fd);
void	redirect_stream(t_cmd *cmd);
int		is_rdr(char *str);

/*Preprocessing*/

void	build_structure(t_cmds *cmdlst, char **envp, t_args *args);
void	get_params(t_args *args, char **cmds, t_cmds *cmslst);
void	execute_subshell_main(t_args *args, int idx);
void	execute_builtin(t_args *args, char ***ft_envp);

/*Handle exit code*/

int		wstatus(int status);
int		wifexited(int status);
int		wifsignaled(int status);
int		wexitstatus(int status);
int		wtermsig(int status);
void	wait_process(t_args *args);
int		get_exit_status(int status);

/*Redirection in builtin*/

int		**backup_fd(t_rdr *rdr);
void	retrive_fd(int **fds);

/*Utils*/

int		get_quote_len(char *str, char *charset, char ign);
int		get_wspace_len(char *str, char *charset, char ign);
int		make_string(char *cmdset, t_cmd *cmd, int p_idx);
char	*ft_substr_wo_chr(char *str, unsigned int start, size_t len, char c);
void	free_arg_structure(t_args *args);
void	free_double_ptr(void ***ptr);
int		get_quote_idx(char *str, char *charset, char ign);
int		get_wspace_idx(char *str, char *charset, char ign);

/* Sub_env */

void	sub_env(char **params, char **ft_envp);
void	skip_qmbt(char *str, int *i, char *charset);

#endif
