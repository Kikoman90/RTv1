/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/07 16:20:03 by fsidler           #+#    #+#             */
/*   Updated: 2016/08/22 19:27:27 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_put_pixel(t_th *mlx, int x, int y, int color)
{
	int				i;
	unsigned int	p;

	i = 0;
	p = x * (mlx->bpp / 8) + y * (mlx->size_line);
	while (i < (mlx->bpp / 8))
	{
		mlx->d[p + i] = color;
		color >>= 8;
		i++;
	}
}

static void	ft_set_ray(t_th *mlx, double u, double x, double y)
{
	double	v;

	u = (WIN_W - (double)x * 2.0) / WIN_H;
	v = (WIN_H - (double)y * 2.0) / WIN_W;
	K = ft_vectorsub(&mlx->cam_dir, &mlx->cam_pos);
	ft_vectornorm(&K);
	I = ft_vectorcross(&K, &(t_vec){0.0, 1.0, 0.0});
	ft_vectornorm(&I);
	J = ft_vectorcross(&I, &K);
	mlx->ray_dir = (t_vec){u * I.x + v * J.x + FOV * K.x, u * I.y + v * J.y
		+ FOV * K.y, u * I.z + v * J.z + FOV * K.z};
	ft_vectornorm(&mlx->ray_dir);
	mlx->cpt = 0;
}

static int	ft_raytrace(t_th *mlx, t_obj *node, double x, double y)
{
	t_obj	*light;
	t_obj	*tmp;
	float	*tab;
	float	res[3];
	double	p;

	light = mlx->light;
	if (!(tab = (float *)malloc(sizeof(float) * 4)))
		return (-1);
	ft_fzero(res, 3);
	p = 1.;
	while (y < mlx->t_y + 1)
	{
		x = mlx->t_x;
		while (x < mlx->t_x + 1)
		{
			ft_set_ray(mlx, 0.0, x, y);
			if ((tmp = ft_intersection(mlx, node, mlx->ray_dir, mlx->cam_pos)) != NULL)
			{
				ft_fzero(tab, 4);
				tab = ft_lambert(mlx, tmp, light, tab);
				res[0] += ft_clamp(tab[0], 0.0, 1.0);
				res[1] += ft_clamp(tab[1], 0.0, 1.0);
				res[2] += ft_clamp(tab[2], 0.0, 1.0);
			}
			p++;
			x = x + (1.0 / mlx->aa);
		}
		y = y + (1.0 / mlx->aa);
	}
	ft_put_pixel(mlx, mlx->t_x, mlx->t_y, (((int)((res[0] / p) * 255) & 0xff) << 16) +
		(((int)((res[1] / p) * 255) & 0xff) << 8) + ((int)((res[2] / p) * 255) & 0xff));
	free(tab);
	return (0);
}

void		*my_thread_process(void *arg)
{
	t_tab_th	*tab;
	t_th		*th;
	t_obj		*node;
	double		x;
	double		y;

	tab = (t_tab_th *)arg;
	node = tab->mlx->obj;
	th = (t_th *)malloc(sizeof(t_th));
	ft_copy(tab->mlx, th);
	y = 0.0;
	while (y < WIN_H)
	{
		x = WIN_W * tab->i / NB_THREAD;
		while (x < WIN_W * (tab->i + 1) / NB_THREAD)
		{
			th->t_y = (int)y;
			th->t_x = (int)x;
			ft_raytrace(th, node, x++, y);
		}
		y++;
	}
	ft_free_lists(th->light, th->obj);
	free(th);
	pthread_exit(0);
}

int			ft_draw(t_mlx *mlx)
{
	pthread_t	th[NB_THREAD];
	t_tab_th	tab[NB_THREAD];
	void		*ret;
	int			i;

	i = -1;
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_clear_window(mlx->mlx, mlx->win);
	mlx->img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	while (++i < NB_THREAD)
	{
		tab[i].i = i;
		tab[i].mlx = mlx;
		pthread_create(&th[i], NULL, my_thread_process, &tab[i]);
	}
	i = -1;
	while (++i < NB_THREAD)
		(void)pthread_join(th[i], &ret);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
	ft_hud(mlx);
	return (0);
}
