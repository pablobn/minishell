/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:18:17 by pbengoec          #+#    #+#             */
/*   Updated: 2022/09/30 17:08:09 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*copy;

	copy = (char *) malloc(ft_strlen(s1) + 1);
	if (copy == 0)
		return (0);
	ft_strlcpy(copy, s1, ft_strlen(s1) + 1);
	return (copy);
}
