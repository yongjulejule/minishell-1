/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_unnecessary_qm.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:10:29 by ghan              #+#    #+#             */
/*   Updated: 2021/09/29 18:00:45 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	alloc_n_rm_qm(t_cmds *cur, int *cp_flag, size_t len,
				size_t n_zero)
{
	char	*to_free;
	size_t	i;
	size_t	k;

	i = 0;
	while (i < len)
	{
		if (!cp_flag[i])
			(n_zero)++;
		i++;
	}
	if (n_zero == len)
		return ;
	to_free = cur->cmd;
	cur->cmd = (char *)ft_calloc(n_zero + 1, sizeof(char));
	k = 0;
	i = 0;
	while (i < len)
	{
		if (!cp_flag[i])
			cur->cmd[k++] = to_free[i];
		i++;
	}
	free(to_free);
}

static void	jump_bs(char *s, int *i, char qm)
{
	(*i)++;
	if (s[*i] == qm || s[*i] == '\\')
		(*i)++;
}

static void	flag_qm(char *s, int *i, int *cnt, int *cp_flag)
{
	static int	pair_check;
	int			first;

	(*cnt)++;
	first = *i;
	if (!(*i) || (*i && (*cnt % 2) && !is_charset(s[*i - 1], " \t\n")))
	{
		cp_flag[*i] = -1;
		pair_check++;
	}
	(*cnt)++;
	skip_qmbt(s, i, "\"'");
	if (!pair_check && !is_charset(s[*i + 1], " \t\n") && s[*i + 1])
	{
		cp_flag[first] = -1;
		pair_check++;
	}
	if (pair_check % 2 && *cnt == 2)
	{
		cp_flag[*i] = -1;
		pair_check = 0;
	}
	(*i)++;
}

static void	fill_cp_flag(int *cp_flag, char *s, size_t len, char qm)
{
	int		cnt;
	int		i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\\')
			jump_bs(s, &i, qm);
		else
		{
			if (s[i] == qm)
				flag_qm(s, &i, &cnt, cp_flag);
			if (cnt == 2)
			{
				cnt = 0;
				if (ft_strchrset(s + i, "\"'"))
					qm = *ft_strchrset(s + i, "\"'");
			}
			if (s[i] && s[i] != qm)
				i++;
		}
	}
}

void	rm_unnecessary_qm(t_cmds *cmds_hd)
{
	t_cmds	*cur;
	size_t	len;
	size_t	n_zero;
	char	qm;
	int		*cp_flag;

	n_zero = 0;
	cur = cmds_hd->next;
	while (cur)
	{
		if (ft_strchrset(cur->cmd, "\"'"))
		{
			len = ft_strlen(cur->cmd);
			cp_flag = (int *)ft_calloc(len, sizeof(int));
			fill_cp_flag(cp_flag, cur->cmd, len,
				*ft_strchrset(cur->cmd, "\"'"));
			alloc_n_rm_qm(cur, cp_flag, len, 0);
			free(cp_flag);
		}
		cur = cur->next;
	}
}
