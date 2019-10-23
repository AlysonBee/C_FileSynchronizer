/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gsferopo <gsferopo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/22 12:56:24 by bmoodley          #+#    #+#             */
/*   Updated: 2018/01/22 07:44:53 by gsferopo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	build(char **line, char **new, char *pos)
{
	*line = ft_strsub(*new, 0, ft_strlen(*new) - ft_strlen(pos));
	*new = ft_strdup(pos + 1);
}

static int	ft_append(int fd, char **new)
{
	char		*buf;
	char		*temp;
	int			ret;

	buf = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (buf == NULL)
		return (-1);
	ret = read(fd, buf, BUFF_SIZE);
	if (ret > 0)
	{
		buf[ret] = '\0';
		temp = ft_strjoin(*new, buf);
		free(*new);
		*new = temp;
	}
	free(buf);
	return (ret);
}

int			get_next_line(const int fd, char **line)
{
	static char *new = NULL;
	char		*pos;
	int			ret;

	if (new == NULL)
		new = ft_strnew(0);
	pos = ft_strchr(new, '\n');
	while (pos == NULL)
	{
		ret = ft_append(fd, &new);
		if (ret == 0)
		{
			if (ft_strlen(new) == 0)
				return (0);
			new = ft_strjoin(new, "\n");
		}
		if (ret < 0)
			return (-1);
		else
			pos = ft_strchr(new, '\n');
	}
	build(line, &new, pos);
	return (1);
}
