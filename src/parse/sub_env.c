/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:16:05 by ghan              #+#    #+#             */
/*   Updated: 2021/10/01 15:59:07 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern int	g_exit_code;

static void	env_or_exit_stat(char **env, char *ln, int end, char **ft_envp)
{
	char	*to_free;

	to_free = ft_strndup(ln, end);
	if (!ft_strcmp("?", to_free))
		*env = ft_itoa(g_exit_code);
	else
	{
		*env = ft_get_envp(ft_envp, to_free);
		if (*env)
			*env = ft_strdup(*env);
	}
	free(to_free);
}

static void	join_front_env_back(char **ln, char *front, char *back, char *env)
{
	char	*to_free;

	to_free = *ln;
	*ln = ft_strjoin(front, "\"");
	free(to_free);
	to_free = *ln;
	*ln = ft_strjoin(*ln, env);
	free(to_free);
	to_free = *ln;
	*ln = ft_strjoin(*ln, "\"");
	free(to_free);
	to_free = *ln;
	*ln = ft_strjoin(*ln, back);
	free(to_free);
}

static void	recompose_ln_env(char **ln, int start, int end, char **ft_envp)
{
	char	*front;
	char	*back;
	char	*env;

	env_or_exit_stat(&env, *ln + start + 1, end, ft_envp);
	if (!env)
		env = ft_strdup("");
	front = ft_strndup(*ln, start);
	back = ft_substr(*ln, start + end + 1,
			ft_strlen(*ln) - start - end - 1);
	join_front_env_back(ln, front, back, env);
	free(front);
	free(back);
	free(env);
}

static void	get_env_interval(char **ln, int i, char **ft_envp)
{
	int	k;

	k = 1;
	if (ft_isalpha(*(*ln + i + k)) || *(*ln + i + k) == '_')
	{
		while (*(*ln + i + k)
			&& (ft_isalnum(*(*ln + i + k)) || *(*ln + i + k) == '_'))
			k++;
	}
	else if (*(*ln + i + k) == '?')
		k++;
	recompose_ln_env(ln, i, k - 1, ft_envp);
}

void	sub_env(char **ln, char **ft_envp)
{
	int	d_qt_flag;
	int	i;

	d_qt_flag = 0;
	i = 0;
	while (*(*ln + i))
	{
		if (*(*ln + i) == '$')
			get_env_interval(ln, i++, ft_envp);
		else if (*(*ln + i) == '\\')
		{
			i++;
			if (is_charset(*(*ln + i), "\"'`$"))
				i++;
		}	
		else if (*(*ln + i) != '\0')
		{
			if (*(*ln + i) == '"')
				d_qt_flag++;
			else if (*(*ln + i) == '\'' && d_qt_flag % 2 == 0)
				skip_qmbt(*ln, &i, "\"'`");
			i++;
		}
	}
}
