/****************************************************************
 * GridManager - tool for managing structured/distributed grids *
 ****************************************************************/

#include<iostream>

using namespace std;

class GridRef {
 public:
  GridRef(int ir, int ic) : r(ir), c(ic) {}
  int r, c;
  friend ostream& operator<<(ostream& os, const GridRef& gr);
};

class GridManager {
 public:
  GridManager(int nrows, int ncols, int nshards);
  int TotalCells();
  GridRef GridDimensions();
  GridRef TileDimensions();
  GridRef TilePosition(int sid);
  int TileSID(GridRef tile_position);
 private:
  int total_rows, total_cols;
  int nshards;
  int grid_rows, grid_cols;

};
