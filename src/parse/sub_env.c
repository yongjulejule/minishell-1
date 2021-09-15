/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 15:16:05 by ghan              #+#    #+#             */
/*   Updated: 2021/09/14 15:16:06 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern int	g_exit_code;

static void	env_or_exit_stat(char **env, char **ln, int start, int end)
{
	char	*to_free;

	to_free = ft_strndup(*ln + start + 1, end);
	if (!ft_strcmp("?", to_free))
		*env = ft_itoa(g_exit_code);
	else
	{
		*env = getenv(to_free);
		if (*env)
			*env = ft_strdup(*env);
	}
	free(to_free);
}

static void	recompose_ln_with_env(char **ln, int start, int end)
{
	char	*to_free;
	char	*front;
	char	*back;
	char	*env;

	env_or_exit_stat(&env, ln, start, end);
	if (!env)
		return ;
	front = ft_strndup(*ln, start);
	back = ft_substr(*ln, start + end + 1,
			ft_strlen(*ln) - start - end - 1);
	to_free = *ln;
	*ln = ft_strjoin(front, env);
	free(to_free);
	to_free = *ln;
	*ln = ft_strjoin(*ln, back);
	free(to_free);
	free(front);
	free(back);
	free(env);
}

void	sub_env(char **ln)
{
	int	i;
	int	k;

	i = 0;
	while (*(*ln + i))
	{
		if (*(*ln + i) == '$')
		{
			k = 1;
			if (ft_isalpha(*(*ln + i + k)) || *(*ln + i + k) == '_')
			{
				while (*(*ln + i + k)
					&& (ft_isalnum(*(*ln + i + k)) || *(*ln + i + k) == '_'))
					k++;
			}
			else if (*(*ln + i + k) == '?')
				k++;
			recompose_ln_with_env(ln, i, k - 1);
		}
		else if (*(*ln + i) == '\\')
			i++;
		if (*(*ln + i) != '\0')
			i++;
	}
}
