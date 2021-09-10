/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 18:06:28 by ghan              #+#    #+#             */
/*   Updated: 2021/09/10 18:06:29 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_line_end(char **one_ln, char *ln)
{
	char	*is_qmbt;
	size_t	i;
	int		cnt;

	*one_ln = ft_strjoin(*one_ln, ln);
	is_qmbt = ft_strchr(*one_ln, '`');
	if (!is_qmbt || (ft_strchr(*one_ln, '\'')
			&& is_qmbt > ft_strchr(*one_ln, '\'')))
		is_qmbt = ft_strchr(*one_ln, '\'');
	if (!is_qmbt || (ft_strchr(*one_ln, '"')
			&& is_qmbt > ft_strchr(*one_ln, '"')))
		is_qmbt = ft_strchr(*one_ln, '"');
	if (is_qmbt)
	{
		cnt = 0;
		i = -1;
		while (++i < ft_strlen(*one_ln))
		{
			if (*(*one_ln + i) == *is_qmbt)
				cnt++;
		}
		if (cnt % 2)
			return (0);
	}
	return (1);
}

void	complete_a_line(char **one_ln, char *ln_read)
{
	while (!check_line_end(one_ln, ln_read))
	{
		ln_read = readline("> ");
		if (!ln_read)
		{
			write(STDERR_FILENO,
				"🤣 esh: unexpected EOF while looking for matching `\"'", 56);
			free(*one_ln);
			*one_ln = ft_strdup("");
			break ;
		}
		add_history(rl_line_buffer);
	}
}

/* TODO - split a line of commands to each command */
char	**split_cmds(char **one_ln)
{
	// printf("%s\n", *one_ln);
	free(*one_ln);
	*one_ln = ft_strdup("");
	return (NULL);
}
