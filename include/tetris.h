#ifndef TETRIS_H_
# define TETRIS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ncurses.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>

typedef struct s_tetri
{
  char		**block;
  int		x;
  int		y;
  int		size_x;
  int		size_y;
}		t_tetri;

int	my_strlen(char *str);
void	my_putstr(char *str);
char	*my_stradd (char *strA, char *strB);
char	*my_getnextline (int fd);
t_tetri	get_new_tetri ();
#endif /* !TETRIS_H_ */
