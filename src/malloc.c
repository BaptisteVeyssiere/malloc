/*
** malloc.c for mall in /home/scutar_n/rendu/PSU/memory/PSU_2016_malloc/src
**
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Mon Jan 30 14:47:14 2017 Nathan Scutari
** Last update Sun Feb 12 16:52:33 2017 Baptiste Veyssiere
*/

#include "malloc.h"

t_glob		glob = { NULL, NULL, PTHREAD_MUTEX_INITIALIZER };

static void	*first_alloc(size_t size)
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
  glob.blocks = tmp;
  glob.last = glob.blocks;
  return (split_block(tmp, size, glob.blocks));
}

static void	*add_alloc(t_malloc *prev, size_t size)
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
  tmp->prev = glob.last;
  glob.last->next = tmp;
  glob.last = tmp;
  tmp->next_free = NULL;
  return (split_block(tmp, size, prev));
}

static void	*find_free_space(t_malloc **prev_free, size_t size)
{
  t_malloc	*tmp;

  tmp = glob.blocks;
  while (tmp)
    {
      if (tmp->is_free == true && align8(tmp->size) >= align8(size))
	{
	  tmp = split_block(tmp, size, *prev_free);
	  break;
	}
      if (tmp->is_free == true)
	*prev_free = tmp;
      tmp = tmp->next_free;
    }
  return (tmp);
}

void	*malloc(size_t size)
{
  t_malloc		*tmp;
  t_malloc		*prev_free;

  if (size > 2000000000)
    return (NULL);
  pthread_mutex_lock(&glob.mutex);
  if (!glob.blocks)
    tmp = first_alloc(size);
  else
    {
      prev_free = glob.blocks;
      if (!(tmp = find_free_space(&prev_free, size)))
	tmp = add_alloc(prev_free, size);
    }
  pthread_mutex_unlock(&glob.mutex);
  return (tmp);
}
