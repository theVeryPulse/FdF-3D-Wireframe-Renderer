/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 19:35:00 by Philip            #+#    #+#             */
/*   Updated: 2024/01/30 22:56:35 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static char	*list_to_str(t_list *list);
static void	list_free(t_list **list);

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
		if (line)
			ft_lstadd_back(&list, ft_lstnew(line));
		else
			break ;
	}
	all = list_to_str(list);
	list_free(&list);
	return (all);
}

static void	list_free(t_list **list)
{
	t_list	*this;
	t_list	*next;

	if (!list || !(*list))
		return ;
	this = *list;
	next = this->next;
	while (this)
	{
		next = this->next;
		free(this->content);
		free(this);
		this = next;
	}
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
		len += ft_strlen(list->content);
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

void	map_check(char *map)
{
	size_t	i;

	if (!map)
		exit(1);
	i = 0;
	while (map[i] && (ft_isspace(map[i]) || ft_isalnum(map[i])))
	{
		i++;
	}
	if (map[i] != '\0')
	{
		free(map);
		exit(1);
	}
}

int	hexa_to_int(const char *src)
{
	size_t		i;
	int			n;
	const char	*lower = "0123456789abcdef";
	char		*s;

	s = ft_strdup(src);
	n = 0;
	i = 2;
	while (s[i])
	{
		if (ft_isupper(s[i]))
			s[i] = ft_tolower(s[i]);
		i++;
	}
	i = 2;
	while (ft_strchr(lower, s[i]))
	{
		n *= 16;
		n += (int)(ft_strchr(lower, s[i]) - lower);
	}
	free(s);
	return (n);
}

void	fill_points(t_map *map, char *str)
{
	size_t	i;
	size_t	pt_i;
	int		this_col;
	int		this_row;

	i = 0;
	pt_i = 0;
	this_col = 1;
	this_row = 1;
	while (str[i])
	{
		if (ft_isdigit(str[i]))
		{
			map->points[pt_i].height = ft_atoi(&str[i]);
			map->points[pt_i].col = this_col;
			map->points[pt_i].row = this_row;
			while (ft_isdigit(str[i]))
				i++;
			if (str[i] == ',')
			{
				map->points[pt_i].color = hexa_to_int(&str[i + 1]);
			}
			while (ft_isalnum(str[i]))
				i++;
			pt_i++;
			this_col++;
		}
		if (str[i] == '\n')
		{
			this_row++;
			this_col = 1;
		}
		i++;
	}
}

t_map	build_map(char *str)
{
	t_map	map;
	size_t	i;

	map.col_num = 1;
	map.row_num = 0;
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] == ' ')
			map.col_num++;
		while (str[i] == ' ')
			i++;
		i++;
	}
	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			map.row_num++;
		i++;
	}
	map.points = (t_point *)ft_calloc(map.col_num * map.row_num, sizeof(t_point));
	if (!map.points)
	{
		free(str);
		exit(1);
	}
	fill_points(&map, str);
	return (map);
}

int	main(int argc, char const *argv[])
{
	char	*content;
	t_map	map;

	if (argc != 2)
		return (1);
	content = read_file(argv[1]);
	printf("Content as one string:\n%s", content);
	map_check(content);
	printf("Map checked\n");
	map = build_map(content);
	free(content);
	printf("Total columns: %d, total rows: %d\n", map.col_num, map.row_num);

	int i = 0;
	while (i < map.col_num * map.row_num)
	{
		printf("row: %d\tcol: %d\theight: %d\tcolor: %x\n",
			map.points[i].row,
			map.points[i].col,
			map.points[i].height,
			map.points[i].color);
		i++;
	}
	return (0);
}
