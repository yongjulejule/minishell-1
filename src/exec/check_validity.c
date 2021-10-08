/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_validity.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/11 16:33:20 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/08 15:15:26 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*prefix_dir_to_cmd(t_args *args, char *param, int nth_path)
{
	char		*tmpstr;
	char		*tmp_cmd;

	if (ft_strchr(param, '/'))
		return (ft_strdup(param));
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
	struct stat	status;

	nth_path = 0;
	while (args->env_path[nth_path] != NULL)
	{
		if (!param || !*param)
			return ;
		tmp_cmd = prefix_dir_to_cmd(args, param, nth_path);
		if (stat(tmp_cmd, &status) == -1 || s_isdir(status.st_mode))
			free(tmp_cmd);
		else
		{
			free(param);
			param = NULL;
			cmd->params[0] = tmp_cmd;
			return ;
		}
		tmp_cmd = NULL;
		nth_path++;
	}
}
