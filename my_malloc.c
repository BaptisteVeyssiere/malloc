/*
** my_malloc.c for malloc in /home/scutar_n/rendu/PSU/memory/PSU_2016_malloc
** 
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
** 
** Started on  Wed Jan 25 10:56:02 2017 Nathan Scutari
** Last update Wed Jan 25 12:19:34 2017 Nathan Scutari
*/

#include <unistd.h>
#include "my_malloc.h"

static void	*first_alloc(size_t size)
{
  sbrk(0); // some weird magics
  blocks = sbrk(0);
  if ((sbrk(align8(size) + sizeof(t_malloc))) == (void *)-1)
    return (NULL);
  blocks->size = align8(size);
  blocks->block = ((void*)blocks) + sizeof(t_malloc);
  blocks->prev = NULL;
  blocks->next = NULL;
  blocks->is_free = 0;
  return (blocks->block);
}

static void	*split_block(t_malloc *tmp, t_malloc *save, size_t size)
{
  t_malloc	*new;

  if (tmp->size >= size + sizeof(t_malloc) + 4)
    {
      new = tmp->block + size;
      new->block = ((void*)new) + sizeof(t_malloc);
      new->size = tmp->size - size - sizeof(t_malloc);
      tmp->size = size;
      new->is_free = 1;
      tmp->is_free = 0;
      new->prev = tmp;
      new->next = tmp->next;
      tmp->next = new;
      return (tmp->block);
    }
  else
    {
      tmp->is_free = 0;
      return (tmp->block);
    }
  return (NULL);
}

static void	*add_allocation(t_malloc *save, size_t size)
{
  t_malloc	*new;

  new = sbrk(0);
  save->next = new;
  if ((sbrk(align8(size) + sizeof(t_malloc))) == (void *)-1)
    return (NULL);
  new->size = align8(size);
  new->block = ((void*)new) + sizeof(t_malloc);
  new->prev = save;
  new->next = NULL;
  new->is_free = 0;
  return (new->block);
}

void	*malloc(size_t size)
{
  t_malloc	*save;
  t_malloc	*tmp;

  tmp = NULL;
  save = NULL;
  if (size == 0)
    return (NULL); // duh
  if (blocks == NULL)
    return (first_alloc(size));
  tmp = blocks;
  while (tmp != NULL)
    {
      if (tmp->size >= align8(size) && tmp->is_free)
	return (split_block(tmp, save, align8(size)));
      save = tmp;
      tmp = tmp->next;
    }
  return (add_allocation(save, size));
}

int	main()
{
  char	*str;
  char	*str2;

  str = malloc(8);
  str2 = malloc(8);
  return (0);
}
