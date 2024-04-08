/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readfile_main.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Philip <juli@student.42london.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 23:37:10 by Philip            #+#    #+#             */
/*   Updated: 2024/04/08 20:20:09 by Philip           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	map = map_build(content);
	free(content);
	printf("Total columns: %d, total rows: %d\n", map.col_num, map.row_num);

	int i = 0;
	while (i < map.col_num * map.row_num)
	{
		printf("row: %d\tcol: %d\theight: %d\tcolor: %x\n",
			map.vertexes[i].row,
			map.vertexes[i].col,
			map.vertexes[i].height,
			map.vertexes[i].color);
		i++;
	}
	free(map.vertexes);
	return (0);
}