/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:50:35 by amaula            #+#    #+#             */
/*   Updated: 2024/07/22 13:37:46 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isspace(char c)
{
	const char	*spaces = "\t\n\v\f\r ";

	while (*spaces)
	{
		if (c == *spaces)
			return (1);
		spaces++;
	}
	return (0);
}

static int	safe_accumulator(long *l, char c)
{
	if ((9223372036854775807 - (c - '0')) / 10 < *l)
		return (0);
	*l *= 10;
	*l += c - '0';
	return (1);
}

int	ft_atoi(const char *str)
{
	int		sign;
	long	ret;

	sign = 1;
	ret = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (*str && *str >= '0' && *str <= '9')
	{
		if (safe_accumulator(&ret, *str) == 0)
			return (0 - (sign == 1));
		str++;
	}
	return ((int)(ret *= sign));
}

