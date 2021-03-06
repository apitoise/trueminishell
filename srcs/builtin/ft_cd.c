/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:23:55 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/15 17:07:01 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static int	gethomevalue(char **path, t_struct *st, int par)
{
	t_varlist	*current;
	char		*home;
	char		*tmp;

	current = st->lst;
	while (current && ft_strcmp(current->name, "HOME"))
		current = current->next;
	if (gethomevaluebis(current, &home, par, st))
		return (1);
	cd_deltilde(*path);
	tmp = ft_strjoin(home, *path);
	if (!tmp)
		return (1);
	free(*path);
	*path = tmp;
	return (0);
}

static int	gotopath(char *path, t_struct *st)
{
	int		ret;
	char	buff[PATH_MAX];
	char	*newpwd;

	if (!ft_strcmp(path, ""))
	{
		free(path);
		return (0);
	}
	ret = chdir(path);
	if (ret == -1 && path)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putchar_fd('\n', 2);
		st->ret = 1;
	}
	free(path);
	if (!getcwd(buff, PATH_MAX))
		return (-1);
	newpwd = ft_strdup(buff);
	modif_pwd("PWD", newpwd, &st->lst);
	return (ret);
}

static void	editpath_pathinit(char **path, int *par)
{
	*path = malloc(sizeof(char) * 2);
	(*path)[0] = '~';
	(*path)[1] = '\0';
	*par = 1;
}

static void	editpath(char *cmd, t_struct *st, int par, int ret)
{
	char	buff[PATH_MAX];
	char	*path;
	int		out;

	out = 1;
	if (st->pipe > 0)
		out = st->stdout_fd;
	if (!cmd)
		editpath_pathinit(&path, &par);
	else if (!ft_strcmp(cmd, "-"))
	{
		if (cd_getoldpwd(&path, st))
			return ;
		ft_putstr_fd(path, out);
		ft_putstr_fd("\n", out);
	}
	else
		path = ft_strdup(cmd);
	if (path[0] == '~' && gethomevalue(&path, st, par))
		return (ft_freeptr((void **)&path));
	if (!getcwd(buff, PATH_MAX))
		ret = 1;
	if (gotopath(path, st) != -1 && !ret)
		modif_pwd("OLDPWD", ft_strdup(buff), &st->lst);
}

void	ft_cd(char **cmd, t_struct *st)
{
	int	par;

	par = 0;
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		st->ret = 1;
	}
	else
		editpath(cmd[1], st, par, 0);
}
