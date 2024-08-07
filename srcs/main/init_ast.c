/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 21:40:53 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/27 09:55:06 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_arg	*init_arg(char **av)
{
	t_arg	*arg;

	while (!*av || **av == '|' || ft_is_redirection(*av))
	{
		if (!*av || **av == '|')
			return (NULL);
		av++;
		if (*av)
			av++;
	}
	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (perror("minishell: init_arg"), NULL);
	arg->next = init_arg(av + 1);
	arg->arg = ft_strdup(*av);
	return (arg);
}

static t_redir	*init_redirect(char **av)
{
	t_redir	*redir;

	while (*av && !ft_is_redirection(*av) && ft_strcmp(*av, "|"))
		av++;
	if (!*av || !ft_is_redirection(*av))
		return (NULL);
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (perror("minishell: init_redir"), NULL);
	*redir = (t_redir){0};
	if (*av)
		redir->type = ft_is_redirection(*av++);
	if (*av && **av)
		redir->file = ft_strdup(*av++);
	else
		redir->file = 0;
	if (*av)
		redir->next = init_redirect(av);
	return (redir);
}

static t_ast	*ft_init_head_node(char **av)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
		return (perror("minishell: init_command"), NULL);
	node->left = init_arg(av);
	node->right = init_redirect(av);
	node->type = COMMAND;
	return (node);
}

static t_ast	*ft_new_ast_branch(t_ast *node_command, int ac, char **av)
{
	t_ast	*node;

	node = malloc(sizeof(t_ast));
	if (!node)
	{
		ft_clean_ast(&node_command);
		return (perror("minishell: init_ast"), NULL);
	}
	node->left = node_command;
	node->type = PIPE;
	node->right = ft_init_ast(ac - 1, av + 1);
	return (node);
}

t_ast	*ft_init_ast(int ac, char **av)
{
	t_ast	*node_command;

	if (!ac)
		return (NULL);
	node_command = ft_init_head_node(av);
	while (*av && **av != '|')
	{
		av++;
		ac--;
	}
	if (*av)
		return (ft_new_ast_branch(node_command, ac, av));
	else
		return (node_command);
}
