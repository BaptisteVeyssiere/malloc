/*
** free.c for first fit in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
** 
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
** 
** Started on  Wed Jan 25 10:57:32 2017 Baptiste Veyssiere
** Last update Thu Jan 26 12:44:26 2017 Baptiste Veyssiere
*/

#include "my_malloc.h"

void	fusion(t_malloc *tmp)
{
  tmp->size += tmp->next->size + sizeof(t_malloc);
  tmp->next = tmp->next->next;
  if (tmp->next)
    tmp->next->prev = tmp;
}

void	free(void *ptr)
{
  t_malloc	*tmp;

  tmp = blocks;

  if (!ptr)
    return ;
  if ((long)ptr % (long)4)
    {
      write(2, "Pointer non-aligned\n", 20);
      return ;
    }
  if ((void*)ptr < (void*)blocks || (void*)ptr > (void*)sbrk(0))
    {
      write(2, "Pointer out of zone\n", 20);
      return ;
    }
  while (tmp)
    {
      if (tmp->block == ptr)
	break;
      tmp = tmp->next;
    }
  if (!tmp)
    return ;
  
  if (tmp->is_free == 1)
    {
      write(2, "Double free or corruption\n", 26);
      return ;
    }  
  tmp->is_free = 1;
  if (tmp->prev && tmp->prev->is_free == 1)
    fusion(tmp->prev);
  if (tmp->next && tmp->next->is_free == 1)
    fusion(tmp);
}
