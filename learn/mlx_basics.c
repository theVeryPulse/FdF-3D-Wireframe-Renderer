#include "fdf.h"

int main(int argc, char const *argv[])
{
	t_vars	vars;

	vars.mlx_ptr = mlx_init();
	vars.win_ptr = mlx_new_window(vars.mlx_ptr, WIDTH, HEIGHT, "Hello world!");

	// Put a string in window
	// mlx_string_put(mlx_ptr, win_ptr, WIDTH / 2, HEIGHT / 2, color, "Hello World!");

	// Draw a line in window
	/* for (int i = 0; i < WIDTH; i++)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, i, HEIGHT / 2, 0x00ff00);
	} */

	// creates a new image in memory. It returns a void * identifier needed to manipulate this image later
	vars.img_vars.img_ptr = mlx_new_image(vars.mlx_ptr, WIDTH, HEIGHT);
	vars.img_vars.addr = mlx_get_data_addr(vars.img_vars.img_ptr,
		&vars.img_vars.bits_per_pixel,
		&vars.img_vars.line_size,
		&vars.img_vars.endian);

	/* Draw a rectangle */
	t_px_coord	left_top = {100, 100};
	t_px_coord	right_bottom = {WIDTH - 100, HEIGHT - 100};

	/* Slope > 1 */
	// draw_line(&vars.img_vars, (t_px_coord){0, 0}, (t_px_coord){10, 1000}, 0xFFFFFF);
	/* Slope < 0 */
	// draw_line(&vars.img_vars, (t_px_coord){0, 1000}, (t_px_coord){1000, 500}, 0xFFFFFF);

	// draw_line(&img, (t_px_coord){960, 540}, (t_px_coord){1900, 1000}, 0xFFFFFF);
	// draw_line(&img, (t_px_coord){960, 540}, (t_px_coord){900, 0}, 0xFFFFFF);

	// draw_line(&img, (t_px_coord){0, 0}, (t_px_coord){500, 500}, 0xFFFFFF);

	/* t_px_coord center = (t_px_coord){1920 / 2, 1080 / 2};
	draw_line(&img, (t_px_coord){center.x - 200, center.y}, (t_px_coord){center.x, center.y + 200}, 0xFFFFFF);
	draw_line(&img, (t_px_coord){center.x - 200, center.y}, (t_px_coord){center.x, center.y - 200}, 0xFFFFFF);
	draw_line(&img, (t_px_coord){center.x, center.y + 200}, (t_px_coord){center.x + 200, center.y}, 0xFFFFFF);
	draw_line(&img, (t_px_coord){center.x, center.y - 200}, (t_px_coord){center.x + 200, center.y}, 0xFFFFFF);
	draw_line(&img, (t_px_coord){center.x - 200, center.y}, (t_px_coord){center.x + 200, center.y}, 0xFFFFFF);
	draw_line(&img, (t_px_coord){center.x, center.y - 200}, (t_px_coord){center.x, center.y + 200}, 0xFFFFFF); */
	return 0;
}
