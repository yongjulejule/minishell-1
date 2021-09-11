/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 03:37:17 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/11 15:48:45 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipe.h"

static char	*prefix_dir_to_cmd(t_args *args, char *param, int nth_path)
{
	char		*tmpstr;
	char		*tmp_cmd;

	tmpstr = ft_strjoin(args->env_path[nth_path], "/");
	tmp_cmd = ft_strjoin(tmpstr, param);
	free(tmpstr);
	tmpstr = NULL;
	return (tmp_cmd);
}

void	check_cmd_validity(t_args *args, t_cmd *cmd, char *param)
{
	int			nth_path;
	char		*tmp_cmd;
	extern int	errno;

	nth_path = 0;
	while (args->env_path[nth_path] != NULL)
	{
		tmp_cmd = prefix_dir_to_cmd(args, param, nth_path);
		if (access(tmp_cmd, X_OK) == -1)
		{
			free(tmp_cmd);
			tmp_cmd = NULL;
		}
		else
		{
			free(param);
			param = NULL;
			cmd->params[0] = tmp_cmd;
			return ;
		}
		nth_path++;
	}
}
