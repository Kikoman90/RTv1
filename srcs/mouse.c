/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 18:39:06 by fsidler           #+#    #+#             */
/*   Updated: 2016/08/17 16:05:02 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int				ft_parameters(int keycode, t_mlx *mlx)
{
	if (keycode == 36 && (mlx->selection = 0) > -1)
		return (0);
	else if (keycode == 24 && TMP->type != 3)
		TMP->size = (TMP->size < 10000) ? TMP->size + 5 : TMP->size;
	else if (keycode == 27 && TMP->type != 3)
		TMP->size = (TMP->size > 6) ? TMP->size - 5 : TMP->size;
	else if (keycode == 0)
		TMP->pos = (t_vec){TMP->pos.x + 10.0 * I.x,
			TMP->pos.y + 10.0 * I.y, TMP->pos.z + 10.0 * I.z};
	else if (keycode == 2)
		TMP->pos = (t_vec){TMP->pos.x - 10.0 * I.x,
			TMP->pos.y - 10.0 * I.y, TMP->pos.z - 10.0 * I.z};
	else if (keycode == 13)
		TMP->pos = (t_vec){TMP->pos.x + 10.0 * J.x,
			TMP->pos.y + 10.0 * J.y, TMP->pos.z + 10.0 * J.z};
	else if (keycode == 1)
		TMP->pos = (t_vec){TMP->pos.x - 10.0 * J.x,
			TMP->pos.y - 10.0 * J.y, TMP->pos.z - 10.0 * J.z};
	else if (keycode == 69)
		TMP->pos = (t_vec){TMP->pos.x - 10.0 * K.x,
			TMP->pos.y - 10.0 * K.y, TMP->pos.z - 10.0 * K.z};
	else if (keycode == 78)
		TMP->pos = (t_vec){TMP->pos.x + 10.0 * K.x,
			TMP->pos.y + 10.0 * K.y, TMP->pos.z + 10.0 * K.z};
	return (ft_objects_rot(keycode, mlx));
}

static void		ft_tmp_string(t_mlx *mlx)
{
	mlx->pos = ft_strjoin("pos: ", (
	ft_strjoin(ft_itoa(TMP->pos.x), (
	ft_strjoin(" ", (
	ft_strjoin(ft_itoa(TMP->pos.y), (
	ft_strjoin(" ", ft_itoa(TMP->pos.z), 'R')), 'B')), 'R')), 'B')), 'R');
	if (TMP->type != 4)
	{
		mlx->rot = ft_strjoin("rot: ", (
		ft_strjoin(ft_ftoa(TMP->rot.x), (
		ft_strjoin(" ", (
		ft_strjoin(ft_ftoa(TMP->rot.y), (
		ft_strjoin(" ", ft_ftoa(TMP->rot.z), 'R')), 'B')), 'R')), 'B')), 'R');
	}
}

static t_obj	*ft_seek(double u, double v, t_vec vpos, t_mlx *mlx)
{
	t_obj	*tmp;
	t_th	*th;

	if (!(th = (t_th *)malloc(sizeof(t_th))))
		return (NULL);
	tmp = mlx->obj;
	K = ft_vectorsub(&mlx->cam_dir, &vpos);
	ft_vectornorm(&K);
	I = ft_vectorcross(&K, &(t_vec){0.0, 1.0, 0.0});
	ft_vectornorm(&I);
	J = ft_vectorcross(&I, &K);
	mlx->ray_dir = (t_vec){u * I.x + v * J.x + FOV * K.x, u * I.y + v * J.y
		+ FOV * K.y, u * I.z + v * J.z + FOV * K.z};
	ft_vectornorm(&mlx->ray_dir);
	tmp = ft_intersection(th, tmp, mlx->ray_dir, vpos);
	free(th);
	return (tmp);
}

void			ft_string_put(t_mlx *mlx)
{
	char	*s;

	s = (TMP->type != 3) ? ft_strjoin("size: ", ft_itoa(TMP->size), 'R') : NULL;
	ft_tmp_string(mlx);
	if (TMP->type == 1 || TMP->type == 2)
	{
		if (TMP->type == 1)
			MSP(mlx->mlx, mlx->win, 550, 720, 0x00FEDC, "object: cone");
		if (TMP->type == 2)
			MSP(mlx->mlx, mlx->win, 550, 720, 0x00FEDC, "object: cylinder");
		MSP(mlx->mlx, mlx->win, 550, 750, 0x00FEDC, mlx->rot);
		MSP(mlx->mlx, mlx->win, 550, 765, 0x00FEDC, s);
	}
	else if (TMP->type == 3)
	{
		MSP(mlx->mlx, mlx->win, 550, 720, 0x00FEDC, "object: plane");
		MSP(mlx->mlx, mlx->win, 550, 750, 0x00FEDC, mlx->rot);
	}
	else if (TMP->type == 4)
	{
		MSP(mlx->mlx, mlx->win, 550, 720, 0x00FEDC, "object: sphere");
		MSP(mlx->mlx, mlx->win, 550, 765, 0x00FEDC, s);
	}
	(TMP->type != 3) ? free(s) : NULL;
}

int				ft_mouse(int button, int x, int y, t_mlx *mlx)
{
	double	u;
	double	v;

	u = (WIN_W - (double)x * 2.0) / WIN_H;
	v = (WIN_H - (double)y * 2.0) / WIN_W;
	if (button == 1 && (x >= 0 && x <= WIN_W) && (y >= 0 && y <= WIN_H))
	{
		mlx_clear_window(mlx->mlx, mlx->win);
		mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
		ft_hud(mlx);
		if ((mlx->tmp = ft_seek(u, v, (t_vec){mlx->cam_pos.x + u,
			mlx->cam_pos.y + v, mlx->cam_pos.z}, mlx)) == NULL)
		{
			MSP(mlx->mlx, mlx->win, 550, 720, 0x00FEDC, "no selection");
			mlx->selection = 0;
			return (0);
		}
		ft_string_put(mlx);
		MSP(mlx->mlx, mlx->win, 550, 735, 0x00FEDC, mlx->pos);
		free(mlx->pos);
		(TMP->type != 4) ? free(mlx->rot) : NULL;
		mlx->selection = 1;
	}
	return (0);
}
