/*
** my_malloc.h for my_malloc in /home/scutar_n/rendu/PSU/memory/PSU_2016_malloc
**
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Wed Jan 25 10:51:19 2017 Nathan Scutari
** Last update Mon Jan 30 17:25:55 2017 Baptiste Veyssiere
*/

#ifndef MALLOC_H_
# define MALLOC_H_

#define _GNU_SOURCE

#include <unistd.h>
#include <stdlib.h>

# define align8(x) ((x-1)/8*8+8)

int	LongToHex(long);

typedef struct	s_malloc
{
  size_t		size;
  struct s_malloc	*next;
  struct s_malloc	*prev;
  int			is_free;
  void			*block;
  char			data[1];
}		t_malloc;

extern t_malloc	*blocks;

#endif /* !MALLOC_H_ */
