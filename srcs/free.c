/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/22 14:08:15 by fsidler           #+#    #+#             */
/*   Updated: 2016/08/18 17:05:52 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_obj	*copy_obj(t_obj *obj)
{
	t_obj	*newlist;

	if (!(newlist = (t_obj *)malloc(sizeof(t_obj))))
		return (NULL);
	if (obj && newlist)
	{
		newlist->type = obj->type;
		newlist->size = obj->size;
		newlist->rot = (t_vec){obj->rot.x, obj->rot.y, obj->rot.z};
		newlist->pos = (t_vec){obj->pos.x, obj->pos.y, obj->pos.z};
		newlist->col.red = obj->col.red;
		newlist->col.green = obj->col.green;
		newlist->col.blue = obj->col.blue;
		newlist->next = NULL;
		if (newlist && obj->next)
			newlist->next = copy_obj(obj->next);
		return (newlist);
	}
	return (NULL);
}

void	ft_copy(t_mlx *mlx, t_th *th)
{
	th->spec = mlx->spec;
	th->maxref = mlx->maxref;
	th->pref = mlx->pref;
	th->cpt = 0;
	th->cam_pos = (t_vec){mlx->cam_pos.x, mlx->cam_pos.y, mlx->cam_pos.z};
	th->cam_dir = (t_vec){mlx->cam_dir.x, mlx->cam_dir.y, mlx->cam_dir.z};
	th->ray_dir = (t_vec){mlx->ray_dir.x, mlx->ray_dir.y, mlx->ray_dir.z};
	th->light = copy_obj(mlx->light);
	th->obj = copy_obj(mlx->obj);
	th->bpp = mlx->bpp;
	th->size_line = mlx->size_line;
	th->d = mlx->d;
}

int		ft_free_lists(t_obj *lgt, t_obj *obj)
{
	t_obj	*fst;
	t_obj	*tmp;

	fst = obj;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
	fst = lgt;
	while (fst != NULL)
	{
		tmp = fst->next;
		free(fst);
		fst = tmp;
	}
	return (-1);
}

int		ft_free_arg(t_mlx *mlx, char *buf, int r)
{
	if (r == 0)
		free(buf);
	else if (r == 1)
	{
		ft_putendl("error: Dynamic memory allocation failed");
		free(mlx->scene);
	}
	else if (r == 2)
	{
		ft_putendl("error: scene descriptor incorrect or incomplete");
		free(mlx->scene);
	}
	else if (r == 3)
	{
		ft_putendl("error: Dynamoc memory allocation failed");
		free(mlx->scene);
		ft_free_lists(mlx->light, mlx->obj);
	}
	return (-1);
}
