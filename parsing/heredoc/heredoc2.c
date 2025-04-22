/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tobourge <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:19:13 by tobourge          #+#    #+#             */
/*   Updated: 2025/04/22 17:19:13 by tobourge         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* write the random string into the filename tab */

int	ft_dup_filename(t_hdoc *infos, char *buff)
{
	int	j;

	j = 0;
	infos->filename = ft_strdup(buff);
	if (!infos->filename)
	{
		ft_dprintf(2, "dup filename and buff fail\n");
		return (0);
	}
	while (j < 10)
	{
		if (infos->filename[j] < 0)
			infos->filename[j] *= (-1);
		if (!ft_isalpha((int)infos->filename[j]))
			infos->filename[j] = infos->filename[j] % ('z' - 'a') + 'a';
		j++;
	}
	return (1);
}

/* open the random file and read 10 characters from it. */

int	ft_init_random(t_hdoc *infos)
{
	int		rdmfd;
	char	buff[11];
	int		size;

	rdmfd = open("/dev/random", O_RDONLY);
	if (rdmfd == -1)
	{
		ft_dprintf(2, "open /random fail\n");
		return (0);
	}
	size = read(rdmfd, buff, 10);
	if (size == -1)
	{
		close(rdmfd);
		ft_dprintf(2, "read buffer /random fail\n");
		return (0);
	}
	buff[10] = '\0';
	close(rdmfd);
	if (!ft_dup_filename(infos, buff))
		return (0);
	return (1);
}

/* write a random filename and open it */

int	ft_copy_herefile(t_list *line, t_hdoc *infos)
{
	if (!infos->filename)
	{
		if (!ft_init_random(infos))
		{
			free(infos->str);
			free(infos->eof);
			return (0);
		}
	}
	line->fd_hdoc = open(infos->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (line->fd_hdoc == -1)
	{
		free(infos->filename);
		free(infos->str);
		free(infos->eof);
		ft_dprintf(2, "heredoc fd fail\n");
		return (0);
	}
	return (1);
}
