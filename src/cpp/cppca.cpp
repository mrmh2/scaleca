#include<iostream>
#include<cstdlib>

using namespace std;

class CA {
public:
  CA(int in_nrows, int ncols); 
  void set(int row, int col, int value);
  void dump();
  void fill_random();
  int *state_data; // FIXME - this should be private and properly inherited
  int *next_state;
  int nrows, ncols;
  int real_nrows, real_ncols;
  void wrap_boundary();
};


class CALife: public CA {
public:
  CALife(int in_nrows, int in_ncols) : CA(in_nrows, in_ncols)
  {
  }
  void update();
  //  CALife(int, int);
};

class CAVote: public CA {
public:
  CAVote(int in_nrows, int in_ncols) : CA(in_nrows, in_ncols) {}
  void update();
};


void CALife::update()
{
  int h8[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

  wrap_boundary();

  for(int r=0; r<nrows; r++)
    for(int c=0; c<ncols; c++) {
      int nsum = 0;
      for (int i=0; i<8; i++) {
	int ro = h8[i][0];
	int co = h8[i][1];
	nsum += state_data[(1 + c + co) + (1 + r + ro) * real_ncols];
      }
      next_state[(1 + c) + (1 + r) * real_ncols] = (nsum == 3 || (nsum == 2 && state_data[(1 + c) + (1 + r) * real_ncols]));
    }

  swap(next_state, state_data);


}

CA::CA(int in_nrows, int in_ncols) : nrows(in_nrows)
{
  //  nrows = in_nrows;
  ncols = in_ncols;

  real_nrows = in_nrows + 2;
  real_ncols = in_ncols + 2;
  
  cout << "Constructing " << nrows << "x" << ncols << endl;

  state_data = new int[real_nrows * real_ncols]();
  next_state = new int[real_nrows * real_ncols]();
  //state_data = (int *) malloc(sizeof(int) * (nrows + 2) * (ncols + 2));
  //  memset(state_data, 0, sizeof(int) * (nrows + 2) * (ncols + 2));
}

void CA::set(int row, int col, int value)
{
  int crow = row + 1;
  int ccol = col + 1;

  state_data[crow * real_ncols + ccol] = value;
}
  

void CA::dump()
{
  // Dump CA state to terminal, including border regions

  // Top row of ghost region
  cout << state_data[0] << "|";
  for(int c=1; c<ncols + 1; c++) cout << state_data[c];
  cout << "|" << state_data[real_ncols-1] << endl;

  // Separator (purely visual)
  cout << "-+";
  for(int c=1; c<ncols + 1; c++) cout << "-";
  cout << "+-" << endl;

  // Main part of CA state
  for(int r=1; r<nrows + 1; r++) {
    cout << state_data[r * real_ncols] << "|";
    for(int c=1; c<ncols + 1; c++) {
      cout << state_data[c + r * (ncols + 2)];
    }
    cout << "|" << state_data[ncols + 1 + (r * real_ncols)] << endl;
  }

  // Lower separator (visual again)
  cout << "-+";
  for(int c=1; c<ncols + 1; c++) cout << "-";
  cout << "+-" << endl;

  // Bottom row of ghost region
  cout << state_data[(real_nrows - 1) * real_ncols] << "|";
  for(int c=1; c<ncols + 1; c++) cout << state_data[c + (real_nrows - 1) * real_ncols];
  cout << "|" << state_data[(real_ncols - 1) + (real_nrows - 1) * real_ncols] << endl;

  cout << endl;
}

void CA::fill_random()
{
  for(int r=0; r<nrows; r++) 
    for(int c=0; c<ncols; c++)
      state_data[1 + c + (r + 1) * (real_ncols)] = rand() % 2;
}

void CA::wrap_boundary()
{
  /* Implement wrapped bounday conditions by setting top row of ghost region
     to bottom row of CA state and so on */
     
  // Bottom row of ghost region
  for(int c=1; c<ncols+1; c++) {
    state_data[c + (real_nrows - 1) * real_ncols] = state_data[c + real_ncols];
  }

  // Top row of ghost region
  for(int c=1; c<ncols+1; c++) {
     state_data[c] = state_data[c + (nrows) * real_ncols];
  }

  // Left column of ghost region
  for(int r=1; r<nrows+1; r++) {
    state_data[r * real_ncols] = state_data[(ncols) + r * real_ncols];
  }

  // Right column of ghost region
  for(int r=1; r<nrows+1; r++) {
    state_data[real_ncols - 1 + r * real_ncols] = state_data[1 + r * real_ncols];
  }


  // Top left corner
  state_data[0] = state_data[ncols + nrows * real_ncols];

  // Bottom right corner
  state_data[(real_ncols - 1) + (real_nrows - 1) * real_ncols] = state_data[1 + real_ncols];

  // Top right corner
  state_data[real_ncols - 1] = state_data[1 + (real_nrows - 2) * real_ncols];

  // Bottom left corner
  state_data[(real_nrows - 1) * real_ncols] = state_data[(real_ncols - 2) + real_ncols];

}

int test_glider()
{
  CALife ca(10, 10);
  ca.dump();
  ca.set(5, 5, 1);
  ca.set(5, 4, 1);
  ca.set(5, 6, 1);
  ca.set(4, 6, 1);
  ca.set(3, 5, 1);
  //  ca.fill_random();
  ca.dump();
  for (int i=0; i<150; i++) {
    ca.update();
    ca.dump();
  }
}

void test_wrap()
{
  CALife ca(15, 15);
  srand(time(0));
  ca.fill_random();
  ca.dump();
  ca.wrap_boundary();
  ca.dump();

}

int main(int argc, char *argv[])
{
  test_glider();
  return 0;
}
