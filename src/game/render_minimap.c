#include "cub3d.h"

static void init_minimap_vars(t_minimap *vars, t_ctx *ctx)
{
    vars->view_range = 8;
    vars->player_map_x = (int)(ctx->maths.px / MAP_S);
    vars->player_map_y = (int)(ctx->maths.py / MAP_S);
    vars->start_x = vars->player_map_x - vars->view_range;
    vars->start_y = vars->player_map_y - vars->view_range;
    vars->minimap_x = 20;
    vars->minimap_y = 20;
}

static void draw_minimap_border(t_ctx *ctx, t_minimap *vars)
{
    t_rsquare border = init_rsquare_vars(
        vars->minimap_y - 2,
        vars->minimap_x - 2,
        (vars->view_range * 2 + 1) * 16 + 4
    );
    render_square(ctx, border, 0x444444FF);
}

static void draw_minimap_walls(t_ctx *ctx, t_minimap *vars)
{
    int x = vars->start_x;
    int y = vars->start_y;

    while (y < vars->player_map_y + vars->view_range + 1)
    {
        x = vars->start_x;
        while (x < vars->player_map_x + vars->view_range + 1)
        {
            if (x >= 0 && x < ctx->ginfo.map_width && 
                y >= 0 && y < ctx->ginfo.map_height && 
                ctx->ginfo.map[y][x] == '1')
            {
                int rel_x = (x - vars->start_x) * 16;
                int rel_y = (y - vars->start_y) * 16;
                t_rsquare square = init_rsquare_vars(
                    vars->minimap_y + rel_y,
                    vars->minimap_x + rel_x,
                    16
                );
                render_square(ctx, square, 0xFF0000FF);
            }
            x++;
        }
        y++;
    }
}

static void draw_player(t_ctx *ctx, t_minimap *vars)
{
    float map_pos_x = ctx->maths.px / MAP_S;
    float map_pos_y = ctx->maths.py / MAP_S;
    float rel_player_x = (map_pos_x - (float)vars->start_x) * 16;
    float rel_player_y = (map_pos_y - (float)vars->start_y) * 16;
    
    t_rsquare player = init_rsquare_vars(
        vars->minimap_y + rel_player_y - 4,
        vars->minimap_x + rel_player_x - 4,
        8
    );
    render_square(ctx, player, 0xFFFFFFFF);
    vars->center_x = vars->minimap_x + rel_player_x;
    vars->center_y = vars->minimap_y + rel_player_y;
}

static bool check_ray_collision(t_ctx *ctx, t_minimap *vars, float ray_x, float ray_y)
{
    float check_points[4][2] = {
        {ray_x - 0.1f, ray_y - 0.1f},
        {ray_x + 0.1f, ray_y - 0.1f},
        {ray_x - 0.1f, ray_y + 0.1f},
        {ray_x + 0.1f, ray_y + 0.1f}
    };

    int i = 0;
    while (i < 4)
    {
        int map_x = (int)((check_points[i][0] - vars->minimap_x) / 16 + vars->start_x);
        int map_y = (int)((check_points[i][1] - vars->minimap_y) / 16 + vars->start_y);

        if (map_x >= 0 && map_x < ctx->ginfo.map_width &&
            map_y >= 0 && map_y < ctx->ginfo.map_height &&
            (ctx->ginfo.map[map_y][map_x] == '1' || ctx->ginfo.map[map_y][map_x] == 'C'))
        {
            float cell_x = (check_points[i][0] - vars->minimap_x) - ((map_x - vars->start_x) * 16);
            float cell_y = (check_points[i][1] - vars->minimap_y) - ((map_y - vars->start_y) * 16);

            if (cell_x >= -0.1f && cell_x <= 16.1f &&
                cell_y >= -0.1f && cell_y <= 16.1f)
                return (true);
        }
        i++;
    }
    return (false);
}

static void cast_single_ray(t_ctx *ctx, t_minimap *vars, float angle)
{
    float ray_x = vars->center_x;
    float ray_y = vars->center_y;
    float dx = cosf(angle) * 0.2f;
    float dy = sinf(angle) * 0.2f;
    float dist = 0;
    float ray_length = 10 * vars->view_range;

    while (dist < ray_length)
    {
        if (check_ray_collision(ctx, vars, ray_x, ray_y))
            break;
        safe_put_pixel(ctx->winfo.img, (int)ray_x, (int)ray_y, 0x00FF00FF);
        ray_x += dx;
        ray_y += dy;
        dist += 0.2f;
    }
}

static void cast_all_rays(t_ctx *ctx, t_minimap *vars)
{
    int i = -32;
    float angle_step = M_PI / 4 / 32;
    
    while (i < 32)
    {
        float ray_angle = ctx->maths.pa + (i * angle_step);
        cast_single_ray(ctx, vars, ray_angle);
        i++;
    }
}

void draw_minimap(t_ctx *ctx)
{
    t_minimap vars;
    
    init_minimap_vars(&vars, ctx);
    draw_minimap_border(ctx, &vars);
    draw_minimap_walls(ctx, &vars);
    draw_player(ctx, &vars);
    cast_all_rays(ctx, &vars);
}