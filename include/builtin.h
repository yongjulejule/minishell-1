/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 10:31:34 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/06 11:44:39 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/* Include Libraries */

# include "libft.h"
# include <sys/errno.h>
# include <stdio.h>
# include <string.h>

/* User Define */

typedef struct s_exp_arg
{
	char				*arg;
	int					flag;
	struct s_exp_arg	*next;
}	t_exp_arg;

/* FUNCTIONS */

/* Error Handling */

int			is_error_no_exit(char *str1, char *str2, char *err_msg, int status);

/* Builtin Commands */

int			exprt(const char *path, char *const argv[], char ***const envp);
int			unset(const char *path, char *const argv[], char ***const envp);
int			cd(const char *path, char *const argv[], char ***const envp);
int			echo(const char *path, char *const argv[], char *const envp[]);
int			ext(const char *path, char *const argv[], char *const envp[]);
int			pwd(const char *path, char *const argv[], char *const envp[]);
int			env(const char *path, char *const argv[], char *const envp[]);

/* Utils */

char		**dup_envp(char *envp[], int set_len);
void		free_double_ptr(void ***ptr);
char		*strdup_skip_qm(char *s, size_t idx, size_t cnt_skip);
void		append_env_var(char ***envp, char *arg, int *n_idx);
t_exp_arg	*argv_to_lst(char **argv, int i);
void		exp_unset_invalid_arg_msg(char c, char *str);
char		*ft_get_envp(char **ft_envp, char *var);

/* Exp lst */

int			exp_lst_size(t_exp_arg *arg);
t_exp_arg	*exp_lst_init(char *arg);
t_exp_arg	*exp_lstlast(t_exp_arg *elem);
void		exp_lst_addback(t_exp_arg *hd, t_exp_arg *new);
void		free_argv_lst(t_exp_arg **av_lst);
void		exprt_no_arg(char **envp, int len);

#endif
