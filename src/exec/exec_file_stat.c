/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_file_stat.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 15:59:04 by yongjule          #+#    #+#             */
/*   Updated: 2021/10/03 16:07:27 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	s_isdir(int mode)
{
	int	s_ifmt;
	int	s_ifdir;

	s_ifmt = 0170000;
	s_ifdir = 0040000;
	return ((mode & s_ifmt) == s_ifdir);
}
