/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 19:12:08 by fsidler           #+#    #+#             */
/*   Updated: 2016/08/18 18:00:10 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			close_hook(t_mlx *mlx)
{
	ft_free_lists(mlx->light, mlx->obj);
	mlx_destroy_image(mlx->mlx, mlx->img);
	mlx_destroy_window(mlx->mlx, mlx->win);
	free(mlx->scene);
	free(mlx);
	exit(0);
	return (0);
}

static int	ft_hook_add(int keycode, t_mlx *mlx)
{
	if (mlx->selection == 1)
	{
		if (keycode == 53)
			close_hook(mlx);
		ft_parameters(keycode, mlx);
		ft_draw(mlx);
		ft_string_put(mlx);
		MSP(mlx->mlx, mlx->win, 550, 735, 0x00FEDC, mlx->pos);
		free(mlx->pos);
		(TMP->type != 4) ? free(mlx->rot) : NULL;
		return (-1);
	}
	if (keycode == 78)
	{
		mlx->cam_dir = (t_vec){mlx->cam_dir.x - 10.0 * K.x,
			mlx->cam_dir.y - 10.0 * K.y, mlx->cam_dir.z - 10.0 * K.z};
		mlx->cam_pos = (t_vec){mlx->cam_pos.x - 10.0 * K.x,
			mlx->cam_pos.y - 10.0 * K.y, mlx->cam_pos.z - 10.0 * K.z};
	}
	return (0);
}

static int	ft_translation_add(int keycode, t_mlx *mlx)
{
	if (keycode == 1)
	{
		mlx->cam_dir = (t_vec){mlx->cam_dir.x - 10.0 * J.x,
			mlx->cam_dir.y - 10.0 * J.y, mlx->cam_dir.z - 10.0 * J.z};
		mlx->cam_pos = (t_vec){mlx->cam_pos.x - 10.0 * J.x,
			mlx->cam_pos.y - 10.0 * J.y, mlx->cam_pos.z - 10.0 * J.z};
	}
	else if (keycode == 13)
	{
		mlx->cam_dir = (t_vec){mlx->cam_dir.x + 10.0 * J.x,
			mlx->cam_dir.y + 10.0 * J.y, mlx->cam_dir.z + 10.0 * J.z};
		mlx->cam_pos = (t_vec){mlx->cam_pos.x + 10.0 * J.x,
			mlx->cam_pos.y + 10.0 * J.y, mlx->cam_pos.z - 10.0 * J.z};
	}
	else if (keycode == 69)
	{
		mlx->cam_dir = (t_vec){mlx->cam_dir.x + 10.0 * K.x,
			mlx->cam_dir.y + 10.0 * K.y, mlx->cam_dir.z + 10.0 * K.z};
		mlx->cam_pos = (t_vec){mlx->cam_pos.x + 10.0 * K.x,
			mlx->cam_pos.y + 10.0 * K.y, mlx->cam_pos.z + 10.0 * K.z};
	}
	ft_pref_key(keycode, mlx);
	return (ft_draw(mlx));
}

static int	ft_translation(int keycode, t_mlx *mlx)
{
	K = ft_vectorsub(&mlx->cam_dir, &mlx->cam_pos);
	ft_vectornorm(&K);
	I = ft_vectorcross(&K, &(t_vec){0.0, 1.0, 0.0});
	ft_vectornorm(&I);
	J = ft_vectorcross(&I, &K);
	(keycode == 53) ? close_hook(mlx) : 0;
	if (keycode == 0)
	{
		mlx->cam_dir = (t_vec){mlx->cam_dir.x + 10.0 * I.x,
			mlx->cam_dir.y + 10.0 * I.y, mlx->cam_dir.z + 10.0 * I.z};
		mlx->cam_pos = (t_vec){mlx->cam_pos.x + 10.0 * I.x,
			mlx->cam_pos.y + 10.0 * I.y, mlx->cam_pos.z + 10.0 * I.z};
	}
	else if (keycode == 2)
	{
		mlx->cam_dir = (t_vec){mlx->cam_dir.x - 10.0 * I.x,
			mlx->cam_dir.y - 10.0 * I.y, mlx->cam_dir.z - 10.0 * I.z};
		mlx->cam_pos = (t_vec){mlx->cam_pos.x - 10.0 * I.x,
			mlx->cam_pos.y - 10.0 * I.y, mlx->cam_pos.z - 10.0 * I.z};
	}
	else if (keycode == 5)
		mlx->spec = (mlx->spec == 0) ? 1 : 0;
	else if (keycode == 48)
		mlx->hud = (mlx->hud == 0) ? 1 : 0;
	return (ft_translation_add(keycode, mlx));
}

int			key_hook(int keycode, t_mlx *mlx)
{
	float	tmp_pos;

	if (ft_hook_add(keycode, mlx) == -1)
		return (0);
	else if (keycode == 123 && (tmp_pos = mlx->cam_pos.x) < 20000)
	{
		POSX = mlx->cam_pos.x * cosf(0.05) + mlx->cam_pos.z * sinf(0.05);
		POSZ = tmp_pos * (-sinf(0.05)) + mlx->cam_pos.z * cosf(0.05);
	}
	else if (keycode == 124 && (tmp_pos = mlx->cam_pos.x) > -20000)
	{
		POSX = mlx->cam_pos.x * cosf(-0.05) + mlx->cam_pos.z * sinf(-0.05);
		POSZ = tmp_pos * (-sinf(-0.05)) + mlx->cam_pos.z * cosf(-0.05);
	}
	else if (keycode == 125 && (tmp_pos = mlx->cam_pos.y) > -20000)
	{
		POSY = mlx->cam_pos.y * cosf(-0.05) + mlx->cam_pos.z * (-sinf(-0.05));
		POSZ = tmp_pos * sinf(-0.05) + mlx->cam_pos.z * cosf(-0.05);
	}
	else if (keycode == 126 && (tmp_pos = mlx->cam_pos.y) < 20000)
	{
		POSY = mlx->cam_pos.y * cosf(0.05) + mlx->cam_pos.z * (-sinf(0.05));
		POSZ = tmp_pos * sinf(0.05) + mlx->cam_pos.z * cosf(0.05);
	}
	return (ft_translation(keycode, mlx));
}
