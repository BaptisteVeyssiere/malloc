/*
** free.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Jan 30 16:04:16 2017 Baptiste Veyssiere
** Last update Mon Jan 30 17:07:51 2017 Baptiste Veyssiere
*/

#include "malloc.h"

t_malloc	*get_free_tmp(void *ptr)
{
  t_malloc	*tmp;

  tmp = blocks;
  while (tmp)
    {
      if (tmp->block == ptr)
	break;
      tmp = tmp->next;
    }
  if (tmp == NULL)
    {
      write(2, "free(): invalid pointer: ", 25);
      LongToHex((long)ptr);
      write(2, "\n", 1);
      exit(134);
    }
  if (tmp->is_free)
    {
      write(2, "double free or corruption: ", 27);
      LongToHex((long)ptr);
      write(2, "\n", 1);
      exit(134);
    }
  return (tmp);
}

void	fusion(t_malloc *tmp)
{
  tmp->size += tmp->next->size + sizeof(t_malloc);
  tmp->next = tmp->next->next;
  if (tmp->next)
    tmp->next->prev = tmp;
}

void		free(void *ptr)
{
  t_malloc	*tmp;

  if (ptr == NULL)
    return ;
  if (((long)ptr % 4) != 0)
    {
      write(2, "Pointer not aligned\n", 20);
      exit(134);
    }
  if ((long)ptr < (long)blocks || (long)ptr > (long)sbrk(0))
    {
      write(2, "Invalid free\n", 13);
      return ;
    }

  tmp = get_free_tmp(ptr);
  tmp->is_free = 1;
  if (tmp->prev && tmp->prev->is_free)
    fusion(tmp->prev);
  if (tmp->next && tmp->next->is_free)
    fusion(tmp);
}
