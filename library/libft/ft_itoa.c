/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbengoec <pbengoec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:03:47 by pbengoec          #+#    #+#             */
/*   Updated: 2022/10/04 15:22:27 by pbengoec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_countdigits(int n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*ft_givevalue(int n, size_t size, char *new)
{
	if (n == -2147483648)
	{
		new[size--] = -(n % 10) + 48;
		ft_givevalue(n / 10, size, new);
	}
	else if (n >= 0 && n <= 9)
	{
		new[size--] = n + 48;
		return (new);
	}
	else if (n < 0)
	{
		n = -n;
		new[0] = '-';
		ft_givevalue(n, size, new);
	}
	else
	{
		new[size--] = n % 10 + 48;
		ft_givevalue(n / 10, size, new);
	}
	return (NULL);
}

char	*ft_itoa(int n)
{
	char	*new;
	size_t	size;

	if (n < 0)
	{
		if (n == -2147483648)
		{
			n++;
			size = ft_countdigits(-n) + 1;
			n--;
		}
		else
			size = ft_countdigits(-n) + 1;
	}
	else
		size = ft_countdigits(n);
	new = ft_calloc(size + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	new[size] = '\0';
	ft_givevalue(n, size - 1, new);
	return (new);
}
