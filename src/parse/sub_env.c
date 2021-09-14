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

static void	recompose_ln_with_env(char **one_ln, int start, int end)
{
	char	*front;
	char	*back;
	char	*env;
	char	*to_free;

	to_free = ft_strndup(*one_ln + start + 1, end);
	env = getenv(to_free);
	free(to_free);
	if (!env)
		return ;
	env = ft_strdup(env);
	front = ft_strndup(*one_ln, start);
	back = ft_substr(*one_ln, end + 1, ft_strlen(*one_ln) - end - 1);
	to_free = *one_ln;
	*one_ln = ft_strjoin(front, env);
	free(to_free);
	to_free = *one_ln;
	*one_ln = ft_strjoin(*one_ln, back);
	free(to_free);
	free(front);
	free(back);
	free(env);
}

void	sub_env(char **ln)
{
	size_t	len;
	size_t	i;
	int	k;

	len = ft_strlen(*ln);
	i = 0;
	while (i < len)
	{
		if (*(*ln + i) == '$')
		{
			k = 1;
			if (ft_isalpha(*(*ln + i + k))
				|| *(*ln + i + k) == '_')
			{
				while (*(*ln + i + k)
					&& (ft_isalnum(*(*ln + i + k)) || *(*ln + i + k) == '_'))
					k++;
			}
			recompose_ln_with_env(ln, i, k - 1);
			len = ft_strlen(*ln);
		}
		else if (*(*ln + i) == '\\')
			i++;
		if (*(*ln + i) != '\0')
			i++;
	}
}
