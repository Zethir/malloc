/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 15:46:16 by cboussau          #+#    #+#             */
/*   Updated: 2017/08/27 18:12:27 by cboussau         ###   ########.fr       */
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


#define TINY_SIZE		(size_t)getpagesize() * 2;
#define	SMALL_SIZE		(size_t)getpagesize() * 16;
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
	struct s_block	*tiny_zone;
	struct s_block	*small_zone;
	struct s_block	*large_zone;
}					t_zone;

t_zone				g_zone;

void				*malloc(size_t size);
void				free(void *ptr);
void				*realloc(void *ptr, size_t size);
t_block				*last_node(t_block **head);

#endif
