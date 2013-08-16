#include"gridmanager.h"

GridManager::GridManager(int nrows, int ncols, int nshards) :
  total_rows(nrows),
  total_cols(ncols),
  nshards(nshards)
{
  // TODO - do this properly!
  switch (nshards) {
  case 2:
    grid_rows = 2;
    grid_cols = 1;
    break;
  case 3:
    grid_rows = 1;
    grid_cols = 3;
    break;
  case 4:
    grid_rows = 2;
    grid_cols = 2;
    break;
  case 6:
    grid_rows = 2;
    grid_cols = 3;
    break;
  case 9:
    grid_rows = 3;
    grid_cols = 3;
    break;
  case 16:
    grid_rows = 4;
    grid_cols = 4;
    break;
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

int GridManager::NeighbourSID(gm::grid_neighbour neigh, int sid)
{
  int no[8][2] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1}, {-1, -1}, {-1, 1}, {1, 1}, {1, -1} };

  int row_offset = no[neigh][0];
  int col_offset = no[neigh][1];

  GridRef tile_pos = TilePosition(sid);

  // We add grid_rows or grid_cols to make modulo arithmetic work with negative
  // offsets.
  int neigh_r = (grid_rows + tile_pos.r + row_offset) % grid_rows;
  int neigh_c = (grid_cols + tile_pos.c + col_offset) % grid_cols;

  //  cout << "nr: " << neigh_r << "nc: " << neigh_c << endl;
  
  return TileSID(GridRef(neigh_r, neigh_c));
}

ostream& operator<<(ostream& os, const GridRef& gr)
{
  os << "(" << gr.r << "," << gr.c << ")";
  return os;
}

bool operator==(const GridRef &gr1, const GridRef &gr2) {
  return (gr1.r == gr2.r && gr1.c == gr2.c);
}

GridRef operator+(const GridRef &gr1, const GridRef &gr2) {
  return GridRef(gr1.r + gr2.r, gr1.c + gr2.c);
}
