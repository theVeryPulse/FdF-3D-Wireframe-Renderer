#include "fdf.h"

int	round_int(double n)
{
	if (n > 0)
		return ((int)(n + 0.5));
	else
		return ((int)(n - 0.5));
}

t_matrix	matrix_multiply(t_matrix mxa, t_matrix mxb)
{
	t_matrix	product;
	int			i;
	float		entry;
	int			p_row_i;
	int			p_col_i;

	if (mxa.col_num != mxb.row_num)
		return ((t_matrix){0});
	product = (t_matrix){.row_num = mxa.row_num, .col_num = mxb.col_num};
	p_row_i = 0;
	while (p_row_i < product.row_num)
	{
		p_col_i = 0;
		entry = 0;
		while (p_col_i <product.col_num)
		{
			i = 0;
			while (i < mxa.col_num)
			{
				entry += mxa.entries[p_row_i][i] * mxb.entries[i][p_col_i];
				i++;
			}
			product.entries[p_row_i][p_col_i] = entry;
			p_col_i++;
		}
		p_row_i++;
	}
	return (product);
}

t_px_coord	xwin_coord(t_px_coord p_point)
{
	t_px_coord	result;

	result.x = p_point.x + WIDTH / 2;
	result.y = -p_point.y + HEIGHT / 2;
	ft_printf("P-system: (%d,%d), X-system: (%d,%d)\n", p_point.x, p_point.y, result.x, result.y);
	return (result);
}

t_matrix	pxcoord_to_mx(t_px_coord px_coord)
{
	t_matrix	mx;

	mx.col_num = 1;
	mx.row_num = 2;
	mx.entries[0][0] = (double)(px_coord.x);
	mx.entries[1][0] = (double)(px_coord.y);
	return (mx);
}

t_px_coord	mx_to_pxcoord(t_matrix mx)
{
	t_px_coord	px_coord;

	if (mx.col_num != 1 || mx.row_num != 2)
		return ((t_px_coord){0});
	px_coord.x = round(mx.entries[0][0]);
	px_coord.y = round(mx.entries[1][0]);
	return (px_coord);
}

int	main(int argc, char **argv)
{
	t_vars		vars;
	char		*content;
	t_map		map;
	
	content = read_file("rotation.fdf"); 
	printf("Content as one string:\n%s", content);
	map_check(content);
	printf("Map checked\n");
	map = build_map(content);
	free(content);
	printf("Total columns: %d, total rows: %d\n", map.col_num, map.row_num);

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "Hello world!");
	vars.img_vars.img_ptr = mlx_new_image(vars.mlx_ptr, WIDTH, HEIGHT);
	vars.img_vars.addr = mlx_get_data_addr(vars.img_vars.img_ptr,
		&vars.img_vars.bits_per_pixel,
		&vars.img_vars.line_size,
		&vars.img_vars.endian);

	double angle = 1 * PI / 180;
	t_matrix rotation = (t_matrix){.row_num = 2, .col_num = 2,
		.entries = {
			{cos(angle), -sin(angle)},
			{sin(angle), cos(angle)}
		}
	};
	t_px_coord	needle = (t_px_coord){.x = 0, .y = 200};
	
	// TODO draw_line cannot draw between 45degrees and 90 degrees, 225degrees and 270 degrees
	draw_line(&vars.img_vars, xwin_coord((t_px_coord){0}), xwin_coord((t_px_coord){200, 300}), WHITE);
	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);


	/* for (int count = 0; count < 360; count++)
	{
		draw_line(&vars.img_vars, xwin_coord((t_px_coord){0}), xwin_coord(needle), WHITE);
		needle = mx_to_pxcoord(matrix_multiply(rotation, pxcoord_to_mx(needle)));
		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
	} */

	/* t_px_coord	a_p = (t_px_coord){.x = -200, .y = 200};
	t_px_coord	b_p = (t_px_coord){.x = 200, .y = 200};
	t_px_coord	c_p = (t_px_coord){.x = 200, .y = -200};
	t_px_coord	d_p = (t_px_coord){.x = -200, .y = -200};
	while (1)
	{
		sleep(1);
		a_p = mx_to_pxcoord(matrix_multiply(rotation, pxcoord_to_mx(a_p)));
		b_p = mx_to_pxcoord(matrix_multiply(rotation, pxcoord_to_mx(b_p)));
		c_p = mx_to_pxcoord(matrix_multiply(rotation, pxcoord_to_mx(c_p)));
		d_p = mx_to_pxcoord(matrix_multiply(rotation, pxcoord_to_mx(d_p)));
		fill_image_with_color(&vars.img_vars, BLACK);
		draw_line(&vars.img_vars, xwin_coord(a_p), xwin_coord(b_p), WHITE);
		draw_line(&vars.img_vars, xwin_coord(b_p), xwin_coord(c_p), WHITE);
		draw_line(&vars.img_vars, xwin_coord(c_p), xwin_coord(d_p), WHITE);
		draw_line(&vars.img_vars, xwin_coord(d_p), xwin_coord(a_p), WHITE);
		mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);
	} */


	mlx_put_image_to_window(vars.mlx_ptr, vars.win_ptr, vars.img_vars.img_ptr, 0, 0);


	mlx_loop(vars.mlx_ptr);
}
