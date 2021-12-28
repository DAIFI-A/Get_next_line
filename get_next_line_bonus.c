/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adaifi <adaifi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 11:03:12 by mck-d             #+#    #+#             */
/*   Updated: 2021/12/28 20:08:53 by adaifi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include"get_next_line.h"

char	*readstr(int fd, char *str)
{
	char	*buff;
	int		n;

	buff = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	n = 1;
	while(!ft_strchr(str, '\n') && n != 0)
	{
		n = read(fd, buff, BUFFER_SIZE);
		if (n == -1)
		{
			free(buff);
			return(NULL);
		}
		if (n == 0)
			break ;
		buff[n] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	return(str);
}

char	*newstr(char *old_str)
{
	int		i;
	int		j;
	char	*str = NULL;

	i = 0;
	while (old_str[i] && old_str[i] != '\n')
		i++;
	if (!old_str[i])
	{
		free(str);
		free(old_str);
		return (NULL);
	}
	str = (char *)malloc(sizeof(char) * (ft_strlen(old_str) - i + 1));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (old_str[i])
		str[j++] = old_str[i++];
	str[j] = '\0';
	free(old_str);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = readstr(fd , str);
	if (!str)
		return (NULL);
	line = get_line(str);
	str = newstr(str);
	return (line);
}

// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;

// 	fd1 = open("nl", O_RDONLY);
// 	i = 1;
// 	while (i < 3)
// 	{
// 		line = get_next_line(fd1);
// 		printf("line [%02d]: %s", i, line);
// 		i++;
// 	}
// 	close(fd1);
// 	return (0);
// }
