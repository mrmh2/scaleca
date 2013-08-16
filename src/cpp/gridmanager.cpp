#include"gridmanager.h"

GridManager::GridManager(int nrows, int ncols, int nshards) :
  total_rows(nrows),
  total_cols(ncols),
  nshards(nshards)
{
  // TODO - do this properly!
  switch (nshards) {
  case 4:
    grid_rows = 2;
    grid_cols = 2;
    break;
  case 6:
    grid_rows = 2;
    grid_cols = 3;
  }
}

int GridManager::TotalCells()
{
  return total_rows * total_cols;
}

GridRef GridManager::GridDimensions()
{
  return GridRef(grid_rows, grid_cols);
}

GridRef GridManager::TileDimensions()
{
  int r = total_rows / grid_rows;
  int c = total_cols / grid_cols;

  return GridRef(r, c);
}

GridRef GridManager::TilePosition(int sid)
{
  int c = sid % grid_cols;
  int r = sid / grid_cols;

  return GridRef(r, c);
}

int GridManager::TileSID(GridRef tile_position)
{
  int r = tile_position.r;
  int c = tile_position.c;

  return c + r * grid_cols;
}

ostream& operator<<(ostream& os, const GridRef& gr)
{
  os << "(" << gr.r << "," << gr.c << ")";
  return os;
}
