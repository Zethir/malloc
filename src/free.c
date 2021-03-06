/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 15:40:32 by cboussau          #+#    #+#             */
/*   Updated: 2017/09/04 14:54:23 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	free_large(t_block *block, t_block *header)
{
	t_block	*prev;

	prev = NULL;
	while (header)
	{
		if (header == block)
		{
			if (prev)
				prev->next = header->next;
			else if (header->next)
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
	pthread_mutex_lock(&g_mutex);
	block = search_mem(ptr);
	if (!block)
		return ;
	if (block->size <= TINY_SIZE || block->size <= SMALL_SIZE)
		block->free = 1;
	else
		free_large(block, g_zone.large);
	pthread_mutex_unlock(&g_mutex);
}
