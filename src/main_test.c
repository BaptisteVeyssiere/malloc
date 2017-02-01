/*
** main_test.c for test in /home/scutar_n/rendu/PSU/memory/PSU_2016_malloc/src
**
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Tue Jan 31 10:22:04 2017 Nathan Scutari
** Last update Wed Feb  1 10:30:37 2017 Nathan Scutari
*/

#include "malloc.h"

void	show_free_mem(void)
{
  t_malloc	*tmp;
  int			i;

  tmp = blocks;
  i = 0;

  write(1, "\nFree List:\n", 12);
  while (tmp)
    {
      ++i;
      if (i == 1)
	write(1, "blocks: ", 8);
      LongToHex((long)tmp + 48);
      write(1, "\n", 1);
      tmp = tmp->next_free;
      if (i > 10)
	return ;
    }
  write(1, "End of list\n\n", 13);
}

int	main()
{
  char		*str;
  char		*str2;
  char		*str3;
  char		*str4;

  str = malloc(552);
  str2 = malloc(120);
  str3 = malloc(1024);
  free(str2);
  free(str3);
  free(str);
  str = malloc(5);
  free(str);
  str = malloc(552);
  str2 = malloc(4096);
  str3 = malloc(1600);
  str4 = malloc(1024);
  free(str4);
  str4 = malloc(2048);
  free(str2);
  free(str);
  str = malloc(5);
  free(str);
  str = malloc(45);
  free(str);
  malloc(45);
  malloc(72);
  malloc(40);
  malloc(56);
  malloc(37);
  malloc(48);
  malloc(42);
  return (0);
}
