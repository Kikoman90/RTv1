/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsidler <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 13:22:37 by fsidler           #+#    #+#             */
/*   Updated: 2015/12/03 14:13:57 by fsidler          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *total, const char *find, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!*find)
		return ((char *)(total));
	if (n > ft_strlen(total))
		n = ft_strlen(total);
	while (j < n)
	{
		while (find[i] != total[j] && j < n)
			j++;
		while (find[i] == total[j] && j < n)
		{
			i++;
			j++;
		}
		if (!find[i])
			return ((char *)(total + (j - i)));
		j = j - i + 1;
		i = 0;
	}
	return (NULL);
}
