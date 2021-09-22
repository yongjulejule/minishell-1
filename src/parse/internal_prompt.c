/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:48:18 by ghan              #+#    #+#             */
/*   Updated: 2021/09/22 16:50:49 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern int	g_exit_code;

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
		else if (*(one_ln + i) != '\0')
			i++;
	}
	return (cnt);
}

static void	internal_prompt_sig_handler(int sig)
{
	char	c;

	c = '\r';
	if (sig == SIGINT)
	{
		g_exit_code = -42;
		rl_on_new_line();
		ioctl(STDIN_FILENO, TIOCSTI, &c);
	}
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
	if (cnt % 2 || !end_by_pipe(*one_ln) || !end_by_esc(one_ln))
		return (0);
	return (1);
}

int	read_internal_prompt(char **one_ln, char *ln_read, int read_cnt)
{
	while (!check_line_end(one_ln, ln_read))
	{
		if (read_cnt)
			free(ln_read);
		signal(SIGINT, internal_prompt_sig_handler);
		ln_read = readline("> ");
		if (g_exit_code == -42)
			break ;
		if (!ln_read)
		{
			write(STDERR_FILENO,
				"🤣 esh: syntax error unexpected end of file\n", 46);
			free(ln_read);
			break ;
		}
		add_history(rl_line_buffer);
		read_cnt++;
	}
	if (read_cnt || (g_exit_code == -42 && !read_cnt))
		free(ln_read);
	if (g_exit_code == -42)
		return (0);
	return (1);
}
