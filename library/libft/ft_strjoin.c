/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 19:06:02 by pbengoec          #+#    #+#             */
/*   Updated: 2023/06/12 19:29:13 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new;
	size_t	sum;

	sum = ft_strlen(s1) + ft_strlen(s2) + 1;
	new = ft_calloc(sum, sizeof(char));
	if (new == 0)
		return (0);
	ft_strlcpy(new, s1, sum);
	ft_strlcat(new, s2, sum);
	return (new);
}
