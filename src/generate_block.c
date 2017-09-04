/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 21:18:41 by cboussau          #+#    #+#             */
/*   Updated: 2017/09/04 15:21:27 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_block		*generate_tiny_block(size_t size)
{
	t_block	*block;

	if ((block = last_node(&(g_zone.tiny))))
	{
		if ((block->next = (t_block *)mmap(0, TINY_ZONE, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (NULL);
		block = block->next;
	}
	else
	{
		if ((g_zone.tiny = (t_block *)mmap(0, TINY_ZONE, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (NULL);
		block = g_zone.tiny;
	}
	block->size = TINY_ZONE - sizeof(t_block);
	split_block(&block, size);
	return (block);
}

t_block		*generate_small_block(size_t size)
{
	t_block	*block;

	if ((block = last_node(&(g_zone.small))))
	{
		if ((block->next = (t_block *)mmap(0, SMALL_ZONE, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (NULL);
		block = block->next;
	}
	else
	{
		if ((g_zone.small = (t_block *)mmap(0, SMALL_ZONE, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (NULL);
		block = g_zone.small;
	}
	block->size = SMALL_ZONE - sizeof(t_block);
	split_block(&block, size);
	return (block);
}
