/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_env_alloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 16:30:15 by ghan              #+#    #+#             */
/*   Updated: 2021/10/09 16:30:34 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	strcpy_bslash_qm(char **env, char *to_fr, size_t len)
{
	size_t	i;
	int		k;

	k = 0;
	i = 0;
	while (i < len)
	{
		if (is_charset(to_fr[i], "\"'\\$"))
		{
			*(*env + k++) = '\\';
			*(*env + k++) = to_fr[i++];
		}
		else if (to_fr[i])
			*(*env + k++) = to_fr[i++];
	}
}

void	env_parse_quote(char **env)
{
	int		i;
	size_t	cnt;
	char	*to_fr;

	cnt = 0;
	i = 0;
	while (*(*env + i))
	{
		if (is_charset(*(*env + i), "\\\"'$"))
			cnt++;
		i++;
	}
	to_fr = *env;
	*env = (char *)ft_calloc(ft_strlen(*env) + cnt + 1, sizeof(char));
	strcpy_bslash_qm(env, to_fr, ft_strlen(to_fr));
	free(to_fr);
}
