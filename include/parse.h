/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 17:11:55 by ghan              #+#    #+#             */
/*   Updated: 2021/09/29 17:55:10 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

/* Include Libraries */

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <term.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft.h"

/*User Defines*/

# define UNEXP_EOF_FLAG -4242
# define INT_PRPT_SIGINT -42
# define SYNTAX_ERR 258
# define GEN_ERR 1

typedef struct	s_cmds
{
	char			*cmd;
	struct s_cmds	*next;
}	t_cmds;

typedef struct s_cursor
{
	struct s_cmds	*elem;
}	t_cursor;


/* FUNCTIONS */

/* from_main */
void	free_cmds_lst(t_cmds **cmds_hd);
void	main_sig_handler(int signal);
char    *ft_get_envp(char **ft_envp, char *var);

/* internal prompt */
int		read_internal_prompt(char **one_ln, char *ln_read, int read_cnt);

/* utils_main */

char	*strchr_skip_bslash(const char *s, int c);
void	is_qmbt(char *one_ln, char **qmbt);
int		end_by_pipe(char *one_ln);
int		end_by_esc(char **one_ln);

/* split */

void	split_by_symbols(t_cmds *cmds_hd, char *s);
void	skip_qmbt(char *str, int *i, char *charset);
void	get_end_idx(char *s, int *i, char *charset, int flag);
int		rdr_after_fd(char *s, int *i);
int		check_front_whitespace(char *str, int len);
void	rm_unnecessary_qm(t_cmds *cmds_hd);

/* sub_env & syntax check */

void	sub_env(char **one_ln, char **ft_envp);
int		check_smcol_pipe_syntax(t_cmds *elem);
int		check_rdr_syntax(t_cmds *elem);
int		is_strset(char *str, char **strset);
int		is_strset_end(char *str, char **strset);
void	init_symbols(char **symbols);

/* split rdr */

int		get_rdr_end_idx(char *s, int *i);
int		check_valid_rdr_symbols(char *s, int i);

/* parse lst */

int		ps_lst_size(t_cmds *cmd);
t_cmds	*ps_lst_init(char *cmd);
t_cmds	*ps_lstlast(t_cmds *elem);
void	ps_lst_addback(t_cmds *hd, t_cmds *new);

#endif
