/*
** free.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Jan 30 16:04:16 2017 Baptiste Veyssiere
** Last update Thu Feb  2 15:50:09 2017 Nathan Scutari
*/

#include "malloc.h"

void	free_error_msg(char *err, int length, void *ptr)
{
  pthread_mutex_unlock(&glob.mutex);
  write(2, err, length);
  LongToHex((long)ptr);
  write(2, "\n", 1);
  exit(134);
}

t_malloc	*get_free_tmp(void *ptr)
{
  t_malloc	*tmp;
  t_malloc	*tmp2;
  t_malloc	*free;

  free = glob.blocks;
  tmp = (t_malloc*)((void*)ptr - sizeof(t_malloc));
  if (tmp->block != ptr)
    free_error_msg("free(): invalid pointer: ", 25, ptr);
  if (tmp->is_free == true)
    free_error_msg("double free or corruption: ", 27, ptr);
  tmp2 = tmp;
  while (tmp2 != glob.blocks)
    {
      if (tmp2->is_free == true)
	{
	  free = tmp2;
	  break;
	}
      tmp2 = tmp2->prev;
    }
  tmp->next_free = free->next_free;
  if (tmp != glob.blocks)
    free->next_free = tmp;
  return (tmp);
}

void	fusion(t_malloc *tmp)
{
  tmp->size += tmp->next->size + sizeof(t_malloc);
  tmp->next_free = tmp->next->next_free;
  if (tmp->next == glob.last)
    glob.last = tmp;
  tmp->next = tmp->next->next;
  if (tmp->next)
    tmp->next->prev = tmp;

}

void		free(void *ptr)
{
  t_malloc	*tmp;

  if (ptr == NULL)
    return ;
  pthread_mutex_lock(&glob.mutex);
  if (((long)ptr % 4) != 0)
    {
      write(2, "Pointer not aligned\n", 20);
      pthread_mutex_unlock(&glob.mutex);
      exit(134);
    }
  if ((long)ptr < ((long)glob.blocks + 48) || (long)ptr > (long)sbrk(0))
    {
      pthread_mutex_unlock(&glob.mutex);
      write(2, "Invalid free\n", 13);
      return ;
    }
  tmp = get_free_tmp(ptr);
  tmp->is_free = true;
  if (tmp->next && tmp->next->is_free == true)
      fusion(tmp);
  if (tmp->prev && tmp->prev->is_free == true)
    fusion(tmp->prev);
  pthread_mutex_unlock(&glob.mutex);
}
