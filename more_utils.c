/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 18:46:12 by ngobert           #+#    #+#             */
/*   Updated: 2022/02/11 10:36:49 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free(char **tab)
{
	int	i;

	i = 0;
	while (tab[i++])
	{
		tab[i] = (free(tab[i]), NULL);
	}	
}

t_data	get_args(int argc, char **argv, char **envp)
{
	t_data	tmp;

	tmp.argc = argc;
	tmp.argv = argv;
	tmp.envp = envp;
	tmp.infile = 0;
	tmp.outfile = 0;
	return (tmp);
}

void	ft_error(const char *str)
{
	perror(str);
	exit(EXIT_FAILURE);
}
