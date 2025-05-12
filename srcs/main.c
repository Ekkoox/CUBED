/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enschnei <enschnei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 15:12:16 by enschnei          #+#    #+#             */
/*   Updated: 2025/05/12 15:54:53 by enschnei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int ac, char **av, char **ev)
{
    t_cubed cubed;
    (void) av;
    (void) ev;

    if (ac != 2)
        return (ft_printf(2, "Error arguments\n"), EXIT_FAILURE);
    // cubed.map = split_map(av[1]);
    ft_printf(1, "Bienvenue dans CUB3D\n");
    return(EXIT_SUCCESS);
}