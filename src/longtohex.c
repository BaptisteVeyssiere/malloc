/*
** IntToHex.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Jan 30 16:45:52 2017 Baptiste Veyssiere
** Last update Mon Jan 30 17:08:11 2017 Baptiste Veyssiere
*/

#include "malloc.h"

int	LongToHex(long n)
{
  int	i;
  char	buff[10];
  char	hex [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
		  'C', 'D', 'E', 'F' };

  i = 10;
  while (n != 0 && i > 2)
    {
      buff[--i] = hex[n % 16];
      n /= 16;
    }
  while (--i > 1)
    buff[i] = '0';
  buff[1] = 'x';
  buff[0] = '0';
  if (write(1, buff, 10) == -1)
    return (1);
  return (0);
}
