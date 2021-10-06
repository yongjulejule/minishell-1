/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ghan <ghan@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 12:08:48 by ghan              #+#    #+#             */
/*   Updated: 2021/10/06 11:42:07 by yongjule         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* SECTION - include .h files */

# define READLINE_LIBRARY 1
# include <sys/errno.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include "libft.h"
# include "parse.h"
# include <readline/readline.h>
# include <readline/history.h>

/* user define */

# define BACKUP_FD 255
# define ESH_ASCII "                                                  _.,:\
=-,,cccedbec.\n\
                             ,                 .e$P\"ud$$$$$$$$$$$$$$bc\n\
                          `. ,              .d$$\":d$$$$$$$$$$$$$$$$$$$$b.\n\
                        ~-. ,uee$$$$$eu .,d$$P\",d$$$$$$$$$$$$$$$$$$$$$$$$L\n\
                         .d$$$$$$$$$$$$$h`\",ue$$$$$$$$$$$$$$<$$$$$$$$$$$$$\n\
                        d$$$$$$$$$$$$$$$$$c`$$$$$$$$$$$$$$$>d$$$$$$$$$$$F\n\
                       ,$$$$$$$$$$$$$$$$$$$b.?$$$$$$$$$$$$$<$$$$$$$$$P\"\n\
                 .,ze$$$$$$$$$$$$$$$$$$$$$uu$ $$$$$$$$$$$$F<$$$$$$P\"\n\
         .ue=+==\",,\"?$$$$$$$??$$$$$$$$$$$$$b`$$$$$$$$$$$$>$$$$$F\n\
       z=\',ed$$$$$$$$$$$$$$$$F $6$$$$$$$$$$$$$.?$$$$$$$$$$$h<$$$$\n\
    ,d\",$$$$$$$$$$$$$$$$$$$$$b$$$$$$$$$$$$$\",`$c\"$$$$$$$$$$$h<$$$,\n\
   zF,$$$$$$$$$$$$$$$$$$$\"$$$$$$F?$$$$$$$$$\'  $$h\'$$$$$$$$$$$$><$$\n\
  dS$$$$$$$$$$$$$$$$$$$$$.$$$$$$$ r \"$$$$$$bud$$F $$$$$$$$$$$$$b$$h\n\
 d$$$$$$$$$$$$$$$$$$$$$$$b`$$$$$$b. u$$$$$$$$$c( <$$$$$$$$$$$$$$$$$h\n\
J$$$$$$$$$$$$$$$$$$$$$$$$$h`$$$$$$$$$$$$$$$$$$$$$beu`\"?$$$$$$$$$$$$$L\n\
$$$$$$$$$$$$$$$$$$$$$$$$$$$b`\"???$PF+==-,\"??$$$$$$$$$$b,?$$$$$$$$$$$\n\
`$$$$$$$$$$$$$$$$$$$$$$$$$$$<$$$$buu$$$$$$$$$ cecececc,??b`$$$$$$$$$$\n\
  \"?$$$$$$$$$$$$$$FJ$$$$$$$F<$$$$$$$$$$$$$$$$ $$$$$$$$$b$bud$$$$$$$$$\n\
     \'\"$$$$$$$$$$FJ$$$$$$$$\'d$$$$$$$$$$$$$$$$ $$$$$$$$$$$$$$$$$$$$$$F\n\
        3$$$$$$$Fd$$$$$$$$\",$$$$$$$$$$$\"$$$$F `$$$$$$$$$$$$$$$$$$$$$\n\
        d$$$$$$$d$$$$$$$F.d$$$$$ $$$P\"=2$$$$    ?$$$$$$$$$$$$$$$$$$\n\
      z$$$$$$$$$$3$$$P\",d$$$$$$F P\" =J$$$$$F     `?$$$$$$$$$$$$$P\"\n\
    u$$$$$$$$$$$L$$\"   $$$$$$$$    `$6R?==?          \"???????\"\n\
    $$$$$$$$$$$$$$     3$bec:/      \'$$CCLL\n\
     ?$$$$$$$$$$$$b.   =?$??$+     :d???$??b.\n\
        `\"   \"  \"\'\"      \'\"  \"`\n\n\
 ____  __    ____  ____  _  _   __   __ _  ____    __\
__  _  _  ____  __    __   \n\
(  __)(  )  (  __)(  _ \\/ )( \\ / _\\ \
(  ( \\(_  _)  / ___)/ )( \\(  __)(  )  (  )  \n\
 ) _) / (_/\\ ) _)  ) __/) __ (/    \\/    /  )\
(    \\___ \\) __ ( ) _) / (_/\\/ (_/\\\n\
(____)\\____/(____)(__)  \\_)(_/\\_/\\_/\\_)\
__) (__)   (____/\\_)(_/(____)\\____/\\____/\n\n"

/* function declarations */

/* utils_main */

char	**esh_pre_process(int argc, char *argv[], char *envp[]);
void	parse_line_main(t_cmds **cmds_hd, char *ln_read, char *one_ln);
int		exec_cmd_main(t_cmds *cmds, char ***envp);
void	unexp_eof_sig_handler(void);
void	eof_exit(char *line_read);

/* main_signal */

void	main_sig_handler(int signal);
void	sigint_n_sigquit_handler(void (*sigfunction));
void	unexp_eof_sigint_handler(int sig);

/* diy envp */

char	**dup_envp(char *envp[], int set_len);
char	*ft_get_envp(char **ft_envp, char *var);
int		exprt(const char *path, char *const argv[], char ***const envp);
int		unset(const char *path, char *const argv[], char ***const envp);
void	reset_env(char ***envp);
void	sh_next_level(char ***envp);

#endif
