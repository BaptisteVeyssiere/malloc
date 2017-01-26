/*
** my_malloc.c for malloc in /home/scutar_n/rendu/PSU/memory/PSU_2016_malloc
** 
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
** 
** Started on  Wed Jan 25 10:56:02 2017 Nathan Scutari
** Last update Thu Jan 26 13:12:37 2017 Baptiste Veyssiere
*/

#include <unistd.h>
#include <stdio.h>
#include "my_malloc.h"

t_malloc	*blocks = NULL;

static void	my_put_nbr(int nbr)
{
  if (nbr >= 10)
    my_put_nbr(nbr / 10);
  nbr = nbr % 10 + 48;
  write(1, &nbr, 1);
}

static void	*first_alloc(size_t size)
{
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

static void	*split_block(t_malloc *tmp, size_t size)
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
    return (NULL);
  if (blocks == NULL)
    return (first_alloc(size));
  tmp = blocks;
  while (tmp != NULL)
    {
      if (tmp->size >= align8(size) && tmp->is_free)
	return (split_block(tmp, align8(size)));
      save = tmp;
      tmp = tmp->next;
    }
  return (add_allocation(save, size));
}

void	show_alloc_mem()
{
  t_malloc	*tmp;

  tmp = blocks;
  IntToHex((long)sbrk(0));
  write(1, "\n", 1);
  while (tmp != NULL)
    {
      if (!tmp->is_free || tmp->is_free)
	{
	  IntToHex((long)tmp);
	  write(1, " - ", 3);
	  IntToHex((long)((void*)tmp + tmp->size));
	  write(1, ": ", 2);
	  my_put_nbr(tmp->size);
	  write(1, " bytes\n", 7);
	}
      tmp = tmp->next;
    }
}

int	main()
{
  char	*str;

  str = malloc(100);
  str[0] = str[1] = '4';
  str = realloc(str, 4);
  write(1, &str[0], 1);
  write(1, &str[1], 1);
  write(1, "\n", 1);
  my_put_nbr(sizeof(t_malloc));
  show_alloc_mem();
  return (0);
}
