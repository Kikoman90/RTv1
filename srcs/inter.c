/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inter.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 17:08:09 by fsidler           #+#    #+#             */
/*   Updated: 2016/06/09 15:40:40 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double	ft_inter_sphere(t_th *mlx, t_obj *tmp, t_vec ray, t_vec pos)
{
	double disc;

	mlx->dist = ft_vectorsub(&pos, &tmp->pos);
	mlx->a = ft_vectordot(&ray, &ray);
	mlx->b = 2 * ft_vectordot(&ray, &mlx->dist);
	mlx->c = ft_vectordot(&mlx->dist, &mlx->dist) - (tmp->size * tmp->size);
	disc = mlx->b * mlx->b - 4 * mlx->a * mlx->c;
	if (disc < 0)
		return (-1);
	mlx->t0 = (-mlx->b + sqrtf(disc)) / (2 * mlx->a);
	mlx->t1 = (-mlx->b - sqrtf(disc)) / (2 * mlx->a);
	if (mlx->t0 > mlx->t1)
		mlx->t0 = mlx->t1;
	return (mlx->t0);
}

double	ft_inter_cylinder(t_th *mlx, t_obj *tmp, t_vec ray, t_vec pos)
{
	double disc;

	mlx->dist = ft_vectorsub(&pos, &tmp->pos);
	ft_vectornorm(&tmp->rot);
	mlx->a = ft_vectordot(&ray, &ray) - pow(ft_vectordot(&ray, &tmp->rot), 2);
	mlx->b = 2 * (ft_vectordot(&ray, &mlx->dist) -
		(ft_vectordot(&ray, &tmp->rot) * ft_vectordot(&mlx->dist, &tmp->rot)));
	mlx->c = ft_vectordot(&mlx->dist, &mlx->dist) -
		pow(ft_vectordot(&mlx->dist, &tmp->rot), 2) - pow(tmp->size, 2);
	disc = mlx->b * mlx->b - 4 * mlx->a * mlx->c;
	if (disc < 0)
		return (-1);
	mlx->t0 = (-mlx->b + sqrtf(disc)) / (2 * mlx->a);
	mlx->t1 = (-mlx->b - sqrtf(disc)) / (2 * mlx->a);
	if (mlx->t0 > mlx->t1)
		mlx->t0 = mlx->t1;
	return (mlx->t0);
}

double	ft_inter_cone(t_th *mlx, t_obj *tmp, t_vec ray, t_vec pos)
{
	double	disc;

	mlx->dist = ft_vectorsub(&pos, &tmp->pos);
	ft_vectornorm(&tmp->rot);
	mlx->a = ft_vectordot(&ray, &ray) - (1 + pow(tan(tmp->size), 2)) *
		pow(ft_vectordot(&ray, &tmp->rot), 2);
	mlx->b = 2 * (ft_vectordot(&ray, &mlx->dist) - (1 + pow(tan(tmp->size), 2))
		* ft_vectordot(&ray, &tmp->rot) * ft_vectordot(&mlx->dist, &tmp->rot));
	mlx->c = ft_vectordot(&mlx->dist, &mlx->dist) - (1 +
		pow(tan(tmp->size), 2)) * pow(ft_vectordot(&mlx->dist, &tmp->rot), 2);
	disc = mlx->b * mlx->b - 4 * mlx->a * mlx->c;
	if (disc < 0)
		return (-1);
	mlx->t0 = (-mlx->b + sqrtf(disc)) / (2 * mlx->a);
	mlx->t1 = (-mlx->b - sqrtf(disc)) / (2 * mlx->a);
	if (mlx->t0 > mlx->t1)
		mlx->t0 = mlx->t1;
	return (mlx->t0);
}

double	ft_inter_plane(t_th *mlx, t_obj *tmp, t_vec ray, t_vec pos)
{
	mlx->t0 = ((ft_vectordot(&tmp->rot, &tmp->pos) -
				ft_vectordot(&tmp->rot, &pos)) / ft_vectordot(&tmp->rot, &ray));
	if (mlx->t0 < 0.0001)
		return (-1);
	return (mlx->t0);
}

t_obj	*ft_intersection(t_th *mlx, t_obj *node, t_vec ray, t_vec pos)
{
	t_obj	*tmp;
	double	dist;

	tmp = NULL;
	mlx->t = 80000.0;
	while (node != NULL)
	{
		if (node->type == 1)
			dist = ft_inter_cone(mlx, node, ray, pos);
		else if (node->type == 2)
			dist = ft_inter_cylinder(mlx, node, ray, pos);
		else if (node->type == 3)
			dist = ft_inter_plane(mlx, node, ray, pos);
		else if (node->type == 4)
			dist = ft_inter_sphere(mlx, node, ray, pos);
		if (dist > 0.0001 && dist < mlx->t)
		{
			tmp = node;
			mlx->t = dist;
		}
		node = node->next;
	}
	return (tmp);
}
