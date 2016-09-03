/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 15:55:36 by fsidler           #+#    #+#             */
/*   Updated: 2016/08/24 17:22:25 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <errno.h>
# include <pthread.h>

# define BUFF_SIZE 100

# define NB_THREAD 8

# define FOV 2.0

# define BLACK 0x000000
# define GRAY 0x686868

# define WIN_W 800
# define WIN_H 800

# define KEYPRESS (2)
# define KEYPRESSMASK (1L << 0)

# define I mlx->i
# define J mlx->j
# define K mlx->k

# define POSX mlx->cam_pos.x
# define POSY mlx->cam_pos.y
# define POSZ mlx->cam_pos.z

# define MSP mlx_string_put
# define TMP mlx->tmp

# define LAMBERT tab[3]

# define PREF1 mlx->pref == 1 && tmp2->type != 3
# define PREF2 mlx->pref == 1 && tmp->type != 3
# define COND1 mlx->spec == 1 && tmp2->type != 3
# define COND2 mlx->spec == 1 && tmp->type != 3

typedef struct		s_color
{
	float			red;
	float			green;
	float			blue;
}					t_color;

typedef struct		s_obj
{
	int				type;
	float			size;
	t_vec			rot;
	t_vec			pos;
	t_color			col;
	struct s_obj	*next;
}					t_obj;

typedef struct		s_mlx
{
	int				bpp;
	int				size_line;
	char			*d;
	int				nbl;
	int				endian;
	int				hud;
	int				selection;
	int				maxref;
	int				pref;
	int				aa;
	char			*pos;
	char			*rot;
	char			**scene;
	void			*mlx;
	void			*win;
	void			*img;
	t_vec			i;
	t_vec			j;
	t_vec			k;
	t_vec			cam_pos;
	t_vec			cam_dir;
	t_vec			ray_dir;
	t_vec			norm;
	t_vec			ref;
	t_vec			dist;
	t_vec			refpos;
	t_obj			*obj;
	t_obj			*tmp;
	t_obj			*light;
	float			spec;
	float			t0;
	float			t1;
	float			t;
	float			a;
	float			b;
	float			c;
}					t_mlx;

typedef struct		s_tab_th
{
	t_mlx			*mlx;
	int				i;
}					t_tab_th;

typedef struct		s_th
{
	int				bpp;
	int				size_line;
	char			*d;
	int				maxref;
	int				pref;
	int				cpt;
	int				ty;
	int				tx;
	int				aa;
	t_vec			i;
	t_vec			j;
	t_vec			k;
	t_vec			cam_pos;
	t_vec			cam_dir;
	t_vec			ray_dir;
	t_vec			norm;
	t_vec			ref;
	t_vec			dist;
	t_vec			refpos;
	t_obj			*obj;
	t_obj			*light;
	float			spec;
	float			t0;
	float			t1;
	float			t;
	float			a;
	float			b;
	float			c;
}					t_th;

int					ft_draw(t_mlx *mlx);
int					ft_parser(t_mlx *mlx);
int					close_hook(t_mlx *mlx);
int					ft_linelen(char *buf, int k);
int					key_hook(int keycode, t_mlx *mlx);
int					ft_pref_key(int keycode, t_mlx *mlx);
int					ft_free_lists(t_obj *lgt, t_obj *obj);
int					ft_parameters(int keycode, t_mlx *mlx);
int					ft_objects_rot(int keycode, t_mlx *mlx);
int					ft_add_light(t_mlx *mlx, int *k, int i);
int					ft_add_plane(t_mlx *mlx, int *k, int i);
int					ft_add_sphere(t_mlx *mlx, int *k, int i);
int					ft_free_arg(t_mlx *mlx, char *buf, int r);
int					ft_check_objects(t_mlx *mlx, t_obj *objects);
int					ft_mouse(int button, int x, int y, t_mlx *mlx);
int					ft_add_cyl_cone(t_mlx *mlx, int *k, int t, int i);

void				ft_hud(t_mlx *mlx);
void				ft_instructions(void);
void				ft_string_put(t_mlx *mlx);
void				ft_init_mlx_var(t_mlx *mlx);
void				ft_copy(t_mlx *mlx, t_th *th);
void				ft_put_pixel(t_th *mlx, int x, int y, int color);

double				ft_inter_cone(t_th *mlx, t_obj *node, t_vec ray,
		t_vec pos);
double				ft_inter_cylinder(t_th *mlx, t_obj *node, t_vec ray,
		t_vec pos);
double				ft_inter_plane(t_th *mlx, t_obj *node, t_vec ray,
		t_vec pos);
double				ft_inter_sphere(t_th *mlx, t_obj *node, t_vec ray,
		t_vec pos);

t_vec				ft_norm(t_th *mlx, t_obj *tmp, t_vec pos);

t_obj				*copy_obj(t_obj *obj);
t_obj				*ft_add_light_link(t_mlx *mlx, t_obj *link);
t_obj				*ft_add_object_link(t_mlx *mlx, t_obj *link);
t_obj				*ft_intersection(t_th *mlx, t_obj *node, t_vec ray,
		t_vec pos);

float				*ft_average(float *r, float *tab);
float				*ft_endlight(t_obj *tmp, t_obj *light, float *tab,
		float d);
float				*ft_lambert(t_th *mlx, t_obj *tmp, t_obj *light,
		float *tab);
float				ft_spec(t_th *mlx, t_vec dist, float d,
		float lambert);

#endif
