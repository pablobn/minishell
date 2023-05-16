/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:26:50 by pbengoec          #+#    #+#             */
/*   Updated: 2022/09/22 20:09:31 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen(s);
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *) &s[i]);
		i--;
	}
	return (NULL);
}

// int main()
// {
// 	// printf("Function strrchr str = \"hola que tal\", char = 'a' \n");
// 	// printf("Solution: %s\n",ft_strrchr("hola que tal", 'a'));
// 	// printf("TRUE Solution: %s\n",strrchr("hola que tal", 'a'));
// 	//printf("%c\n",'\xe2\x80\x93');
// }