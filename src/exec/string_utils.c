/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:06 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/04 12:27:40 by ghan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	*ft_substr_wo_chr(char *str, unsigned int start, size_t len, char c)
{
	size_t	idx;
	char	*ret;

	idx = 0;
	ret = (char *)ft_calloc(len + 1, sizeof(char));
	while (idx < len)
	{
		if (str[start] != c
			|| (str[start] == c && is_charset(str[start + 1], " \n\t")))
			ret[idx++] = str[start];
		else if (str[start + 1] == c)
			ret[idx++] = str[start++ + 1];
		if (str[start])
			start++;
	}
	ret[idx] = '\0';
	return (ret);
}

static char	*strdup_skip_bsnl(char *s, size_t len)
{
	char	*ret;
	int		idx;
	int		k;

	ret = (char *)ft_calloc(len + 1, sizeof(char));
	k = 0;
	idx = 0;
	while (s[idx])
	{
		if (s[idx] == '\\' && s[idx + 1] == '\n')
			idx += 2;
		else
			ret[k++] = s[idx++];
	}
	return (ret);
}

static void	rm_bsnl_replace_bstab(char **str)
{
	int		idx;
	size_t	len;
	char	*to_fr;

	len = ft_strlen(*str);
	idx = 0;
	while (*(*str + idx))
	{
		if (*(*str + idx) == '\\')
		{
			idx++;
			if (*(*str + idx) == '\t')
				*(*str + idx) = ' ';
			else if (*(*str + idx) == '\n')
				len -= 2;
			idx++;
		}
		if (*(*str + idx) != '\0' && *(*str + idx) != '\\')
			idx++;
	}
	to_fr = *str;
	*str = strdup_skip_bsnl(*str, len);
	free(to_fr);
	to_fr = NULL;
}

int	make_string(char *cmdset, t_cmd *cmd, int p_idx)
{
	int	len;

	len = 2;
	if (!ft_strcmp(cmdset, "\'\'") || !ft_strcmp(cmdset, "\"\""))
		cmd->params[p_idx] = ft_strdup("");
	else if (is_charset(cmdset[0], "'"))
	{
		len = get_quote_len(&cmdset[1], "'", '\0');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 1, len, '\0');
	}
	else if (is_charset(cmdset[0], "\""))
	{
		len = get_quote_len(&cmdset[1], "\"", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 1, len, '\\');
		rm_bsnl_replace_bstab(&cmd->params[p_idx]);
	}
	else
	{
		len = get_wspace_len(&cmdset[0], "\t\n ", '\\');
		cmd->params[p_idx] = ft_substr_wo_chr(cmdset, 0, len, '\\');
	}
	if (!len)
		len = 2;
	return (len);
}
