/*
** malloc_split.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Sun Feb 12 16:52:16 2017 Baptiste Veyssiere
** Last update Sun Feb 12 16:53:10 2017 Baptiste Veyssiere
*/

#include "malloc.h"

void	*split_o(t_malloc *block, size_t size, t_malloc *prev_free, int align_size)
{
  t_malloc	*new;

  new = block->block + align_size;
  new->block = ((void*)new) + sizeof(t_malloc);
  if (glob.last == block)
    glob.last = new;
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

void	*split_block(t_malloc *block, size_t size,
		     t_malloc *prev_free)
{
  int		align_size;

  align_size = align8(size);
  if (align8(block->size) >= align_size + sizeof(t_malloc) + 4)
    return (split_o(block, size, prev_free, align_size));
  else
    {
      block->is_free = false;
      prev_free->next_free = block->next_free;
      return (block->block);
    }
  return (NULL);
}
