/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/23 15:39:37 by cboussau          #+#    #+#             */
/*   Updated: 2017/08/31 00:07:33 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

void	*allocate_tiny(size_t size)
{
	t_block	*block;

	if ((block = check_size(&(g_zone.tiny), size)))
		put_in_block(&block, size);
	else if ((block = check_free_block(&(g_zone.tiny), size + sizeof(t_block))))
		split_block(&block, size);
	else if ((block = generate_tiny_block(size)) == NULL)
		return (NULL);
	return (block->mem);
}

void	*allocate_small(size_t size)
{
	t_block	*block;

	if ((block = check_size(&(g_zone.small), size)))
		put_in_block(&block, size);
	else if ((block = check_free_block(&(g_zone.small),
					size + sizeof(t_block))))
		split_block(&block, size);
	else if ((block = generate_small_block(size)) == NULL)
		return (NULL);
	return (block->mem);
}

void	*allocate_large(size_t size)
{
	t_block	*block;

	if ((block = last_node(&(g_zone.large))))
	{
		if ((block->next = (t_block *)mmap(0, size, PROT, MAP, -1, 0))
				== MAP_FAILED)
			return (NULL);
		block = block->next;
	}
	else
	{
		if ((g_zone.large = (t_block *)mmap(0, size, PROT, MAP, -1, 0))
				== MAP_FAILED)
			return (NULL);
		block = g_zone.large;
	}
	block->size = size - sizeof(t_block);
	block->free = 0;
	block->mem = block + 1;
	return (block->mem);
}

void	*malloc_hub(size_t size)
{
	void	*mem;

	if (size <= 0)
		return (NULL);
	if (size <= TINY_SIZE)
		mem = allocate_tiny(size);
	else if (size <= SMALL_SIZE)
		mem = allocate_small(size);
	else
		mem = allocate_large(size + sizeof(t_block));
	if (!mem)
		return (NULL);
	return (mem);
}

void	*malloc(size_t size)
{
	void	*mem;

	pthread_mutex_lock(&g_mutex);
	mem = malloc_hub(size);
	pthread_mutex_unlock(&g_mutex);
	return (mem);
}
