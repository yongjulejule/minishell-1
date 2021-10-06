/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diy_envp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 20:30:17 by ghan              #+#    #+#             */
/*   Updated: 2021/10/06 14:37:43 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_next_level(char ***envp)
{
	char	*argv[3];
	char	*lvl;
	char	*next_level;

	lvl = ft_get_envp(*envp, "SHLVL");
	if (!lvl)
		next_level = ft_strdup("1");
	else
		next_level = ft_itoa(ft_atoi(lvl) + 1);
	argv[0] = "export";
	argv[1] = ft_strjoin("SHLVL=", next_level);
	argv[2] = NULL;
	exprt("export", argv, envp);
	free(argv[1]);
	free(next_level);
}

void	reset_env(char ***envp)
{
	char	*argv[3];
	char	*cwd;
	char	*tmp;

	argv[0] = "unset";
	argv[1] = "_";
	argv[2] = NULL;
	unset("unset", argv, envp);
	argv[1] = "OLDPWD";
	unset("unset", argv, envp);
	argv[0] = "export";
	exprt("export", argv, envp);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_putendl_fd(strerror(errno), STDERR_FILENO);
	tmp = ft_strjoin("INPUTRC=", cwd);
	free(cwd);
	argv[1] = ft_strjoin(tmp, "/.inputrc");
	free(tmp);
	exprt("export", argv, envp);
	free(argv[1]);
}

char	*ft_get_envp(char **ft_envp, char *var)
{
	int		set_len;
	int		i;
	size_t	eq_idx;
	size_t	len;	

	set_len = ft_strsetlen(ft_envp);
	i = -1;
	while (++i < set_len)
	{
		if (ft_strchr(ft_envp[i], '='))
		{
			eq_idx = ft_strchr(ft_envp[i], '=') - ft_envp[i];
			len = eq_idx;
			if (ft_strlen(var) > eq_idx)
				len = ft_strlen(var);
			if (!ft_strncmp(ft_envp[i], var, len))
				return (ft_envp[i] + eq_idx + 1);
		}
		else if (!ft_strcmp(ft_envp[i], var))
			return (ft_envp[i] + ft_strlen(ft_envp[i]));
	}
	return (NULL);
}

char	**dup_envp(char *envp[], int set_len)
{
	char	**ret;
	int		i;

	ret = (char **)ft_calloc(set_len + 1, sizeof(char *));
	i = -1;
	while (++i < set_len)
		ret[i] = ft_strdup(envp[i]);
	return (ret);
}
