/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 15:46:16 by cboussau          #+#    #+#             */
/*   Updated: 2017/08/27 22:06:50 by cboussau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/resource.h>
#include <pthread.h>
#include <libft.h>


#define TINY_SIZE		(size_t)getpagesize() * 2
#define	SMALL_SIZE		(size_t)getpagesize() * 16
#define TINY_ZONE		(size_t)(TINY_SIZE + sizeof(t_block)) * 100
#define SMALL_ZONE		(size_t)(SMALL_SIZE + sizeof(t_block)) * 100

#define PROT			PROT_READ | PROT_WRITE
#define	MAP				MAP_ANON | MAP_PRIVATE

typedef struct		s_block
{
	size_t			size;
	int				free;
	void			*mem;
	struct s_block	*next;
}					t_block;

typedef struct		s_zone
{
	struct s_block	*tiny;
	struct s_block	*small;
	struct s_block	*large;
}					t_zone;

t_zone				g_zone;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
void				show_alloc_mem();

void				*allocate_tiny(size_t size);
void				*allocate_small(size_t size);
void				*allocate_large(size_t size);
void				put_in_block(t_block **block, size_t size);
void				split_block(t_block **block, size_t size);

t_block				*generate_tiny_block(size_t size);
t_block				*generate_small_block(size_t size);
t_block				*check_free_block(t_block **head, size_t size);
t_block				*check_size(t_block **head, size_t size);
t_block				*last_node(t_block **head);

#endif
