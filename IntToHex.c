#include <unistd.h>

int	IntToHex(long n)
{
  int	i;
  int	r;
  char	buff[11];
  char	hex [] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B',
		  'C', 'D', 'E', 'F' };

  i = 10;
  buff[10] = '\n';
  while (n != 0 && i > 2)
    {
      buff[--i] = hex[n % 16];
      n /= 16;
    }
  while (--i > 1)
    buff[i] = '0';
  buff[1] = 'x';
  buff[0] = '0';
  if (write(1, buff, 11) == -1)
    return (1);
  return (0);
}
