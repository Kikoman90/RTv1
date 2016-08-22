/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/17 17:19:46 by fsidler           #+#    #+#             */
/*   Updated: 2016/08/22 19:44:38 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ft_check_objects(t_mlx *mlx, t_obj *object)
{
	object = mlx->light;
	while (object != NULL)
	{
		if (!(object->col.red >= 0 && object->col.red <= 255) ||
			!(object->col.green >= 0 && object->col.green <= 255) ||
			!(object->col.blue >= 0 && object->col.blue <= 255))
			return (-1);
		object = object->next;
	}
	object = mlx->obj;
	while (object != NULL)
	{
		if (!(object->col.red >= 0 && object->col.red <= 255) ||
			!(object->col.green >= 0 && object->col.green <= 255) ||
			!(object->col.blue >= 0 && object->col.blue <= 255))
			return (-1);
		if (object->type == 2 || object->type == 4)
		{
			if (object->size < 0)
				return (-1);
		}
		object = object->next;
	}
	return (0);
}

t_vec	ft_norm(t_th *mlx, t_obj *tmp, t_vec pos)
{
	t_vec	norm;
	t_vec	temp;
	t_vec	temp2;

	if (tmp->type == 1 || tmp->type == 2)
	{
		temp = ft_vectorscale(&tmp->rot,
			(ft_vectordot(&mlx->ray_dir, &tmp->rot) * mlx->t0
			+ ft_vectordot(&mlx->dist, &tmp->rot)));
		if (tmp->type == 1)
			temp = ft_vectorscale(&temp, (1 + pow(tan(tmp->size), 2)));
		temp2 = ft_vectorsub(&pos, &tmp->pos);
		norm = ft_vectorsub(&temp2, &temp);
	}
	else if (tmp->type == 3)
		norm = tmp->rot;
	if (tmp->type == 4)
		norm = ft_vectorsub(&pos, &tmp->pos);
	ft_vectornorm(&norm);
	return (norm);
}

float	ft_spec(t_th *mlx, t_vec dist, float d, float lambert)
{
	float	spec;
	float	tmp;
	t_vec	ref;

	spec = 0.0;
	ref = ft_vectorscale(&mlx->norm, (2.0 * ft_vectordot(&mlx->norm, &dist)));
	ref = ft_vectorsub(&dist, &ref);
	if ((tmp = ft_vectordot(&ref, &mlx->ray_dir)) > 0.0 && lambert > 0.15)
	{
		spec = pow(tmp, 20.0) * 4 * d;
		spec = ft_clamp(spec, 0.0, 1.0);
	}
	return (spec);
}

int		ft_pref_key(int keycode, t_mlx *mlx)
{
	(keycode == 15 && mlx->maxref < 15) ? mlx->maxref++ : mlx->maxref;
	(keycode == 3 && mlx->maxref > 0) ? mlx->maxref-- : mlx->maxref;
	if (keycode == 14)
		mlx->pref = (mlx->pref == 0) ? 1 : 0;
	if (keycode == 7)
	{
		if (mlx->aa == 1 || mlx->aa == 2 || mlx->aa == 4 || mlx->aa == 8)
			mlx->aa *= 2;
	}
	if (keycode == 6)
	{
		if (mlx->aa == 2 || mlx->aa == 4 || mlx->aa == 8 || mlx->aa == 16)
			mlx->aa /= 2;
	}
	return (0);
}

void	ft_init_mlx_var(t_mlx *mlx)
{
	mlx->obj = NULL;
	mlx->light = NULL;
	mlx->hud = 1;
	mlx->spec = 0;
	mlx->maxref = 0;
	mlx->pref = 0;
	mlx->selection = 0;
	mlx->aa = 1;
}
