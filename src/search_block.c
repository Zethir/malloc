/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 21:18:41 by cboussau          #+#    #+#             */
/*   Updated: 2017/08/27 22:17:59 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <malloc.h>

t_block *search_node(t_block *block, void *mem)
{
	while (block)
	{
		if (block->mem == mem)
			return (block);
		block = block->next;
	}
	return (NULL);
}

t_block	*search_mem(void *mem)
{
	t_block	*block;

	if ((block = search_node(g_zone.tiny, mem)))
		return (block);
	else if ((block = search_node(g_zone.small, mem)))
		return (block);
	else if ((block = search_node(g_zone.large, mem)))
		return (block);
	return (NULL);
}
