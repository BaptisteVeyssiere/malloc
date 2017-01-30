/*
** show_alloc_mem.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Jan 30 17:13:51 2017 Baptiste Veyssiere
** Last update Mon Jan 30 17:28:37 2017 Baptiste Veyssiere
*/

#include "malloc.h"

static void	my_put_nbr(int nbr)
{
  if (nbr >= 10)
    my_put_nbr(nbr / 10);
  nbr = nbr % 10 + 48;
  write(1, &nbr, 1);
}

void	show_alloc_mem()
{
  t_malloc	*tmp;

  tmp = blocks;
  LongToHex((long)sbrk(0));
  write(1, "\n", 1);
  while (tmp != NULL)
    {
      if (!tmp->is_free)
	{
	  LongToHex((long)tmp);
	  write(1, " - ", 3);
	  LongToHex((long)((char*)tmp + tmp->size));
	  write(1, ": ", 2);
	  my_put_nbr(tmp->size);
	  write(1, " bytes\n", 7);
	}
      tmp = tmp->next;
    }
}
