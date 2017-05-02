#include "include/tetris.h"

t_tetri		get_block (char	*file)
{
  t_tetri	tetri;
  char		*line;
  int		fd;
  int		i;
  int		value;
  tetri.x = 3;
  tetri.y = 0;
  tetri.size_y = 0;
  fd = open(file, O_RDWR);
  while ((line = my_getnextline(fd))[0] != '\n' &&
	 (value = my_strlen(line)) > 1)
    {
      if (tetri.size_y == 0)
	tetri.size_x = my_strlen(line) - 1;
      ++tetri.size_y;
    }
  close(fd);
  tetri.block = malloc(sizeof(char *) * tetri.size_y);
  fd = open(file, O_RDWR);
  i = -1;
  while ((line = my_getnextline(fd))[0])
    tetri.block[++i] = line;
  close(fd);
  return (tetri);
}

void		aff_tetri_debug (t_tetri tetri)
{
  int		i;

  i = -1;
  printf("position x & y = %d & %d\n", tetri.x, tetri.y);
  printf("size x & y = %d & %d\n", tetri.size_x, tetri.size_y);
  printf ("============\n");
  while (++i < tetri.size_y)
    printf("%s\n", tetri.block[i]);
  printf ("============\n");
}

t_tetri		get_new_tetri ()
{
  t_tetri	tetri;
  DIR		*dir;
  struct dirent	*file;
  int		nb_tetri;
  int		i;
  int		rand_value;

  nb_tetri = 0;
  i = -1;
  if ((dir = opendir ("tetriminos")) == NULL)
    return (tetri);
  while ((file = readdir (dir)))
    if (file->d_name[0] != '.')
      ++nb_tetri;
  closedir (dir);
  if ((dir = opendir ("tetriminos")) == NULL)
    return (tetri);
  rand_value = rand() % nb_tetri;
  printf("[%d, %d]", rand_value, nb_tetri);
  while ((file = readdir (dir)))
    if (file->d_name[0] != '.' && ++i == rand_value)
      tetri = get_block (my_stradd("tetriminos/", file->d_name));
  aff_tetri_debug (tetri);
  closedir (dir);
  return (tetri);
}
