/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yongjule <yongjule@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 10:31:34 by yongjule          #+#    #+#             */
/*   Updated: 2021/09/24 11:02:36 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "libft.h"
# include <sys/errno.h>
# include <stdio.h>
# include <string.h>

/*
typedef enum e_builtin
{
	echo = 0,
	cd,
	pwd,
	exprt,
	unset,
	env,
	ext,
	notbuiltin,
}	t_builtin;
*/

void	exprot(const char *path, char *const argv[], char **envp);
void	echo(const char *path, char *const argv[], char *const envp[]);
void	ext(const char *path, char *const argv[], char *const envp[]);

#endif
