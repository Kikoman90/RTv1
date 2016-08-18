/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 15:48:36 by fsidler           #+#    #+#             */
/*   Updated: 2016/08/18 17:06:11 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static int		ft_start(char *s, int *fd)
{
	if (BUFF_SIZE < 1)
	{
		ft_putendl("error: BUFF_SIZE must be greater than 0");
		return (-1);
	}
	if ((*fd = open(s, O_RDONLY)) == -1)
	{
		ft_putendl(ft_strjoin("error: ", strerror(errno), 'N'));
		return (-1);
	}
	return (1);
}

static char		*ft_getbuf(char *s, int *nbl)
{
	int		fd;
	char	*buf;
	char	*line;

	buf = ft_strnew(1);
	if (ft_start(s, &fd) == -1)
		return (NULL);
	while (get_next_line(fd, &line) > 0 && (*nbl)++ > -1)
		buf = ft_strjoin(buf, ft_strjoin(line, "\n", 'L'), 'B');
	if (close(fd) == -1)
	{
		ft_putendl(ft_strjoin("error: ", strerror(errno), 'N'));
		return (NULL);
	}
	return (buf);
}

static char		**ft_getscene(char *buf, int nbl, int j)
{
	int		i;
	int		k;
	char	**scene;

	k = 0;
	if (!buf)
		return (NULL);
	if (!(scene = (char **)malloc(sizeof(char *) * (nbl + 1))))
		return (NULL);
	while (buf[k] != '\0' && j < nbl)
	{
		i = 0;
		if (!(scene[j] = (char *)malloc(sizeof(char) * ft_linelen(buf, k))))
			return (NULL);
		while (buf[k] != '\n' && buf[k] != '\0')
			scene[j][i++] = buf[k++];
		scene[j][i] = '\0';
		k++;
		j++;
	}
	free(buf);
	return (scene);
}

static int		init_mlx(t_mlx *mlx, char *s)
{
	char	*buf;
	char	*name;

	name = ft_strjoin("RTv1: ", s, 'N');
	mlx->mlx = mlx_init();
	mlx->img = mlx_new_image(mlx->mlx, WIN_W, WIN_H);
	mlx->win = mlx_new_window(mlx->mlx, WIN_W, WIN_H, name);
	free(name);
	mlx->d = mlx_get_data_addr(mlx->img, &mlx->bpp, &mlx->size_line,
	&mlx->endian);
	mlx->nbl = 0;
	if ((buf = ft_getbuf(s, &(mlx->nbl))) == NULL)
		return (ft_free_arg(mlx, buf, 0));
	if ((mlx->scene = ft_getscene(buf, mlx->nbl, 0)) == NULL)
		return (ft_free_arg(mlx, NULL, 1));
	mlx->obj = NULL;
	mlx->light = NULL;
	mlx->hud = 1;
	mlx->spec = 0;
	mlx->maxref = 0;
	mlx->pref = 0;
	mlx->selection = 0;
	if (ft_parser(mlx) == -1)
		return (ft_free_arg(mlx, NULL, 2));
	return (0);
}

int				main(int argc, char **argv)
{
	t_mlx	*mlx;

	(void)argv;
	if (argc != 2)
	{
		ft_putendl("usage: ./RTv1 input_file");
		return (0);
	}
	if (!(mlx = (t_mlx *)malloc(sizeof(t_mlx))))
		return (0);
	if (init_mlx(mlx, argv[1]) == -1)
	{
		free(mlx);
		return (0);
	}
	ft_instructions();
	if (ft_draw(mlx) == -1)
		return (0);
	mlx_mouse_hook(mlx->win, ft_mouse, mlx);
	mlx_hook(mlx->win, 17, (1L << 17), close_hook, mlx);
	mlx_hook(mlx->win, KEYPRESS, KEYPRESSMASK, key_hook, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
