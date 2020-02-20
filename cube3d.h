/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moboustt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 01:10:12 by moboustt          #+#    #+#             */
/*   Updated: 2020/02/02 18:43:11 by moboustt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <mlx.h>
# include <fcntl.h>

# define PI 3.14159265359
# define TWO_PI (2 * PI)

# define TRUE 1
# define FALSE 0
# define MINI 0.3

# define SQUARE_SIZE 64
# define NUM_ROWS 14
# define NUM_COLS 29
# define TEX_WIDTH 64
# define TEX_HEIGHT 64

# define WINDOW_WIDTH (NUM_COLS * SQUARE_SIZE)
# define WINDOW_HEIGHT (NUM_ROWS * SQUARE_SIZE)

# define NUM_RAYS (WINDOW_WIDTH)
# define FOV_ANGLE (60 * (PI / 180))

# define MAX_INT 2147483647
# define BUFFER_SIZE 90

typedef struct		s_ray
{
	float			ray_angle;
	float			wall_h_x;
	float			wall_h_y;
	float			distance;
	int				wall_h_vert;
	int				is_ray_facing_up;
	int				is_ray_facing_down;
	int				is_ray_facing_right;
	int				is_ray_facing_left;
	int				wall_h_content;
	int				was_hit_vertical;
}					t_ray[NUM_RAYS];

t_ray				rays[NUM_RAYS];
uint32_t			buff[TEX_WIDTH * TEX_HEIGHT + 1];

typedef struct		s_struct
{
	int				bpp;
	int				size_line;
	int				endian;
	int				bpp_text;
	int				size_line_text;
	int				endian_text;
	int				*img_data_texture;
	void			*xpm_ptr;
	void			*mlx_ptr;
	void			*img_ptr;
	void			*win_ptr;
	char			*img_data;
	float			move_step;
	float			updated_player_x;
	float			updated_player_y;
	float			x;
	float			y;
	float			radius;
	float			width;
	float			height;
	int				turn_direction;
	int				walk_direction;
	float			rotation_angle;
	float			walk_speed;
	float			turn_speed;

	float			dx;
	float			dy;
	float			ray_angle;
	float			x_intercept;
	float			y_intercept;
	float			save_horiz_wall_hit_x;
	float			save_horiz_wall_hit_y;
	float			save_vert_wall_hit_x;
	float			save_vert_wall_hit_y;
	int				found_horiz_wall_hit;
	int				found_vert_wall_hit;
	int				vert_wall_hit_content;
	float			horz_hit_distance;
	float			vert_hit_distance;
	int				is_ray_facing_down;
	int				is_ray_facing_up;
	int				is_ray_facing_right;
	int				is_ray_facing_left;

	float			corrected_dsitance;
	float			top_pixel;
	float			bottom_pixel;
	float			distance_to_projection_plane;
	float			wall_height;
	int				i_wall_index;
	int				txt_offset_x;
	int				txt_offset_y;

	float			vert_touch_x;
	float			vert_touch_y;
	float			horiz_touch_x;
	float			horiz_touch_y;

	int				steps;
	float			x_inc;
	float			y_inc;

	int was_touching_sprite;
	int which_radius;
	
}					t_struct;
typedef struct	s_struc
{
	int			fd;
	char		*line;
	signed int	width;
	signed int	height;
	signed int	f_red;
	signed int	f_green;
	signed int	f_blue;
	signed int	c_red;
	signed int	c_green;
	signed int	c_blue;
	char *path_to_the_north_texture;
	char *path_to_the_south_texture;
	char *path_to_the_west_texture;
	char *path_to_the_east_texture;
}				t_read;

int		get_next_line(int fd, char **line);
void	free_d_shit(char **to_free);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(const char *s1);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *s);
int		gnl_get_index(char *stack);
void	gnl_verify_line(char **line, char **stack, char **heap);
int		gnl_read_line(char **line, char **stack, char **heap, int byte, int fd);
int		ft_atoi(const char *s);
char	**ft_split(const char *ss, char c);
void	render_player(t_struct *data);
void	initialize_1(t_struct *data);
void	initialize_2(t_struct *data);
int		render_map(t_struct *data);
void	fill_square(int square_x, int square_y, int tile_size,
int square_color, t_struct *data);
int		key_hook(int keycode, void *param);
int		initialize_window(t_struct *data);
int		move_player(t_struct *data);
void	circle(t_struct *data);
void	draw_line(t_struct *data);
void	ft_draw(t_struct *data, int x, int y, int color);
int		if_wall(float x, float y);
void	line(t_struct *data, int x0, int y0, int x1, int y1);
void	ft_draw_texture(t_struct *data, int x, int y, int color);
float	limit_angle(float angle);
float	distance_between_points(float x1, float y1, float x2, float y2);
void	horizontal_ray_intersection(float ray_angle, t_struct *data,
int *found_horiz_wall_hit, int *horz_wall_content);
void	vertical_ray_intersection(float ray_angle, t_struct *data,
int *found_vert_wall_hit, int *vert_wall_content);
void	get_smalest_distance(t_struct *data, int found_horiz_wall_hit,
int found_vert_wall_hit);
void	cast_single_ray(int ray_id, float ray_angle, t_struct *data);
void	fill_out_ray(int ray_id, t_struct *data, int vert_wall_content,
int horz_wall_content);
void	render_all_rays(t_struct *data);
void	cast_rays(t_struct *data);
void	render_firt_time(t_struct *data);
void	mini_map(t_struct *data);
int		update(t_struct *data, uint32_t *buff);
int		ft_close(void *param);
int		key_pressed(int keycode, t_struct *data);
int		key_released(int keycode, t_struct *data);
void	texture_from_file(t_struct *data);
void	texture(t_struct *data);
void	render_walls(t_struct *data);
void	calculate_vert_ray_intercept(t_struct *data, float ray_angle);
void	calculate_horz_ray_intercept(t_struct *data, float ray_angle);

#endif
