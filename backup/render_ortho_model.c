// #include "fdf.h"

// void	render_ortho_model(t_vars *vars)
// {
// 	int	i;
// 	int	j;

// 	i = 0;
// 	while (i < vars->map.row_num)
// 	{
// 		j = 0;
// 		while (j < vars->map.col_num)
// 		{
// 			if (j != vars->map.col_num - 1)
// 			{
// 				draw_line(&vars->img_vars,
// 					raster_coord(ortho_screen_coord(vars->map.vertexes[j + i * vars->map.col_num].real_coord)),
// 					raster_coord(ortho_screen_coord(vars->map.vertexes[j + 1 + i * vars->map.col_num].real_coord)),
// 					WHITE);
// 			}
// 			if (i != vars->map.row_num - 1)
// 			{
// 				draw_line(&vars->img_vars,
// 					raster_coord(ortho_screen_coord(vars->map.vertexes[j + i * vars->map.col_num].real_coord)),
// 					raster_coord(ortho_screen_coord(vars->map.vertexes[j + (i + 1) * vars->map.col_num].real_coord)),
// 					WHITE);
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// }