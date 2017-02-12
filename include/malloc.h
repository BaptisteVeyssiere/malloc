/*
** my_malloc.h for my_malloc in /home/scutar_n/rendu/PSU/memory/PSU_2016_malloc
**
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Wed Jan 25 10:51:19 2017 Nathan Scutari
** Last update Sun Feb 12 16:54:00 2017 Baptiste Veyssiere
*/

#ifndef MY_MALLOC_H_
# define MY_MALLOC_H_

#define _GNU_SOURCE

#include <pthread.h>
#include <stdbool.h>
#include <unistd.h>
#include <stdlib.h>

# define align8(x) ((x-1)/8*8+8)
# define alignpagesize(x) ((x-1)/pagesize*pagesize+pagesize)

typedef struct	s_malloc
{
  size_t		size;
  struct s_malloc	*next;
  struct s_malloc	*prev;
  int			is_free;
  void			*block;
  struct s_malloc	*next_free;
}		t_malloc;

typedef struct		s_glob
{
  t_malloc		*blocks;
  t_malloc		*last;
  pthread_mutex_t	mutex;
}			t_glob;

extern t_glob	glob;

int	LongToHex(long);
void	*split_o(t_malloc *block, size_t size, t_malloc *prev_free, int align_size);
void	*split_block(t_malloc *block, size_t size, t_malloc *prev_free);

#endif /* !MY_MALLOC_H_ */
