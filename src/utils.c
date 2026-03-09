/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emaigne <emaigne@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/09 14:14:03 by emaigne           #+#    #+#             */
/*   Updated: 2026/03/09 14:33:57 by emaigne          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_intnum(char *str)
{
	int	i;
	int	digit_count;

	if (!str || !*str)
		return (0);
	i = 0;
	digit_count = 0;
	if (str[0] == '-' || str[0] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		digit_count++;
		i++;
	}
	if (digit_count > 10)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	nbr;
	int	sign;

	nbr = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sign *= -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	return (nbr * sign);
}
