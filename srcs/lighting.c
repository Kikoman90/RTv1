/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lighting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 15:48:31 by fsidler           #+#    #+#             */
/*   Updated: 2016/09/07 17:27:53 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		ft_shadow(t_th *mlx, t_obj *tmp, t_obj *light, t_vec pos)
{
	t_obj	*node;
	t_vec	dist;

	node = mlx->obj;
	dist = ft_vectorsub(&light->pos, &pos);
	mlx->t = sqrtf(ft_vectordot(&dist, &dist));
	ft_vectornorm(&dist);
	while (node != NULL)
	{
		if (node != tmp)
		{
			if (node->type == 1)
				mlx->a = ft_inter_cone(mlx, node, dist, pos);
			else if (node->type == 2)
				mlx->a = ft_inter_cylinder(mlx, node, dist, pos);
			else if (node->type == 3)
				mlx->a = ft_inter_plane(mlx, node, dist, pos);
			else if (node->type == 4)
				mlx->a = ft_inter_sphere(mlx, node, dist, pos);
			if (mlx->a > 0.0001 && mlx->a < mlx->t)
				return (1);
		}
		node = node->next;
	}
	return (0);
}

static t_obj	*ft_ref_inter(t_th *mlx, t_obj *node, t_obj *tmp, t_vec pos)
{
	t_obj	*tmp2;
	double	dist;

	tmp2 = NULL;
	while (node != NULL)
	{
		if (node != tmp)
		{
			if (node->type == 1)
				dist = ft_inter_cone(mlx, node, mlx->ref, pos);
			else if (node->type == 2)
				dist = ft_inter_cylinder(mlx, node, mlx->ref, pos);
			else if (node->type == 3)
				dist = ft_inter_plane(mlx, node, mlx->ref, pos);
			else if (node->type == 4)
				dist = ft_inter_sphere(mlx, node, mlx->ref, pos);
			if (dist > 0.0001 && dist < mlx->t)
			{
				tmp2 = node;
				mlx->t = dist;
			}
		}
		node = node->next;
	}
	return (tmp2);
}

static t_obj	*ft_ref_init(t_th *mlx, t_obj *tmp, t_vec *pos)
{
	t_obj	*tmp2;

	mlx->t = 8000.0;
	mlx->ref = ft_vectorscale(&mlx->norm,
		(2 * ft_vectordot(&mlx->refpos, &mlx->norm)));
	mlx->ref = ft_vectorsub(&mlx->refpos, &mlx->ref);
	ft_vectornorm(&mlx->ref);
	tmp2 = ft_ref_inter(mlx, mlx->obj, tmp, *pos);
	if (!tmp2)
		return (NULL);
	*pos = (t_vec){pos->x + mlx->t * mlx->ref.x, pos->y +
		mlx->t * mlx->ref.y, pos->z + mlx->t * mlx->ref.z};
	mlx->refpos = (t_vec){mlx->ref.x, mlx->ref.y, mlx->ref.z};
	mlx->norm = ft_norm(mlx, tmp2, *pos);
	return (tmp2);
}

static float	*ft_reflect(t_th *mlx, t_obj *tmp, t_vec *pos, float *tab)
{
	t_obj	*tmp2;
	t_obj	*light;
	t_vec	dist;
	double	d;

	if (mlx->cpt >= mlx->maxref || (light = mlx->light) == NULL)
		return (tab);
	if ((tmp2 = ft_ref_init(mlx, tmp, pos)) == NULL || (mlx->cpt++) < 0)
		return (tab);
	while (light != NULL)
	{
		LAMBERT = 0.14;
		dist = ft_vectorsub(&light->pos, pos);
		d = ft_clamp(1.0 / sqrtf(sqrtf(ft_vectordot(&dist, &dist))), 0.0, 1.0);
		ft_vectornorm(&dist);
		if (ft_shadow(mlx, tmp2, light, *pos) == 0)
			LAMBERT += ft_clamp(ft_vectordot(&dist, &mlx->norm), 0.0, 1.0);
		tab = ft_endlight(tmp2, light, tab, d);
		tab[0] += (COND1) ? ft_spec(mlx, dist, d, tab[3]) : 0.0;
		tab[1] += (COND1) ? ft_spec(mlx, dist, d, tab[3]) : 0.0;
		tab[2] += (COND1) ? ft_spec(mlx, dist, d, tab[3]) : 0.0;
		light = light->next;
	}
	return ((PREF1) ? tab : ft_reflect(mlx, tmp2, pos, tab));
}

float			*ft_lambert(t_th *mlx, t_obj *tmp, t_obj *light, float *tab)
{
	t_vec	pos;
	t_vec	dist;
	float	d;

	pos = (t_vec){mlx->cam_pos.x + mlx->t * mlx->ray_dir.x, mlx->cam_pos.y +
		mlx->t * mlx->ray_dir.y, mlx->cam_pos.z + mlx->t * mlx->ray_dir.z};
	mlx->norm = ft_norm(mlx, tmp, pos);
	while (light != NULL)
	{
		LAMBERT = 0.15;
		dist = ft_vectorsub(&light->pos, &pos);
		d = ft_clamp((1.0 / sqrtf(sqrtf(ft_vectordot(&dist, &dist)))), 0., 1.);
		ft_vectornorm(&dist);
		if (ft_shadow(mlx, tmp, light, pos) == 0)
			LAMBERT += ft_clamp(ft_vectordot(&dist, &mlx->norm), 0.0, 1.0);
		tab = ft_endlight(tmp, light, tab, d);
		tab[0] += (COND2) ? ft_spec(mlx, dist, d, tab[3]) : 0.0;
		tab[1] += (COND2) ? ft_spec(mlx, dist, d, tab[3]) : 0.0;
		tab[2] += (COND2) ? ft_spec(mlx, dist, d, tab[3]) : 0.0;
		light = light->next;
	}
	mlx->refpos = (t_vec){mlx->ray_dir.x, mlx->ray_dir.y, mlx->ray_dir.z};
	return ((PREF2) ? tab : ft_reflect(mlx, tmp, &pos, tab));
}
