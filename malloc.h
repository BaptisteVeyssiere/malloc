/*
** malloc.h for first fit in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
** 
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
** 
** Started on  Wed Jan 25 10:55:03 2017 Baptiste Veyssiere
** Last update Wed Jan 25 10:57:14 2017 Baptiste Veyssiere
*/

#ifndef MALLOC_H_
# define MALLOC_H_

struct	s_block {
  size_t		size;
  struct s_block	*next;
  struct s_block	*prev;
  int			free;
  void			*ptr;
  char			data[1];
};

#endif /* !MALLOC_H_ */
