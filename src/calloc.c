/*
** calloc.c for Project-Master in /home/veyssi_b/rendu/tek2/PSU/PSU_2016_malloc
**
** Made by Baptiste Veyssiere
** Login   <veyssi_b@epitech.net>
**
** Started on  Mon Jan 30 17:20:48 2017 Baptiste Veyssiere
** Last update Mon Feb  6 10:50:28 2017 Nathan Scutari
*/

#include "malloc.h"

void	*calloc(size_t nmemb, size_t size)
{
  void	*ptr;

  if (nmemb == 0 || size == 0 ||
      (ptr = malloc(nmemb * size)) == NULL)
    return (NULL);
  for(size_t i = 0; i < (nmemb * size); ++i)
    *(((char*)ptr) + i) = 0;
  return (ptr);
}
