/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 17:15:27 by fsidler           #+#    #+#             */
/*   Updated: 2015/12/13 19:13:26 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	j = n;
	while (j--)
		((UC *)dest)[j] = '\0';
	i = 0;
	while (n-- && src[i])
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
