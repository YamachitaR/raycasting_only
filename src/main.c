#include "raycasting.h"

int map[10][10] = {
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 2, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 1, 1, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
	};

int close_win(t_core *core)
{
    mlx_destroy_window(core->mlx, core->win);
    exit(0);
}

int	get_key(int key, t_core *core)
{
	if (key == 65307)
		close_win(core);
	if (key == 100)
		printf("D\n");
	if (key == 97)
		printf("A\n");
	if (key == 119)
		printf("W\n");
	if (key == 115)
		printf("S\n");
}

int main (void)
{
    void *mlx;
    void *win;
    void *frame;
    t_core core;
    t_player player;

    core.mlx = mlx_init();
    core.win = mlx_new_window(core.mlx, 10 * 64, 10 * 64, "mlx 42");
    core.img = mlx_new_image(core.mlx, 10 * 64, 10 * 64);
    core.addr = mlx_get_data_addr(core.img, &core.bits_per_pixel, &core.line_length, &core.endian);
    player.pos = show_minimap(&core, map);
    print_player(&core, player);
    show_dir(&core, player, map);
    printf("player pos: %d %d\n", player.pos.x / 64, player.pos.y / 64);
    dist_horizontal(map, player, (PI / 6), &core);
    dist_vert(map, player, (PI / 6), &core);
    mlx_put_image_to_window(core.mlx, core.win, core.img, 0, 0);
    mlx_hook(core.win, 17, 0, close_win, &core);
    mlx_key_hook(core.win, &get_key, &core);
    mlx_loop(core.mlx);
}
