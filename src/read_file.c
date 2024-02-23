/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:35:00 by Philip            #+#    #+#             */
/*   Updated: 2024/02/23 18:26:07 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*list_to_str(t_list *list);
/* static void	list_free(t_list **list); */

void	ensure_eol(t_list *last)
{
	char	*temp;

	if (*(ft_strchr(last->content, '\0') - 1) != '\n')
	{
		temp = ft_strjoin(last->content, "\n");
		free(last->content);
		last->content = temp;
	}
}

char	*read_file(const char *file)
{
	int		fd;
	char	*all;
	char	*line;
	t_list	*list;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		exit(1);
	}
	list = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (line && line[0])
			ft_lstadd_back(&list, ft_lstnew(line));
		else
			break ;
	}
	ensure_eol(ft_lstlast(list));
	all = list_to_str(list);
	ft_lstclear(&list, free);
	return (all);
}

static char	*list_to_str(t_list *list)
{
	t_list	*node;
	size_t	len;
	char	*s;

	if (!list)
		return (NULL);
	len = 0;
	node = list;
	while (node)
	{
		len += ft_strlen(node->content);
		node = node->next;
	}
	s = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (NULL);
	node = list;
	while (node)
	{
		ft_strlcat(s, node->content, len + 1);
		node = node->next;
	}
	return (s);
}

int	hexa_atoi(const char *str)
{
	size_t				i;
	int					n;
	char				*copy;
	static const char	*lower = "0123456789abcdef";

	copy= ft_strndup(str, 12);
	n = 0;
	i = 2;
	while (copy[i])
	{
		if (ft_isupper(copy[i]))
			copy[i] = ft_tolower(copy[i]);
		i++;
	}
	i = 2;
	while (ft_strchr(lower, copy[i]))
	{
		n *= 16;
		n += (int)(ft_strchr(lower, copy[i]) - lower);
		i++;
	}
	free(copy);
	return (n);
}
