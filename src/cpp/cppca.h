#include<iostream>
#include<cstdlib>
#include<ctime>
#include<sys/time.h>

#ifndef _cppca_h
#define _cppca_h

class CA {
public:
  CA(int in_nrows, int ncols); 
  void set(int row, int col, int value);
  int get_cell(int row, int col);
  void dump();
  void fill_random();
  void wrap_boundary();
  //  void save_state(string filename);
 protected:
  int *state_data; // FIXME - this should be private and properly inherited
  int *next_state;
  int nrows, ncols;
  int real_nrows, real_ncols;
};

class CALife: public CA {
public:
 CALife(int in_nrows, int in_ncols) : CA(in_nrows, in_ncols) {}
  void update();
  //  CALife(int, int);
};

class CAVote: public CA {
public:
  CAVote(int in_nrows, int in_ncols) : CA(in_nrows, in_ncols) {}
  void update();
};

#endif
