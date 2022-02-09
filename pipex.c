/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngobert <ngobert@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 13:46:29 by ngobert           #+#    #+#             */
/*   Updated: 2022/02/09 16:20:26 by ngobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_pipex(t_data *data, char *cmd1, char *cmd2)
{
	if (pipe(data->fd) == -1)
		ft_error("Failed opening the pipe\n");
	data->child_1 = fork();
	if (data->child_1 == -1)
		ft_error("Failed forkink for child 1\n");
	if (data->child_1 == 0)
		child1_exec(data, cmd1);
	data->child_2 = fork();
	if (data->child_2 == -1)
		ft_error("Failed forking for child 2\n");
	if (data->child_1 == 0)
		child2_exec(data, cmd2);
	close_and_wait(data);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	t_data	data;
	if (argc != 5)
		ft_error("Too much args");	
	else
	{
		data = get_args(argc, argv, envp);
		data.infile = open(argv[1], O_RDONLY);
		data.outfile = open(argv[4], O_TRUNC | O_CREAT | O_WRONLY);
		if (!data.infile || !data.outfile)
			ft_error("Problem opening files\n");
		ft_pipex(&data, argv[1], argv[2]);
	}
}
