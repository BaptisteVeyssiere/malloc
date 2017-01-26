/*
** realloc.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
** 
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
** 
** Started on  Thu Jan 26 12:38:06 2017 Baptiste Veyssiere
** Last update Thu Jan 26 13:17:09 2017 Baptiste Veyssiere
*/

#include "my_malloc.h"

t_malloc	*check_realloc(void *ptr)
{
  t_malloc	*tmp;

  tmp  = blocks;
  
  if (!ptr)
    return (NULL);
  if ((long)ptr % (long)4)
    {
      write(2, "Pointer non-aligned\n", 20);
      return NULL;
    }
  if ((void*)ptr < (void*)blocks || (void*)ptr > (void*)sbrk(0))
    {
      write(2, "Pointer out of zone\n", 20);
      return NULL;
    }
  while (tmp)
    {
      if (tmp->block == ptr)
	break;
      tmp = tmp->next;
    }
  if (!tmp)
    return NULL;
  return (tmp);
}

void	*realloc(void *ptr, size_t size)
{
  t_malloc	*tmp;
  void		*ret;

  if (!(tmp = check_realloc(ptr)))
    return NULL;
  free(tmp->block);
  if (!(ret = malloc(size)))
    return (NULL);
  if (tmp->block == ret)
    return (ret);
  for (unsigned int i = 0; i < tmp->size; ++i)
    *((char*)ret + i) = *((char*)(tmp->block) + i);
  return (ret);
}
