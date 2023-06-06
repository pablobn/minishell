/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdiaz-ru <sdiaz-ru@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:45:19 by pbengoec          #+#    #+#             */
/*   Updated: 2023/06/06 15:50:09 by sdiaz-ru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (*s)
	{
		i++;
		s++;
	}
	return (i);
}

// int main()
// {
// 	printf("Function strlen value = 'adios' \n");
// 	printf("Solution: %zu\n", ft_strlen("adios"));
// }