#include<iostream>

using namespace std;

class CA {
public:
  CA(int nrows, int ncols);
  set(int row, int col);
  void dump();
private:
  int *state_data;
  int nrows, ncols;
};

CA::CA(int in_nrows, int in_ncols)
{
  nrows = in_nrows;
  ncols = in_ncols;
  cout << "Constructing " << nrows << "x" << ncols << endl;
  state_data = (int *) malloc(sizeof(int) * (nrows + 2) * (ncols + 2));
  memset(state_data, 0, sizeof(int) * (nrows + 2) * (ncols + 2));
}

void CA::set(int row, int col, int value)
{
  //  state
}
  

void CA::dump()
{
  for(int r=1; r<nrows + 1; r++) {
    for(int c=1; c<ncols + 1; c++) {
      cout << state_data[c + r * (ncols + 2)];
    }
    cout << endl;
  }

}


int main(int argc, char *argv[])
{
  CA ca(10, 10);
  ca.dump();
  return 0;
}
