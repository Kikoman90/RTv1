/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/23 16:34:18 by fsidler           #+#    #+#             */
/*   Updated: 2016/08/17 16:14:27 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		ft_hud(t_mlx *mlx)
{
	char	*s;

	if (mlx->hud == 1)
	{
		s = ft_strjoin("number of reflections: ", ft_itoa(mlx->maxref), 'R');
		MSP(mlx->mlx, mlx->win, 50, 750, 0x00FEDC, s);
		free(s);
		if (mlx->spec == 1)
			MSP(mlx->mlx, mlx->win, 50, 765, 0x00FEDC, "specularity: on");
		else
			MSP(mlx->mlx, mlx->win, 50, 765, 0x00FEDC, "specularity: off");
	}
}

void		ft_instructions(void)
{
	ft_putendl("--- INSTRUCTIONS ---");
	ft_putendl("left click: select object");
	ft_putendl("ENTER: deselect object");
	ft_putendl("< ^ > v: rotate camera/object");
	ft_putendl("pg up/pg down: rotate object along z axis");
	ft_putendl("w a s d: move camera/object");
	ft_putendl("+/-(num): move camera/object along local z axis");
	ft_putendl("+/-: increase/decrease size/angle for objects");
	ft_putendl("G: activate/deactivate gloss");
	ft_putendl("R/F: increase/decrease the number of reflections");
	ft_putendl("E: activate/deactivate reflection on planes only");
	ft_putendl("TAB: hide/show hud");
	ft_putendl("ESC: exit");
}

static int	ft_last_hook(int keycode, t_mlx *mlx)
{
	float	tmp_rot;

	if (keycode == 121 && TMP->type != 4 && (tmp_rot = TMP->rot.x) < 6000.0)
	{
		TMP->rot.x = TMP->rot.x * cosf(0.5) + TMP->rot.y * (-sinf(0.5));
		TMP->rot.y = tmp_rot * sinf(0.5) + TMP->rot.y * cosf(0.5);
	}
	if (keycode == 116 && TMP->type != 4 && (tmp_rot = TMP->rot.x) > -6000.0)
	{
		TMP->rot.x = TMP->rot.x * cosf(-0.5) + TMP->rot.y * (-sinf(-0.5));
		TMP->rot.y = tmp_rot * sinf(-0.5) + TMP->rot.y * cosf(-0.5);
	}
	return (0);
}

int			ft_objects_rot(int keycode, t_mlx *mlx)
{
	float	tmp_rot;

	if (keycode == 123 && TMP->type != 4 && (tmp_rot = TMP->rot.x) < 6000.0)
	{
		TMP->rot.x = TMP->rot.x * cosf(0.5) + TMP->rot.z * sinf(0.5);
		TMP->rot.z = tmp_rot * (-sinf(0.5)) + TMP->rot.z * cosf(0.5);
	}
	if (keycode == 124 && TMP->type != 4 && (tmp_rot = TMP->rot.x) > -6000.0)
	{
		TMP->rot.x = TMP->rot.x * cosf(-0.5) + TMP->rot.z * sinf(-0.5);
		TMP->rot.z = tmp_rot * (-sinf(-0.5)) + TMP->rot.z * cosf(-0.5);
	}
	if (keycode == 125 && TMP->type != 4 && (tmp_rot = TMP->rot.y) > -6000.0)
	{
		TMP->rot.y = TMP->rot.y * cosf(-0.5) + TMP->rot.z * (-sinf(-0.5));
		TMP->rot.z = tmp_rot * sinf(-0.5) + TMP->rot.z * cosf(-0.5);
	}
	if (keycode == 126 && TMP->type != 4 && (tmp_rot = TMP->rot.y) < 6000.0)
	{
		TMP->rot.y = TMP->rot.y * cosf(0.5) + TMP->rot.z * (-sinf(0.5));
		TMP->rot.z = tmp_rot * sinf(0.5) + TMP->rot.z * cosf(0.5);
	}
	return (ft_last_hook(keycode, mlx));
}

float		*ft_endlight(t_obj *tmp, t_obj *light, float *tab, float d)
{
	LAMBERT = ft_clamp(LAMBERT * 4.0 * d, 0.0, 1.0);
	tab[0] += LAMBERT * (tmp->col.red / 255) * (light->col.red / 255);
	tab[1] += LAMBERT * (tmp->col.green / 255) * (light->col.green / 255);
	tab[2] += LAMBERT * (tmp->col.blue / 255) * (light->col.blue / 255);
	return (tab);
}
