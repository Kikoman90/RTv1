/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 17:24:09 by fsidler           #+#    #+#             */
/*   Updated: 2015/12/13 19:01:17 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *tot, const char *fnd)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*fnd == '\0')
		return ((char *)tot);
	while (tot[j])
	{
		i = 0;
		while (i < ft_strlen(fnd) - 1 && tot[j] && (UC)fnd[i] == (UC)tot[j])
		{
			i++;
			j++;
		}
		if ((UC)tot[j] - (UC)fnd[i] == 0)
			return ((char *)(tot + (j - i)));
		j = (j - i) + 1;
	}
	return (NULL);
}
