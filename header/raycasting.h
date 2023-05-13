#include <stdio.h>
#include <math.h>
#include <mlx.h>
#include <stdlib.h>
#define PI 3.14159265359

typedef struct s_vec2
{
    int x;
    int y;   
}   t_vec2;

typedef struct s_core
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *addr;
    int     bits_per_pixel;
    int     line_length;
    int     endian;
    int     width;
    int     height;
    time_t	t_init;
}   t_core;

typedef struct s_player
{
    t_vec2 pos;
    double dir;
}   t_player;

void plot_pixel(t_core *core, t_vec2 pos, int color);
void print_sky_and_floor(t_core *core);
void create_rectangle(t_core *core, t_vec2 pos, t_vec2 size, int color);
t_vec2 show_minimap(t_core *core, int map[10][10]);
void   print_player(t_core *core, t_player player);
void show_dir(t_core *core, t_player player, int map[10][10]);
void dist_horizontal(int map[10][10], t_player player, double angle, t_core *core);
t_vec2 vec2(int x, int y);