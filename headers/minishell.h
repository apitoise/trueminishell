/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 17:06:20 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/15 15:34:40 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <string.h>
# include <limits.h>
# include <termios.h>
# include <curses.h>
# include <ncurses.h>
# include <term.h>
# include <errno.h>
# define MAX_FD 3000

typedef struct s_varlist
{
	char				*name;
	char				*content;
	int					visible;
	void				*next;
}						t_varlist;

typedef struct s_history
{
	char				*cmdline;
	size_t				len;
	size_t				capacity;
}						t_history;

typedef struct s_sig
{
	pid_t				pid;
	t_history			**cmdl;
	char				**cmdt;
}						t_sig;

typedef struct s_struct
{
	int					exit;
	int					pipe;
	int					chevrons;
	char				*s;
	char				**input;
	char				**cmd;
	char				**env;
	pid_t				pid;
	t_varlist			*lst;
	int					ret;
	int					childps;
	int					childret;
	int					stdout_fd;
	int					stdin_fd;
	int					was_chevr;
	int					was_lchevr;
	int					stdin_copy;
	int					stdout_copy;
	char				*result;
	int					ttywidth;
	int					ttyheight;
	int					startposx;
	int					posx;
	int					posy;
	t_history			**hstab;
	size_t				hslen;
	size_t				hscapacity;
	unsigned int		hsindex;
}						t_struct;

extern t_sig			g_sig;

void					minishell(t_struct *st);
void					printlist_export(t_struct *st);
void					shell_init(void);
void					print_list(t_varlist **lst);
int						do_chevrons(char **cmd, t_struct *st);
char					**del_chevron(char **cmd);
void					ft_edit_cmd(char **cmd);
void					init_struct(t_struct *st, char **env);
void					init_sig_struct(void);
void					ft_cd(char **path, t_struct *st);
int						cd_getoldpwd(char **path, t_struct *st);
void					cd_deltilde(char *path);
int						ft_echo(char **cmd, t_struct *st);
void					ft_exit(char **cmd, int child, t_struct *st);
int						ft_pwd(char **cmd, t_struct *st);
int						ft_unset(char **cmd, t_struct *st);
void					ft_export(char **cmd, t_struct *st, int i);
char					*xp_getname(char *cmd, char c);
int						xp_catlist(char *name, char *content, t_varlist **lst);
void					xp_modiflist(char *name, char *content, int visible,
							t_varlist **lst);
int						xp_checkerror(char *arg, t_struct *st);
int						xp_newlst(char *name, char *content, int visible,
							t_varlist **lst);
int						xp_idnotvalid(char *arg, t_struct *st);
int						xp_varexist(char *str, t_varlist **lst);
int						xp_isalpha(char c);
void					ft_varlstclear(t_varlist **lst);
void					ft_free_hstab(t_history **hstab, int len);
void					ft_free_st(t_struct *st);
int						first_check(char **cmd, t_struct *st);
void					ft_env(t_struct *st);
void					init_shlvl(t_struct *st);
int						elem_error(char *name, char *content);
int						gethomevaluebis(t_varlist *current, char **home,
							int par, t_struct *st);
int						homenotset(t_struct *st);
void					modif_pwd(char *name, char *content, t_varlist **lst);
void					do_builtin(char **cmd, t_struct *st);
void					do_routine(t_struct *st);
void					chevrons_routine(char **cmd, t_struct *st);
void					do_pipe(t_struct *st);
char					**get_env(char **env);
void					ft_split_cmd(const char *s, char c,
							t_struct *st, int i);
char					**ft_split_cmdline(char *s, char c);
int						ft_error(char *s);
void					ft_freeptr(void **ptr);
int						ft_syntax_error(char *token, t_struct *st);
void					ft_checkpath(char **cmd, t_struct *st);
void					not_cmd(char **str, t_struct *st);
void					init_lstenv(char **env, t_struct *st);
void					get_signals(void);
void					ctrl_c(int useless);
void					ctrl_backslash(int useless);
void					ft_fork(char **cmd, char *filepath, t_struct *st);
void					ft_exec(char **cmd, char *filepath, t_struct *st);
int						ft_parsecmdline(char **s, t_struct *st);
int						ft_checkvalid(char *s, t_struct *st);
int						ft_dollar(char **s1, t_struct *st);
int						ft_dollar_d(char **s1, int *i, char **s2, t_struct *st);
void					ft_dollar_cat(char **s2, char **tmp);
void					ft_dollar_alias_cpybis_loop(char **tmp2, char *str,
							int toq);
void					ft_dollar_alias_cpybis_loop2(char **tmp2, char *str,
							int i, int *j);
int						ft_addbslash(char **s);
int						ft_rmbslash(char **s, int i, int j);
int						ft_tkorqt(char *str, int i);
int						ft_freestr(char *str);
int						ft_isspechar(char c);
int						init_termcap(t_struct *st);
char					*ft_termcap(t_struct *st);
int						tc_editcmdl(char *buff, t_history *new, t_struct *st);
int						tc_ediths(t_history **new, t_struct *st);
int						tc_browsehs(char c, t_history *new, t_struct *st);
int						ft_getposition(t_struct *st);
int						ft_getwinsz(t_struct *st);
int						ft_winszdiff(t_history *new, t_struct *st);
int						ft_putc(int c);
int						ft_isblank(char *str);
int						ft_tputsstr(char *str, t_history *new, t_struct *st);
int						ft_nextline(t_history *new, t_struct *st);
void					ft_freehs(t_history *new);
int						get_i(char c);
void					pipe_or_chevron(char c, t_struct *st);

#endif
