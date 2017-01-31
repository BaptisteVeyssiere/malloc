/*
** main_test.c for test in /home/scutar_n/rendu/PSU/memory/PSU_2016_malloc/src
**
** Made by Nathan Scutari
** Login   <scutar_n@epitech.net>
**
** Started on  Tue Jan 31 10:22:04 2017 Nathan Scutari
** Last update Tue Jan 31 16:09:21 2017 Nathan Scutari
*/

#include "malloc.h"

int	main()
{
  char		*str;

  malloc(10);
  malloc(500);
  malloc(9753);
  free(malloc(1230));
  malloc(2);
  malloc(9);
  malloc(1000);
  return (0);
}
