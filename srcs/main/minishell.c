/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 16:26:19 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/29 00:35:35 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	intern_exec(char *line, t_list **lst_env)
{
	char	**tab;
	t_ast	*ast;
	int		status;

	line = ft_expand_var(line, *lst_env, 1);
	line = ft_expand_tilde(line);
	line = ft_expand_exit_status(line);
	tab = ft_split_charset_with_quote(line, WHITESPACES, lst_env);
	free(line);
	if (!tab)
	{
		perror("minishell: malloc failure");
		ft_free_split(&tab);
		return ;
	}
	ast = ft_init_ast(ft_tablen(tab), tab);
	ft_save_ast_link(&ast);
	ft_free_split(&tab);
	ft_execute_ast(ast, lst_env, &status);
	ft_set_status(status);
	ft_set_wip(1);
	ft_clean_ast(&ast);
}

void	ft_minishell(t_prompt *prompt, t_list **lst_env)
{
	char	*line;

	while (1)
	{
		ft_generate_prompt(*lst_env, prompt);
		line = readline(prompt->prompt_to_display);
		free(prompt->prompt_to_display);
		if (!line)
			break ;
		if (!*line || (ft_strlen(line) == 1 && line[0] == ':'))
		{
			free(line);
			continue ;
		}
		add_history(line);
		if (!ft_easy_error_reviews(line))
		{
			free(line);
			continue ;
		}
		intern_exec(line, lst_env);
		if (ft_get_end())
			break ;
	}
}
