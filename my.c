#include "include/tetris.h"

int my_strlen (char *str)
{
  int i;

  i = -1;
  if (!str)
    return (-1);
  while (str[++i] || str[i] != '\0');
  return (i);
}

void my_putstr (char *str)
{
  if (str != NULL)
    write (1, str, my_strlen(str));
}

char *my_stradd (char *strA, char *strB)
{
  char *out;
  int i;
  int j;

  i = -1;
  j = -1;
  if (strA == NULL && strB == NULL)
    return (NULL);
  if (strA == NULL)
    return (strB);
  if (strB == NULL)
    return (strA);
  if (!(out = malloc(sizeof(char) * (my_strlen(strA) * my_strlen(strB) + 1))))
    return (NULL);
  while (strA[++i])
    out[i] = strA[i];
  while (strB[++j])
    {
      out[i] = strB[j];
      ++i;
    }
  return (out);
}

int	str_contain (char *str, char c)
{
  int i;
  int j;

  i = -1;
  j = 0;
  while (str && str[++i])
    if (str[i] == c)
      ++j;
  return (j);
}

char	*remove_first_line (char *str)
{
  char	*out;
  int	i;
  int	j;

  my_putstr("in :");
  my_putstr(str);
  my_putstr("\n"); 
  if ((out = malloc(sizeof(char) * my_strlen(str))) == NULL)
    return (NULL);
  i = -1;
  j = 0;
  while (str[++i] && str[i] != '\n');
  while (str[++i])
    {
      out[j] = str[i];
      ++j;
    }
  my_putstr("out :");
  my_putstr(out);
  my_putstr("\n");
  return (out);
}

char	*to_line (char *str)
{
  char	*out;
  int	i;

 if ((out = malloc(sizeof(char) * my_strlen(str))) == NULL)
    return (NULL);
  i = -1;
  while (str && str[++i] && str[i] != '\n')
    out [i] = str[i];
  out[i] = str[i];
  return (out);
}

char		*my_getnextline (int fd)
{
  static char	*line;
  char		*buffer;
  int		size;
  int		buffer_size;

  buffer_size = 256;
  size = buffer_size;
  if (line == NULL)
    if ((line = malloc(sizeof(char *))) == NULL)
      return (NULL);
  line = remove_first_line (line);
  if ((buffer = malloc(sizeof(char) * buffer_size)) == NULL)
    return (NULL);
  while (str_contain (line, '\n') == 0 && size == buffer_size)
    {
      if ((size = read (fd, buffer, buffer_size)) < 0)
	return (NULL);
      buffer[size - 1] = '\0';
      line = my_stradd (line, buffer);
    }
  return (to_line (line));
}
