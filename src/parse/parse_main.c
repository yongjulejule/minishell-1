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

#include "parse.h"

static int	cnt_skip_qmbt(char *one_ln, char *qmbt)
{
	size_t	i;
	int		cnt;

	cnt = 0;
	i = 0;
	while (qmbt && *(one_ln + i))
	{
		if (qmbt && *(one_ln + i) == '\\')
		{
			i++;
			if (*(one_ln + i) == *qmbt || *(one_ln + i) == '\\')
				i++;
		}
		if (*(one_ln + i) == *qmbt)
			cnt++;
		if (cnt && cnt % 2 == 0)
		{
			cnt = 0;
			i++;
			is_qmbt(one_ln + i, &qmbt);
		}
		if (*(one_ln + i) != '\0')
			i++;
	}
	return (cnt);
}

static int	check_line_end(char **one_ln, char *ln)
{
	char	*to_free;
	char	*qmbt;
	int		cnt;

	to_free = *one_ln;
	*one_ln = ft_strjoin(*one_ln, ln);
	free(to_free);
	is_qmbt(*one_ln, &qmbt);
	cnt = cnt_skip_qmbt(*one_ln, qmbt);
	if (cnt % 2 || !end_by_pipe(*one_ln) || !end_by_esc(*one_ln))
		return (0);
	return (1);
}

char	**parse_line_main(char *ln_read)
{
	char	**cmds;
	char	*one_ln;
	int		read_flag;

	read_flag = 0;
	one_ln = ft_strdup("");
	while (!check_line_end(&one_ln, ln_read))
	{
		ln_read = readline("> ");
		if (!ln_read)
		{
			write(STDERR_FILENO,
				"🤣 esh: unexpected EOF while looking for matching `\"'\n", 56);
			break ;
		}
		add_history(rl_line_buffer);
		read_flag = 1;
	}
	sub_env(&one_ln);
	cmds = split_by_pipe_sc(one_ln, ";|");
	free(one_ln);
	if (read_flag)
		free(ln_read);
	return (cmds);
}
