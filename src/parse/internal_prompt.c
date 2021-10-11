/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_prompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 23:48:18 by ghan              #+#    #+#             */
/*   Updated: 2021/10/11 14:51:17 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

extern int	g_exit_code;

static int	cnt_skip_qm(char *one_ln, char *qm, size_t i)
{
	int	cnt;

	cnt = 0;
	i = 0;
	while (qm && *(one_ln + i))
	{
		if (cnt == 0 && *(one_ln + i) == '\\' && *(one_ln + i + 1) == '\'')
			i += 2;
		else if (qm && *(one_ln + i) == '\\')
		{
			i++;
			if ((*qm == '"' && *(one_ln + i) == *qm) || *(one_ln + i) == '\\')
				i++;
		}
		if (*(one_ln + i) == *qm)
			cnt++;
		if (cnt && cnt % 2 == 0)
		{
			cnt = 0;
			is_qm(one_ln + ++i, &qm);
		}
		else if (*(one_ln + i) != '\0' && *(one_ln + i) != '\\')
			i++;
	}
	return (cnt);
}

static unsigned long	ioctl_diy_request(unsigned int inout,
	char group, int num, size_t len)
{
	return (inout | ((len & IOCPARM_MASK) << 16) | ((group) << 8) | (num));
}

static void	internal_prompt_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_exit_code = INT_PRPT_SIGINT;
		rl_on_new_line();
		ioctl(STDIN_FILENO,
			ioctl_diy_request(IOC_IN, 't', 114, sizeof(char)), "\n");
	}
}

static int	check_line_end(char **one_ln, char *ln)
{
	char	*to_free;
	char	*qm;
	int		cnt;

	to_free = *one_ln;
	*one_ln = ft_strjoin(*one_ln, ln);
	free(to_free);
	is_qm(*one_ln, &qm);
	cnt = cnt_skip_qm(*one_ln, qm, 0);
	if (cnt % 2)
	{
		to_free = *one_ln;
		*one_ln = ft_strjoin(*one_ln, "\n");
		free(to_free);
	}
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
		if (g_exit_code == INT_PRPT_SIGINT)
			break ;
		if (!ln_read)
		{
			ft_putstr_fd("🤣 esh: syntax error \
unexpected end of file\n", STDERR_FILENO);
			g_exit_code = UNEXP_EOF_FLAG;
			break ;
		}
		else if (*ln_read)
			add_history(rl_line_buffer);
		read_cnt++;
	}
	if (read_cnt || (g_exit_code == -42 && !read_cnt))
		free(ln_read);
	if (g_exit_code == INT_PRPT_SIGINT || g_exit_code == UNEXP_EOF_FLAG)
		return (0);
	return (1);
}
