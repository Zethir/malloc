/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_alloc_mem.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 15:40:32 by cboussau          #+#    #+#             */
/*   Updated: 2017/09/04 14:54:12 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

size_t		print_alloc_mem(t_block *block, char *type_mem)
{
	size_t	sum_alloc;

	ft_putstr(type_mem);
	print_memory((void *)block);
	ft_putchar('\n');
	sum_alloc = 0;
	while (block)
	{
		if (block->free == 0)
		{
			print_memory((void *)block->mem);
			ft_putstr(" - ");
			print_memory((void *)block->mem + block->size);
			ft_putstr(" : ");
			ft_putnbr(block->size);
			ft_putstr(" octets\n");
			sum_alloc += block->size;
		}
		block = block->next;
	}
	return (sum_alloc);
}

void		show_alloc_mem(void)
{
	size_t	sum_alloc;

	sum_alloc = 0;
	pthread_mutex_lock(&g_mutex);
	if (g_zone.tiny)
		sum_alloc += print_alloc_mem(g_zone.tiny, "TINY : ");
	if (g_zone.small)
		sum_alloc += print_alloc_mem(g_zone.small, "SMALL : ");
	if (g_zone.large)
		sum_alloc += print_alloc_mem(g_zone.large, "LARGE : ");
	ft_putstr("Total : ");
	ft_putnbr(sum_alloc);
	ft_putstr(" octets\n");
	pthread_mutex_unlock(&g_mutex);
}
