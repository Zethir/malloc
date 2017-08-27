/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 15:39:37 by cboussau          #+#    #+#             */
/*   Updated: 2017/08/27 19:11:59 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*allocate_large(size_t size)
{
	t_block	*block;
	
	if ((block = last_node(&(g_zone.large_zone))))
	{
		if ((block->next = (t_block *)mmap(0, size, PROT, MAP, -1, 0))
				== MAP_FAILED)
			return (MAP_FAILED);
		block = block->next;
	}
	else
	{
		if ((g_zone.large_zone = (t_block *)mmap(0, size, PROT, MAP, -1, 0))
				== MAP_FAILED)
			return (MAP_FAILED);
		block = g_zone.large_zone;
	}
	block->size = size;
	block->free = 0;
	block->mem = block + 1;
	return (block->mem);
}

void	*malloc(size_t size)
{
	void	*mem;

/*	
 	if (size <= 0)
		return (NULL);
 	if (size <= TINY_SIZE)
		mem = allocate_tiny(size);
	else if (size <= SMALL_SIZE)
		mem = allocate_small(size);
	else
	{*/
		mem = allocate_large(size + sizeof(t_block));
//	}
//	if (mem = MAP_FAILED)
//		return (NULL);
	return (mem);
}
