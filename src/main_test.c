/*
** main_test.c for test in /home/scutar_n/rendu/PSU/memory/PSU_2016_malloc/src
**
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Tue Jan 31 10:22:04 2017 Nathan Scutari
** Last update Tue Jan 31 12:23:46 2017 Baptiste Veyssiere
*/

#include "malloc.h"

int	main()
{
  char		*str;

  for (int i = 0; i < 100000; ++i)
    str = malloc(2);
  free(str);
  if ((str == malloc(2)))
    write(1, "lol ca marche\n", 15);
  return (0);
}
