/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvecchio <hvecchio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 12:33:12 by hvecchio          #+#    #+#             */
/*   Updated: 2024/07/17 17:53:08 by hvecchio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_free master_data

//free_cmd_tbls

//ft_free_cmd_tab(tab)
{
	md->cmd_tbls = NULL;
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split && split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
	}
}

