/*
** realloc.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Jan 30 15:29:31 2017 Baptiste Veyssiere
** Last update Thu Feb  2 15:39:46 2017 Nathan Scutari
*/

#include "malloc.h"

void		*realloc(void *ptr, size_t size)
{
  t_malloc	*tmp;
  void		*new;
  size_t	oldsize;

  if (ptr == NULL)
    return (malloc(size));
  else if (size == 0)
    {
      free(ptr);
      return (NULL);
    }

  tmp = glob.blocks;
  while (tmp)
    {
      if (tmp->block == ptr)
	break;
      tmp = tmp->next;
    }
  free(ptr);
  oldsize = tmp->size;
  new = malloc(size);
  for(size_t i = 0; i < size && i < oldsize; ++i)
    *((char*)new + i) = *((char*)ptr + i);
  return (new);
}
