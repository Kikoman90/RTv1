#include "rtv1.h"

static float	*ft_get_color_pixel(t_mlx *mlx, int x, int y, float* tab)
{
	int		i;

	i = -1;
	while (++i < 3)
		tab[i] = (unsigned char)(mlx->d[(y * mlx->size_line) +
		 (x * (mlx->bpp / 8)) + i]) / 255.;
	return (tab);
}

static double	ft_add_pixel(int x, int y, t_mlx *mlx, float *r)
{
	double	p;
	float	*tab;


	if (!(tab = (float *)malloc(sizeof(float) * 3)))
		return (1);
	p = 0.0;
	ft_fzero(r, 3);
	if (x > 0 && ++p > 0)
		ft_average(r, ft_get_color_pixel(mlx, x - 1, y, tab));
	if (x < WIN_W - 1 && ++p > 0)
		ft_average(r, ft_get_color_pixel(mlx, x + 1, y, tab));
	if (y > 0 && ++p > 0)
		ft_average(r, ft_get_color_pixel(mlx, x, y - 1, tab));
	if (y < WIN_H - 1 && ++p > 0)
		ft_average(r, ft_get_color_pixel(mlx, x, y + 1, tab));
	free(tab);
	return (p);
}

static void		*my_thread_process(void *arg)
{
	t_tab_th	*tab;
	float		r[3];
	double		p;
	int			x;
	int			y;

	tab = (t_tab_th *)arg;
	y = -1;
	while (++y < WIN_H)
	{
		x = tab->i * WIN_W / NB_THREAD;
		if (y % 2 == 0)
			++x;
		while (x < WIN_W * (tab->i + 1) / NB_THREAD)
		{
			p = ft_add_pixel(x, y, tab->mlx, r);
			ft_put_pixel((t_th *)tab->mlx, x, y, (((int)(r[2] / p * 255) & 0xff) << 16) +
			(((int)(r[1] / p * 255) & 0xff) << 8) + ((int)(r[0] / p * 255) & 0xff));
			x += 2;
		}
	}
	pthread_exit(0);
}

void			ft_draw_average_color(t_mlx *mlx)
{
	pthread_t	th[NB_THREAD];
	t_tab_th	tab[NB_THREAD];
	void		*ret;
	int			i;

	i = -1;
	while (++i < NB_THREAD)
	{
		tab[i].i = i;
		tab[i].mlx = mlx;
		pthread_create(&th[i], NULL, my_thread_process, &tab[i]);
	}
	i = -1;
	while (++i < NB_THREAD)
		(void)pthread_join(th[i], &ret);
}