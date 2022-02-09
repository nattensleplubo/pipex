/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:45:21 by ngobert           #+#    #+#             */
/*   Updated: 2022/02/09 15:39:14 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
