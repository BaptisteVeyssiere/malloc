/*
** realloc.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
** 
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
** 
** Started on  Thu Jan 26 12:38:06 2017 Baptiste Veyssiere
** Last update Fri Jan 27 12:00:07 2017 Baptiste Veyssiere
*/

#include "my_malloc.h"

t_malloc	*check_realloc(void *ptr)
{
  t_malloc	*tmp;

  tmp  = blocks;

  if ((long)ptr % (long)4)
    {
      write(2, "Pointer non-aliaaagned\n", 20);
      return (NULL);
    }
  if ((void*)ptr < (void*)blocks || (void*)ptr > (void*)sbrk(0))
    {
      write(2, "Pointer out of zonaaae\n", 20);
      return (NULL);
    }
  while (tmp)
    {
      if (tmp->block == ptr)
	break;
      tmp = tmp->next;
    }
  if (!tmp)
    return (NULL);
  return (tmp);
}

void	*realloc(void *ptr, size_t size)
{
  t_malloc	*tmp;
  void		*ret;

  if (ptr == NULL)
    return (malloc(size));
  else if (size == 0)
    {
      free(ptr);
      return (NULL);
    }
  
  if ((tmp = check_realloc(ptr)) == NULL)
    return (NULL);
  if ((ret = malloc(size)) == NULL)
    return (ptr);
  free(tmp->block);
  if (tmp->block == ret)
    return (ret);
  for (unsigned int i = 0; i < tmp->size; ++i)
    *((char*)ret + i) = *((char*)(tmp->block) + i);
  return (ret);
}
