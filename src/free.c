/*
** free.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Jan 30 16:04:16 2017 Baptiste Veyssiere
** Last update Tue Jan 31 21:34:24 2017 Nathan Scutari
*/

#include "malloc.h"

void	my_put_nbr(int);

void	free_error_msg(char *err, int length, void *ptr)
{
  write(2, err, length);
  LongToHex((long)ptr);
  write(2, "\n", 1);
  exit(134);
}

t_malloc	*get_free_tmp(void *ptr)
{
  t_malloc	*tmp;
  t_malloc	*free;

  tmp = blocks;
  free = blocks;
  while (tmp)
    {
      if (tmp->is_free)
	free = tmp;
      if (tmp->block == ptr)
	break;
      tmp = tmp->next;
    }
  if (tmp == NULL)
    free_error_msg("free(): invalid pointer: ", 25, ptr);
  if (tmp->is_free == true)
    free_error_msg("double free or corruption: ", 27, ptr);
  tmp->next_free = free->next_free;
  free->next_free = tmp;
  return (tmp);
}

void	fusion(t_malloc *tmp)
{
  tmp->size += tmp->next->size + sizeof(t_malloc);
  tmp->next_free = tmp->next->next_free;
  if (tmp->next == last)
    last = tmp;
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
  write(1, "Free ", 5);
  my_put_nbr(tmp->size);
  write(1, "\n", 1);
  tmp->is_free = true;
  if (tmp->next && tmp->next->is_free == true)
      fusion(tmp);
  if (tmp->prev && tmp->prev->is_free == true)
    fusion(tmp->prev);
}
