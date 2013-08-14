#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<vector>
#include<iterator>
#include<algorithm>
#include<numeric>

#include<assert.h>

#include<omp.h>

#ifndef _cppca_h
#define _cppca_h

using namespace std;

enum border {NORTH, SOUTH, EAST, WEST};
enum corner {NW, NE, SE, SW};

class CA {
public:
  CA(int in_nrows, int ncols); 
  CA(string filename);
  CA(const CA &orig);

  void set_cell(int row, int col, int value);
  int get_cell(int row, int col);
  void dump();
  void fill_random();

  void wrap_boundary();
  void nwrap_boundary();

  void save_state(string filename);
  void read_state(string filename);

  int sum_state();
  vector<int> get_border(border b);
  void set_border(border b, vector<int> new_border);
  int get_corner(corner co);
  void set_corner(corner co, int new_val);
 protected:
  //  int *state_data; // FIXME - this should be private and properly inherited
  //  int *next_state;
  vector<int> state_data;
  vector<int> next_state;
  int nrows, ncols;
  int real_nrows, real_ncols;
};

class CALife: public CA {
public:
 CALife(int in_nrows, int in_ncols) : CA(in_nrows, in_ncols) {}
  CALife(string filename) : CA(filename) {}
  void update();
  //  CALife(int, int);
};

class CAVote: public CA {
public:
  CAVote(int in_nrows, int in_ncols) : CA(in_nrows, in_ncols) {}
  CAVote(string filename) : CA(filename) {}
  void update();
};

#endif
