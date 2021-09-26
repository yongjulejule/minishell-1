/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jun <yongjule@42student.42seoul.kr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 17:27:15 by jun               #+#    #+#             */
/*   Updated: 2021/09/26 14:40:27 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	wstatus(int status)
{
	return (status & 0177);
}

int	wifexited(int status)
{
	return (wstatus(status) == 0);
}

int	wifsignaled(int status)
{
	return (wstatus(status) != 0177 && wstatus(status) != 0);
}

int	wexitstatus(int status)
{
	return ((status >> 8) & 0x000000ff);
}

int	wtermsig(int status)
{
	return (wstatus(status));
}
