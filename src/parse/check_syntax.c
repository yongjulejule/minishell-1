/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:15:16 by ghan              #+#    #+#             */
/*   Updated: 2021/09/14 17:15:16 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static int	check_one_str(char *str)
{
	if (!ft_strcmp(";", str))
	{
		write(STDERR_FILENO,
			"🤣 esh: syntax error near unexpected token `;'\n", 49);
		return (0);
	}
	else if (!ft_strcmp("|", str))
	{
		write(STDERR_FILENO,
			"🤣 esh: syntax error near unexpected token `|'\n", 49);
		return (0);
	}
	return (1);
}

static void	write_error(char *first, char *secnd)
{
	if (!ft_strcmp(";", first) && !ft_strcmp(";", secnd))
		write(STDERR_FILENO,
			"🤣 esh: syntax error near unexpected token `;;'\n", 50);
	else if ((!ft_strcmp("", first) && !ft_strcmp(";", secnd))
		|| (!ft_strcmp(";", first) && !ft_strcmp("|", secnd)))
		write(STDERR_FILENO,
			"🤣 esh: syntax error near unexpected token `;'\n", 49);
	else if (!ft_strcmp("|", first) && !ft_strcmp("|", secnd))
		write(STDERR_FILENO,
			"🤣 esh: syntax error near unexpected token `||'\n", 50);
	else if ((!ft_strcmp("", first) && !ft_strcmp("|", secnd))
		|| (!ft_strcmp("|", first) && !ft_strcmp(";", secnd)))
		write(STDERR_FILENO,
			"🤣 esh: syntax error near unexpected token `|'\n", 49);
}

int	check_smcol_pipe_syntax(char **cmds)
{
	int	i;

	i = 0;
	while (cmds[i + 1])
	{
		if ((!ft_strcmp(";", cmds[i]) && !ft_strcmp(";", cmds[i + 1]))
			|| (!ft_strcmp("", cmds[i]) && !ft_strcmp(";", cmds[i + 1]))
			|| (!ft_strcmp("|", cmds[i]) && !ft_strcmp("|", cmds[i + 1]))
			|| (!ft_strcmp("", cmds[i]) && !ft_strcmp("|", cmds[i + 1]))
			|| (!ft_strcmp(";", cmds[i]) && !ft_strcmp("|", cmds[i + 1]))
			|| (!ft_strcmp("|", cmds[i]) && !ft_strcmp(";", cmds[i + 1])))
		{
			write_error(cmds[i], cmds[i + 1]);
			return (0);
		}
		i++;
	}
	if (!i && !check_one_str(cmds[i]))
		return (0);
	return (1);
}
