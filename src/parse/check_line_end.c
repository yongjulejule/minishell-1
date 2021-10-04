/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_end.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 17:38:45 by ghan              #+#    #+#             */
/*   Updated: 2021/10/04 17:38:53 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

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
		if (trim[i] != '\0')
			i++;
	}
}

static void	check_pipe_front_rdr(char *s, int *val, char *p, int i)
{
	while (s[i])
	{
		p = ft_strchr(s + i, '|');
		if (p)
		{
			if (p - s >= 1 && is_charset(*(p - 1), "<>"))
			{
				*val = 0;
				break ;
			}
			else if (p - s >= 2 && ((is_charset(*(p - 2), "<>")
						&& is_charset(*(p - 1), "<>&"))
					|| (*(p - 2) == '&' && check_valid_rdr_symbols(p - 2, 0))))
			{
				*val = 0;
				break ;
			}
			else
				i = p - s + 1;
		}
		else
			break ;
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
	check_pipe_front_rdr(trim, &val, NULL, 0);
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

int	end_by_esc(char **one_ln)
{
	size_t	len;
	size_t	cnt;

	len = ft_strlen(*one_ln);
	cnt = 0;
	while (len >= cnt + 1 && *(*one_ln + len - cnt - 1) == '\\')
		cnt++;
	if (cnt % 2)
	{
		*(*one_ln + len - 1) = '\0';
		return (0);
	}
	return (1);
}
