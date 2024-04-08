/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:35:00 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 21:44:36 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

static char	*list_to_str(t_list *list);
static void	ensure_eol(t_list *last);

/**
 * @brief Reads the content of a file and returns it as one string.
 *
 * @param file The path to the file to read.
 * @return A dynamically allocated string containing the file's content, or NULL
 *         on failure.
 * @note Appends new line character if the string does end with one.
 */
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

/**
 * @brief Converts a linked list of strings into a single string.
 *
 * @param list The linked list of strings to concatenate.
 * @return The concatenated string.
 */
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

/**
 * @brief Ensures that the line in a linked list of strings ends with a
 *        newline character.
 *
 * @param last A pointer to the last node in the linked list.
 */
static void	ensure_eol(t_list *last)
{
	char	*temp;

	if (*(ft_strchr(last->content, '\0') - 1) != '\n')
	{
		temp = ft_strjoin(last->content, "\n");
		free(last->content);
		last->content = temp;
	}
}
