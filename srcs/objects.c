/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/08 18:54:09 by fsidler           #+#    #+#             */
/*   Updated: 2016/06/21 18:42:50 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int	ft_col_n_pos(t_mlx *mlx, t_obj *link, int k)
{
	int	i;

	i = 6;
	if (ft_strncmp(mlx->scene[k + 2], "		col(", 6) != 0 || \
			ft_strncmp(mlx->scene[k + 3], "		pos(", 6) != 0)
		return (-1);
	link->col.red = ft_atoi(mlx->scene[k + 2], &i);
	link->col.green = ft_atoi(mlx->scene[k + 2], &i);
	link->col.blue = ft_atoi(mlx->scene[k + 2], &i);
	if (mlx->scene[k + 2][i] != ')')
		return (-1);
	i = 6;
	link->pos.x = ft_atoi(mlx->scene[k + 3], &i);
	link->pos.y = ft_atoi(mlx->scene[k + 3], &i);
	link->pos.z = ft_atoi(mlx->scene[k + 3], &i);
	if (mlx->scene[k + 3][i] != ')')
		return (-1);
	return (0);
}

int			ft_add_light(t_mlx *mlx, int *k, int i)
{
	t_obj	*link;

	if (!(link = (t_obj *)malloc(sizeof(t_obj))))
		return (-1);
	if (ft_strcmp(mlx->scene[*k + 1], "	{") != 0 || \
			ft_strcmp(mlx->scene[*k + 4], "	}") != 0)
		return (-1);
	if (ft_strncmp(mlx->scene[*k + 2], "		col(", 6) != 0 || \
			ft_strncmp(mlx->scene[*k + 3], "		pos(", 6) != 0)
		return (-1);
	link->col.red = ft_atoi(mlx->scene[*k + 2], &i);
	link->col.green = ft_atoi(mlx->scene[*k + 2], &i);
	link->col.blue = ft_atoi(mlx->scene[*k + 2], &i);
	if (mlx->scene[*k + 2][i] != ')')
		return (-1);
	i = 6;
	link->pos.x = ft_atoi(mlx->scene[*k + 3], &i);
	link->pos.y = ft_atoi(mlx->scene[*k + 3], &i);
	link->pos.z = ft_atoi(mlx->scene[*k + 3], &i);
	if (mlx->scene[*k + 3][i] != ')')
		return (-1);
	link->next = NULL;
	mlx->light = ft_add_light_link(mlx, link);
	*k += 5;
	return (0);
}

int			ft_add_plane(t_mlx *mlx, int *k, int i)
{
	t_obj	*link;

	if (!(link = (t_obj *)malloc(sizeof(t_obj))))
		return (-1);
	link->type = 3;
	if (ft_strcmp(mlx->scene[*k + 1], "	{") != 0 || \
			ft_strcmp(mlx->scene[*k + 5], "	}") != 0)
		return (-1);
	if (ft_col_n_pos(mlx, link, *k) == -1 || \
			ft_strncmp(mlx->scene[*k + 4], "		rot(", 6) != 0)
		return (-1);
	link->rot.x = (float)ft_atoi(mlx->scene[*k + 4], &i);
	link->rot.y = (float)ft_atoi(mlx->scene[*k + 4], &i);
	link->rot.z = (float)ft_atoi(mlx->scene[*k + 4], &i);
	if (mlx->scene[*k + 4][i] != ')')
		return (-1);
	link->next = NULL;
	mlx->obj = ft_add_object_link(mlx, link);
	*k += 6;
	return (0);
}

int			ft_add_cyl_cone(t_mlx *mlx, int *k, int t, int i)
{
	t_obj	*link;

	if (!(link = (t_obj *)malloc(sizeof(t_obj))))
		return (-1);
	if (ft_strcmp(mlx->scene[*k + 1], "	{") != 0 || \
			ft_strcmp(mlx->scene[*k + 6], "	}") != 0 || (link->type = t) != t)
		return (-1);
	if (ft_col_n_pos(mlx, link, *k) == -1 || \
			ft_strncmp(mlx->scene[*k + 4], "		rot(", 6) != 0)
		return (-1);
	link->rot.x = (float)ft_atoi(mlx->scene[*k + 4], &i);
	link->rot.y = (float)ft_atoi(mlx->scene[*k + 4], &i);
	link->rot.z = (float)ft_atoi(mlx->scene[*k + 4], &i);
	if (mlx->scene[*k + 4][i] != ')')
		return (-1);
	if (ft_strncmp(mlx->scene[*k + 5], "		size(", 7) != 0)
		return (-1);
	i = 7;
	link->size = ft_atoi(mlx->scene[*k + 5], &i);
	if (mlx->scene[*k + 5][i] != ')')
		return (-1);
	link->next = NULL;
	mlx->obj = ft_add_object_link(mlx, link);
	*k += 7;
	return (0);
}

int			ft_add_sphere(t_mlx *mlx, int *k, int i)
{
	t_obj	*link;

	if (!(link = (t_obj *)malloc(sizeof(t_obj))))
		return (-1);
	link->type = 4;
	if (ft_strcmp(mlx->scene[*k + 1], "	{") != 0 || \
			ft_strcmp(mlx->scene[*k + 5], "	}") != 0)
		return (-1);
	if (ft_col_n_pos(mlx, link, *k) == -1)
		return (-1);
	if (ft_strncmp(mlx->scene[*k + 4], "		size(", 7) != 0)
		return (-1);
	link->size = ft_atoi(mlx->scene[*k + 4], &i);
	if (mlx->scene[*k + 4][i] != ')')
		return (-1);
	link->next = NULL;
	mlx->obj = ft_add_object_link(mlx, link);
	*k += 6;
	return (0);
}
