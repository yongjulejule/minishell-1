/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_qm_flag_alloc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/09 00:45:24 by ghan              #+#    #+#             */
/*   Updated: 2021/10/09 02:37:50 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static size_t	dup_with_flag_len(int *flag, size_t n)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (i < n)
	{
		if (flag[i++] >= 0)
			len++;
	}
	return (len);
}

char	*strndup_with_flag(char *s1, int *flag, size_t n, size_t add)
{
	char	*ret;
	size_t	i;
	size_t	k;

	ret = (char *)ft_calloc(dup_with_flag_len(flag, n) + add + 1, 1);
	i = 0;
	k = 0;
	while (i < n)
	{
		if (flag[i] == 0)
			ret[k++] = s1[i];
		else if (flag[i] == ADD_BS)
		{
			ret[k++] = '\\';
			ret[k++] = s1[i];
		}
		i++;
	}
	return (ret);
}

void	flag_qm(char *s, int *i, int *cp_flag, size_t *add_cnt)
{
	char	qm;
	int		fst;

	fst = *i;
	qm = s[fst];
	skip_qm(s, i, "\"'");
	cp_flag[fst] = RM_CHAR;
	cp_flag[*i] = RM_CHAR;
	brace_skip_rm_ws(s, cp_flag, qm);
	*add_cnt += flag_add_cnt(s, cp_flag, fst + 1, *i);
}
