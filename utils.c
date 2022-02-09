/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 14:45:21 by ngobert           #+#    #+#             */
/*   Updated: 2022/02/09 18:13:18 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_line(t_data *data)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (data->envp[i++])
	{
			path = ft_strnstr(data->envp[i], "PATH=", ft_strlen(data->envp[i]));
			if (path)
			{
				path = ft_substr(path, 5, ft_strlen(path));
				if (!path)
					ft_error("Substr failed :(\n");
				return (path);
			}
	}
}

char	**get_paths(t_data *data)
{
	char	*str;
	char	**paths;

	str = get_line(data);
	paths = ft_split(str, ':');
	if (!paths)
		ft_error("Split failed\n");
	return (free(str), paths);
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
