/*
** show_alloc_mem.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Jan 30 17:13:51 2017 Baptiste Veyssiere
** Last update Thu Feb  2 15:39:22 2017 Nathan Scutari
*/

#include "malloc.h"

void	my_put_nbr(int nbr)
{
  if (nbr >= 10)
    my_put_nbr(nbr / 10);
  nbr = nbr % 10 + 48;
  write(1, &nbr, 1);
}

void	show_alloc_mem()
{
  t_malloc	*tmp;

  tmp = glob.blocks;
  LongToHex((long)sbrk(0));
  write(1, "\n", 1);
  while (tmp != NULL)
    {
      if (!tmp->is_free || tmp->is_free)
	{
	  LongToHex((long)tmp->block);
	  write(1, " - ", 3);
	  LongToHex((long)((char*)tmp->block + tmp->size));
	  write(1, ": ", 2);
	  my_put_nbr(tmp->size);
	  write(1, " bytes", 7);
	  if (tmp->is_free)
	    write(1, " F\n", 3);
	  else
	    write(1, " M\n", 3);
	}
      tmp = tmp->next;
    }
}
