/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 15:41:20 by cboussau          #+#    #+#             */
/*   Updated: 2017/08/31 00:05:28 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*join_block(t_block *block, size_t size)
{
	block->next = (void *)block->mem + size;
	block->next->mem = block->next + 1;
	block->next->size = block->next->size - (size - block->size);
	block->next->free = 1;
	block->size = size;
	return (block->mem);
}

void	*realloc_hub(t_block *block, size_t size)
{
	void	*new_block;

	if (block->next && block->next->free &&
			block->next->size > size - block->size + 1)
	{
		if (block->size <= TINY_SIZE || block->size <= SMALL_SIZE)
			return (join_block(block, size));
		else
			return (NULL);
	}
	else if (!(new_block = malloc(size)))
		return (NULL);
	ft_memcpy(new_block, block->mem, block->size);
	free(block->mem);
	return (new_block);
}

void	*realloc(void *ptr, size_t size)
{
	t_block	*block;
	void	*mem;

	if (!ptr)
		return (NULL);
	block = search_mem(ptr);
	if (!block)
		return (NULL);
	if (block->size > size)
		return (block->mem);
	pthread_mutex_lock(&g_mutex);
	mem = realloc_hub(block, size);
	pthread_mutex_unlock(&g_mutex);
	return (mem);
}
