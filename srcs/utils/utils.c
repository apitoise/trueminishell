/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apitoise <apitoise@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/19 15:28:04 by apitoise          #+#    #+#             */
/*   Updated: 2021/06/15 15:58:09 by lgimenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"
#include "../../libft/libft.h"

static void	print_it_loop(t_varlist *tmp, int i, int out)
{
	if (tmp->content[i] == '\\' || tmp->content[i] == '"'
		|| tmp->content[i] == '$')
		write(out, "\\", 1);
	write(out, &(tmp->content[i]), 1);
}

static char	*print_it(t_struct *st, t_varlist **cur, t_varlist *tmp)
{
	int	i;
	int	out;

	out = 1;
	if (st->pipe > 0)
		out = st->stdout_fd;
	*cur = st->lst;
	if (!ft_strcmp(tmp->name, "_"))
		return (tmp->name);
	ft_putstr_fd("declare -x ", out);
	ft_putstr_fd(tmp->name, out);
	if (tmp->content)
	{
		ft_putstr_fd("=\"", out);
		i = -1;
		while (tmp->content[++i])
			print_it_loop(tmp, i, out);
		ft_putstr_fd("\"", out);
	}
	ft_putstr_fd("\n", out);
	return (tmp->name);
}

static int	print_bis(t_varlist *tmp, t_varlist *current, char *lw, int i)
{
	if (!tmp->name[0] || tmp->name == lw)
		*tmp = *current;
	else
	{
		i = 0;
		while (tmp->name[i] == current->name[i] && tmp->name[i]
			&& current->name[i])
			i++;
		if (current->name[i] < tmp->name[i])
			*tmp = *current;
	}
	return (i);
}

void	printlist_export(t_struct *st)
{
	t_varlist	*current;
	t_varlist	tmp;
	char		*lastwrit;
	int			i;

	if (st->lst == NULL)
		return ;
	current = st->lst;
	lastwrit = "";
	tmp.name = "";
	while (current != NULL)
	{
		i = 0;
		while (lastwrit[i] == current->name[i] && lastwrit[i]
			&& current->name[i])
			i++;
		if (current->name[i] > lastwrit[i])
			print_bis(&tmp, current, lastwrit, i);
		if (current->next == NULL && tmp.name != lastwrit && tmp.visible == 1)
			lastwrit = print_it(st, &current, &tmp);
		else
			current = current->next;
	}
}
