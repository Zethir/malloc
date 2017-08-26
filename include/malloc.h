/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboussau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/17 15:46:16 by cboussau          #+#    #+#             */
/*   Updated: 2017/08/26 16:29:29 by cboussau         ###   ########.fr       */
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

#define TINY_ZONE		
#define SMALL_ZONE		

typedef enum		e_block_type
{
	TINY,
	SMALL,
	LARGE
}					t_block_type;					

typedef struct		s_mem
{
	t_block_type	block_type;
	struct s_mem	*next;
}					t_mem;

#endif
