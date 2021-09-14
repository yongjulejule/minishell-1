/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_main.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 12:32:30 by ghan              #+#    #+#             */
/*   Updated: 2021/09/14 12:32:31 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

char	*strchr_skip_bslash(const char *s, int c)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	while (*str != (unsigned char)c && (*str != '\0'))
	{
		if (*str == '\\')
			str++;
		if (*str != '\0')
			str++;
	}
	if (*str != (unsigned char)c)
		return (NULL);
	return ((char *)str);
}

void	is_qmbt(char *one_ln, char **qmbt)
{
	*qmbt = strchr_skip_bslash(one_ln, '`');
	if (!(*qmbt) || (strchr_skip_bslash(one_ln, '\'')
			&& *qmbt > strchr_skip_bslash(one_ln, '\'')))
		*qmbt = strchr_skip_bslash(one_ln, '\'');
	if (!(*qmbt) || (strchr_skip_bslash(one_ln, '"')
			&& *qmbt > strchr_skip_bslash(one_ln, '"')))
		*qmbt = strchr_skip_bslash(one_ln, '"');
}

static void	check_pipe_front(char *trim, int *val)
{
	int	i;

	i = 0;
	while (trim[i])
	{
		if (trim[i] == '|')
		{
			if (!(*val) || trim[i + 1] == '\0')
				break ;
			*val = 0;
		}
		else if (!is_charset(trim[i], " \t\n;"))
			(*val)++;
		if (trim[i] == '\\')
			i++;
		i++;
	}
}

int	end_by_pipe(char *one_ln)
{
	size_t	len;
	size_t	cnt;
	char	*trim;
	int		val;

	val = 0;
	trim = ft_strtrim(one_ln, " \t\n");
	check_pipe_front(trim, &val);
	len = ft_strlen(trim);
	cnt = 0;
	while (len >= cnt + 2 && trim[len - 1] == '|'
		&& trim[len - cnt - 2] == '\\')
		cnt++;
	if (val && trim[len - 1] == '|' && cnt % 2 == 0)
	{
		free(trim);
		return (0);
	}
	free(trim);
	return (1);
}

int	end_by_esc(char *one_ln)
{
	size_t	len;
	size_t	cnt;

	len = ft_strlen(one_ln);
	cnt = 0;
	while (len >= cnt + 1 && one_ln[len - cnt - 1] == '\\')
		cnt++;
	if (cnt % 2)
		return (0);
	return (1);
}
