/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_block.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 21:18:41 by cboussau          #+#    #+#             */
/*   Updated: 2017/08/27 22:17:59 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

int		generate_tiny_block(t_block **block, size_t size)
{
	t_block	*new_block;
	t_block *last_block;

	new_block = *block;
	if ((last_block = last_node(&(g_zone.tiny))))
	{
		if ((last_block->next = (t_block *)mmap(0, TINY_ZONE, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (1);
		new_block = last_block->next;
	}
	else
	{
		if ((g_zone.tiny = (t_block *)mmap(0, TINY_ZONE, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (1);
		new_block = g_zone.tiny;
	}
	new_block->size = TINY_ZONE - sizeof(t_block);
	split_block(&new_block, size);
	return (0);
}
int		generate_small_block(t_block **block, size_t size)
{
	t_block	*new_block;
	t_block *last_block;

	new_block = *block;
	if ((last_block = last_node(&(g_zone.small))))
	{
		if ((last_block->next = (t_block *)mmap(0, SMALL_ZONE, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (1);
		new_block = last_block->next;
	}
	else
	{
		if ((g_zone.small = (t_block *)mmap(0, SMALL_ZONE, PROT, MAP, -1, 0))
			== MAP_FAILED)
			return (1);
		new_block = g_zone.small;
	}
	new_block->size = SMALL_ZONE - sizeof(t_block);
	split_block(&new_block, size);
	return (0);
}
