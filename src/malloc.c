/*
** malloc.c for mall in /home/scutar_n/rendu/PSU/memory/PSU_2016_malloc/src
**
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Mon Jan 30 14:47:14 2017 Nathan Scutari
** Last update Wed Feb  1 10:36:59 2017 Nathan Scutari
*/

#include "malloc.h"

void	show_alloc_mem();
void	my_put_nbr(int);

t_malloc	*blocks = NULL;
t_malloc	*last = NULL;

void	*split_block(t_malloc *block, size_t size,
		     t_malloc *prev_free)
{
  int		align_size;
  t_malloc	*new;

  align_size = align8(size);
  if (align8(block->size) >= align_size + sizeof(t_malloc) + 4)
    {
      new = block->block + align_size;
      new->block = ((void*)new) + sizeof(t_malloc);
       if (last == block)
	 last = new;
      new->prev = block;
      new->size = align8(block->size) - align_size - sizeof(t_malloc);
      block->size = size;
      new->next = block->next;
      block->next = new;
      new->next_free = block->next_free;
      block->next_free = NULL;
      prev_free->next_free = new;
      if (new->next)
	new->next->prev = new;
      block->is_free = false;
      new->is_free = true;
      return (block->block);
    }
  else
    {
      block->is_free = false;
      prev_free->next_free = block->next_free;
      return (block->block);
    }
  return (NULL);
}

void	*first_alloc(size_t size)
{
  t_malloc	*tmp;
  int		alloc_size;
  int		pagesize;

  pagesize = getpagesize();
  alloc_size = alignpagesize(size + sizeof(t_malloc));
  tmp = sbrk(0);
  if ((sbrk(alloc_size)) == (void*) -1)
    return (NULL);
  tmp->block = (void*)tmp + sizeof(t_malloc);
  tmp->size = alloc_size - sizeof(t_malloc);
  tmp->is_free = true;
  tmp->next = NULL;
  tmp->prev = NULL;
  tmp->next_free = NULL;
  blocks = tmp;
  last = blocks;
  return (split_block(tmp, size, blocks));
}

void	*add_alloc(t_malloc *prev, size_t size)
{
  t_malloc	*tmp;
  int		alloc_size;
  int		pagesize;

  pagesize = getpagesize();
  alloc_size = alignpagesize(size + sizeof(t_malloc));
  tmp = sbrk(0);
  if ((sbrk(alloc_size)) == (void*) -1)
    return (NULL);
  tmp->block = (void*)tmp + sizeof(t_malloc);
  tmp->size = alloc_size - sizeof(t_malloc);
  tmp->is_free = true;
  tmp->next = NULL;
  tmp->prev = last;
  last->next = tmp;
  last = tmp;
  tmp->next_free = NULL;
  return (split_block(tmp, size, prev));
}

void	*malloc(size_t size)
{
  t_malloc		*tmp;
  t_malloc		*prev_free;

  write(1, "Malloc : ", 9);
  my_put_nbr(size);
  write(1, "\n", 1);
  if (size == 0)
    return (NULL);
  if (!blocks)
    tmp = first_alloc(size);
  else
    {
      prev_free = blocks;
      tmp = blocks;
      while (tmp)
	{
	  if (tmp->is_free == true && align8(tmp->size) >= align8(size))
	    {
	      tmp = split_block(tmp, size, prev_free);
	      break;
	    }
	  if (tmp->is_free == true)
	    prev_free = tmp;
	  tmp = tmp->next_free;
	}
      if (!tmp)
	tmp = add_alloc(prev_free, size);
    }
  /*  prev_free = blocks;
  while (prev_free)
    {
      if (prev_free->block == tmp)
	write(1, "found\n", 6);
      prev_free = prev_free->next;
      }*/
  show_free_mem();
  show_alloc_mem();
  return (tmp);
}
