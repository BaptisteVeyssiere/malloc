/*
** free.c for first fit in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
** 
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
** 
** Started on  Wed Jan 25 10:57:32 2017 Baptiste Veyssiere
** Last update Wed Jan 25 12:06:23 2017 Baptiste Veyssiere
*/

#include <stdio.h>
#include <unistd.h>
#include "my_malloc.h"

void	fusion(t_malloc *tmp)
{
  tmp->size += tmp->next->size + sizeof(t_malloc);
  tmp->next = tmp->next->next;
  tmp->next->prev = tmp;
}

void	free(void *ptr)
{
  t_malloc	*tmp;

  tmp = blocks;
  
  /* Vérification de l'alignement */
  if ((long)ptr % 4)
    {
      write(2, "Pointer non-aligned\n", 20);
      return ;
    }

  /* Vérification zone */
  if (ptr < blocks && ptr > sbrk(0))
    {
      write(2, "Pointer out of zone\n", 20);
      return ;
    }
      
  /* Trouver le bon maillon */
  while (tmp && tmp->next)
    {
      if (tmp->ptr == ptr)
	break;
      tmp = tmp->next;
    }

  if (tmp->free == 1)
    {
      write(2, "Double free or corruption\n", 26);
      return ;
    }
  
  tmp->free = 1;
  if (tmp->prev && tmp->prev->free == 1)
    fusion(tmp->prev);
  if (tmp->next && tmp->next->free == 1)
    fusion(tmp);
}
