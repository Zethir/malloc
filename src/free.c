/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 15:40:32 by cboussau          #+#    #+#             */
/*   Updated: 2017/08/23 15:50:26 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	free_hub(t_block *block, size_t zone_size)
{
	block = NULL;
	zone_size = 0;
}

void	free_large(t_block *block)
{
	t_block *header;
	t_block	*prev;

	header = g_zone.large;
	prev = NULL;
	while (header)
	{
		if (header == block)
		{
			if (prev)
				prev->next = header->next;
			if (header->next)
				g_zone.large = header->next;
			else
				g_zone.large = NULL;
			munmap(block, block->size + sizeof(t_block));
			return ;
		}
		prev = header;
		header = header->next;
	}
}

void	free(void *ptr)
{
	t_block	*block;

	if (!ptr)
		return ;
	block = search_mem(ptr);
	if (!block)
		return ;
	if (block->size <= TINY_SIZE)
		free_hub(block, TINY_SIZE);
	else if (block->size <= SMALL_SIZE)
		free_hub(block, SMALL_SIZE);
	else
		free_large(block);
}
