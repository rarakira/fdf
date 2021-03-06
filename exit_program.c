/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 12:50:11 by lbaela            #+#    #+#             */
/*   Updated: 2021/10/27 17:12:19 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	exit_on_error(char	*msg)
{
	ft_putendl_fd(msg, 1);
	exit(1);
}
