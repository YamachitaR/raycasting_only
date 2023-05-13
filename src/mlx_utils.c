#include "raycasting.h"

void plot_pixel(t_core *core, t_vec2 pos, int color)
{
    char    *pixel;

    pixel = core->addr + (pos.y * core->line_length + pos.x * (core->bits_per_pixel / 8)); 
    *(unsigned int *)pixel = color;
}

void print_sky_and_floor(t_core *core)
{
    create_rectangle(core, (t_vec2){0, 0}, (t_vec2){500, 160}, 0x0000FF);
    create_rectangle(core, (t_vec2){0, 160}, (t_vec2){500, 160}, 0x808080);
}

t_vec2 show_minimap(t_core *core, int map[10][10])
{
    t_vec2 i;
    t_vec2 player_pos;

    i.y = 0;
    i.x = 0;
    
    while (i.y < 10)
    {
        i.x = 0;
        while (i.x < 10)
        {
            if (map[i.y][i.x] == 1)
                create_rectangle(core, vec2(i.x * 64, i.y * 64), vec2(63, 63), 0x0000FF);
            else
                create_rectangle(core, vec2(i.x * 64, i.y * 64), vec2(63, 63), 0x00FF00);
            if (map[i.y][i.x] == 2)
                player_pos = vec2(i.x * 64, i.y * 64);
            i.x++;
        }
        i.y++;
    }
    return (player_pos);
}

void   print_player(t_core *core, t_player player)
{
    create_rectangle(core, player.pos, vec2(30, 30), 0xFF0000);   
}

void show_dir(t_core *core, t_player player, int map[10][10])
{
    t_vec2 dir;

    dir.x = player.pos.x + 15;
    dir.y = player.pos.y;

    while (map[dir.y / 64][dir.x / 64] != 1)
    {
        plot_pixel(core, dir, 0xFF0000);
        dir.y--;
    }
}


int is_wall(double ay, double ax, int map[10][10])
{
    if (ay / 64 < 0 || ax / 64 < 0 || ay / 64 > 9 || ax / 64 > 9)
        return (1);
    if (map[(int)ay / 64][(int)ax / 64] == 1)
        return (1);
    return (0);
}

void dist_horizontal(int map[10][10], t_player player, double angle, t_core *core)
{
    double ay;
    double ax;
    double ya;
    double xa;

    if (sin(angle) > 0)
    {
        ay = floor(player.pos.y / 64) * 64 - 0.0001;
        ax = player.pos.x + (player.pos.y - ay) / tan(angle);
        ya = -64;
        xa = - 64 / tan(angle);
        while (is_wall(ay, ax, map) != 1)
        {
            ay += ya;
            ax += xa;
        }
        printf("ay = %f, ax = %f\n", ay / 64, ax / 64);
        plot_pixel(core, vec2(ax, ay), 0xFF0000);
    }
    else
    {

        ay = floor(player.pos.y / 64) * 64 + 64;
        ax = player.pos.x + (player.pos.y - ay) / tan(angle);
        ya = 64;
        xa = 64 / tan(angle);
        while (is_wall(ay, ax, map) != 1)
        {
            ay += ya;
            ax += xa;
        }
        printf("ay = %f, ax = %f\n", ay / 64, ax / 64);
        plot_pixel(core, vec2(ax, ay), 0xFF0000);
    }
}

void dist_vert(int map[10][10], t_player player, double angle, t_core *core)
{
    double bx;
    double by;
    double xa;
    double ya;

    if (cos(angle) > 0)
    {
        bx = floor(player.pos.x / 64) * 64;
        by = -64 * tan(angle);
        ya = player.pos.y + (player.pos.x - bx) * tan(angle);
        xa = 64;
        while (is_wall(by, bx, map) != 1)
        {
            by += ya;
            bx += xa;
        }
        printf("by = %f, bx = %f\n", by / 64, bx / 64);
        plot_pixel(core, vec2(bx, by), 0xFF0F00);
    }
    else
    {
        bx = floor(player.pos.x / 64) * 64 - 0.0001;
        by = 64 * tan(angle);
        ya = player.pos.y + (player.pos.x - bx) * tan(angle);
        xa = -64;
        while (is_wall(by, bx, map) != 1)
        {
            by += ya;
            bx += xa;
        }
        printf("by = %f, bx = %f\n", by / 64, bx / 64);
        plot_pixel(core, vec2(bx, by), 0xFF0F00);
    }
}

t_vec2 vec2(int x, int y)
{
    t_vec2 vec;

    vec.x = x;
    vec.y = y;
    return (vec);
}

void create_rectangle(t_core *core, t_vec2 pos, t_vec2 size, int color)
{
    t_vec2  i;

    i.y = 0;
    while (i.y < size.y)
    {
        i.x = 0;
        while (i.x < size.x)
        {
            plot_pixel(core, (t_vec2){pos.x + i.x, pos.y + i.y}, color);
            i.x++;
        }
        i.y++;
    }
}