/*
** my_malloc.h for my_malloc in /home/scutar_n/rendu/PSU/memory/PSU_2016_malloc
** 
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
** 
** Started on  Wed Jan 25 10:51:19 2017 Nathan Scutari
** Last update Wed Jan 25 12:14:37 2017 Baptiste Veyssiere
*/

#ifndef MY_MALLOC_H_
# define MY_MALLOC_H_

#define _GNU_SOURCE

#include <unistd.h>
#include <stdlib.h>

typedef struct	s_malloc
{
  size_t		size;
  struct s_malloc	*next;
  struct s_malloc	*prev;
  int			is_free;
  void			*block;
}		t_malloc;

t_malloc	*blocks = NULL;

#endif /* !MY_MALLOC_H_ */
