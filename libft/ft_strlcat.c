/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 14:44:52 by fsidler           #+#    #+#             */
/*   Updated: 2015/12/03 17:45:09 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	m;

	i = 0;
	j = 0;
	while (dest[i] && i < n)
		i++;
	m = i;
	while (src[j] && i < n - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (m < n)
		dest[i] = '\0';
	return (m + ft_strlen(src));
}
