/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_unncessary_qm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 12:10:29 by ghan              #+#    #+#             */
/*   Updated: 2021/09/29 12:44:49 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

static void	fill_cp_flag(int *cp_flag, char *s, size_t len, char qm)
{
	int		cnt;
	int		i;

	cnt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '\\')
		{
			i++;
			if (s[i] == qm || s[i] == '\\')
				i++;
		}
		else
		{
			if (s[i] == qm)
				cnt++;
			if ((!i && s[i] == qm)
				|| (i && !(cnt % 2) && is_charset(s[i], " \t\n"))
				|| (cnt % 2 && is_charset(s[i + 1], " \t\n")))
				cp_flag[i] = -1;
			if (cnt == 2)
			{
				cnt = 0;
				qm = ft_strchrset(s + i + 1, "\"'");
			}
			if (s[i])
				i++;
		}
	}
}

void	rm_unnecessary_qm(t_cmds *cmds_hd)
{
	t_cmds	*cur;
	int		*cp_flag;
	int		len;
	char	qm;

	cur = cmds_hd->next;
	while (cur)
	{
		if (ft_strchrset(cur->cmd, "\"'"))
		{
			len = ft_strlen(cur->cmd);
			cp_flag = (int *)ft_calloc(len, sizeof(char));
			fill_cp_flag(cp_flag, cur->cmd, len,
				*ft_strchrset(cur->cmd, "\"'"));
		}
		cur = cur->next;
	}
}