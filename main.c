#include "include/tetris.h"

char **remplir ()
{
  char **tab;
  int i;
  int j;

  i = -1;
  tab = malloc (sizeof(char *) * 24);
  while (++i < 24)
    tab[i] = malloc (sizeof(char) * 11);
  i = -1;
  while (++i < 24)
    {
      j = -1;
      while (++j < 10)
	tab[i][j] = '_';
      tab[i][10] = '\n';
    }
  tab[24] = NULL;
  i = -1;
  return (tab);
}

char **remove_line(char **tab, int line)
{
  int i;

  i = 24;
  while (--i > line);
  ++i;
  while (--i > 0)
    tab[i] = tab[i - 1];
  while (tab[0][++i] != '\n')
    tab[0][i] = '_';
  tab[0][10] = '\n';
  return (tab);
}

char **verif_tab (char **tab)
{
  int i;
  int j;
  int k;

  i = -1;
  while (tab[++i])
    {
      j = -1;
      k = 0;
      while (tab[i][++j] != '\n')
	if (tab[i][j] != '_')
	  ++k;
      if (k == 10)
	tab = remove_line (tab, i);
    }
  return (tab);
}

void		aff_board (char **tab)
{
  int		i;
  int		j;
  
  i = -1;
  mvprintw(0, 0, "==========");
  while (tab[++i])
    {
      j = -1;
      while (tab[i][++j])
	mvprintw(i, j, "%c", tab[i][j]);
    }
}

void		aff_block (t_tetri tetri)
{
  int		x;
  int		y;
  
  x = -1;
  while (++x < tetri.size_x)
    {
      y = -1;
      while (++y < tetri.size_y)
	{
	  mvprintw(tetri.y + y, tetri.x + x, "%c", tetri.block[x][y]);
	}
    }
}

void		fixed_tetri (char **tab, t_tetri tetri)
{
  int		x;
  int		y;
  
  x = -1;
  while (tetri.block[++x])
    {
      y = -1;
      while (tetri.block[x][++y])
	{
	  tab[tetri.y + y][tetri.x + x] = tetri.block[x][y];
	}
    }
}

int		verif_below(char **tab, t_tetri *block, int ch)
{
  int	x;
  int	y;
  int	x_add;

  x = -1;
  x_add = 0;
  if (block->y + block->size_y == 24)
    return (0);
  if (ch == 'j' && block->x > 0)
    x_add = -1;
  else if (ch == 'k' && block->x < 10 - block->size_x)
    x_add = 1;
  while (++x < block->size_x)
    {
      y = -1;
      while (++y < block->size_y)
	if (tab[block->y + y + 1][block->x + x + x_add] != '_' &&
	    block->block[x][y] != '_')
	  return (0);
    }
  return (1);
}

int		main ()
{
  int		ch;
  char		**tab;
  /* t_tetri	hold; */
  t_tetri	tetri;

  initscr();
  tab = remplir ();
  ch = 0;
  timeout(3000);
  srand(time(NULL));
  while ((ch = getch()) != 'q')
    {
      tetri = get_new_tetri();
      verif_tab (tab);
      while (verif_below(tab, &tetri, ch = getch()) == 1 &&
	     ch != 'q')
	{
	  if (ch == 'j' && tetri.x > 0)
	    --tetri.x;
	  else if (ch == 'k' && tetri.x < 10 - tetri.size_x)
	    ++tetri.x;
	  ++tetri.y;
	  aff_board (tab);
	  my_putstr("before\n");
	  aff_block (tetri);
	  my_putstr("after");
	}
      fixed_tetri (tab, tetri);
      refresh();
    }
  endwin();
  return (0);
}
