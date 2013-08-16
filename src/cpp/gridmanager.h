/****************************************************************
 * GridManager - tool for managing structured/distributed grids *
 ****************************************************************/

#include<iostream>

#ifndef _GRIDMANAGER_H
#define _GRIDMANAGER_H

using namespace std;

namespace gm {
  enum grid_neighbour {NORTH, SOUTH, WEST, EAST, NW, NE, SE, SW};
}

class GridRef {
 public:
  GridRef(int ir, int ic) : r(ir), c(ic) {}
  int r, c;
  friend ostream& operator<<(ostream& os, const GridRef& gr);
  friend bool operator==(const GridRef &gr1, const GridRef &gr2);
  friend GridRef operator+(const GridRef &gr1, const GridRef &gr2);
};

class GridManager {
 public:
  GridManager(int nrows, int ncols, int nshards);
  int TotalCells();
  GridRef GridDimensions();
  GridRef TileDimensions();
  GridRef TilePosition(int sid);
  int TileSID(GridRef tile_position);
  int NeighbourSID(gm::grid_neighbour neigh, int sid);
 private:
  int total_rows, total_cols;
  int nshards;
  int grid_rows, grid_cols;

};

#endif
