/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_structure.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 16:16:34 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/26 17:18:32 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static void	free_ptr(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

void	free_double_ptr(void ***ptr)
{
	void	**tmp;

	tmp = *ptr;
	while (*tmp)
	{
		free_ptr(tmp);
		tmp++;
	}
	free(*ptr);
	*ptr = NULL;
}

static void	free_rdr_lst(t_rdr **rdr)
{
	t_rdr	*cur;
	t_rdr	*tmp;

	cur = *rdr;
	while (cur)
	{
		tmp = cur;
		free_ptr((void **)&tmp->file);
		free_ptr((void **)&tmp->limiter);
		cur = cur->next;
		free(tmp);
	}
	*rdr = NULL;
}

void	free_arg_structure(t_args *args)
{
	int	idx;

	idx = 0;
	while (idx < args->cnt)
	{
		free_rdr_lst(&args->cmd[idx].rdr);
		free_double_ptr((void ***)&args->cmd[idx].params);
		idx++;
	}
	free_double_ptr((void ***)&args->env_path);
	free_ptr((void **)&args->cmd);
	free_ptr((void **)&args);
}
