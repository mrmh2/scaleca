#include"gridmanager.h"


using namespace std;

void dump_vector(vector<int> v)
{
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, ""));
  cout << endl;
}

void test_construct()
{
  int nthreads = 4;
  GridManager gm(4000, 4000, nthreads);

  for(int i = 0; i < nthreads; i++) {
    GridRef gr = gm.TilePosition(i);
    cout << "(" << gr.r << "," << gr.c << ")" << endl;
  }

  cout << gm.TileDimensions() << endl;

  for(int i = 0; i < nthreads; i++) {
    cout << gm.TileSID(gm.TilePosition(i)) << endl;
  }
  
}

void test_neigh()
{
  int nthreads = 9;

  GridManager gm(6000, 6000, nthreads);

  /* 0 1 2
     3 4 5
     6 7 8 */

  for(int i = 0; i < nthreads; i++) {
    cout << gm.NeighbourSID(gm::NORTH, i) << " ";
  }
  cout << endl;

  for(int i = 0; i < nthreads; i++) {
    cout << gm.NeighbourSID(gm::SOUTH, i) << " ";
  }
  cout << endl;

  for(int i = 0; i < nthreads; i++) {
    cout << gm.NeighbourSID(gm::NW, i) << " ";
  }
  cout << endl;

  for(int i = 0; i < nthreads; i++) {
    cout << gm.NeighbourSID(gm::NE, i) << " ";
  }
  cout << endl;

  for(int i = 0; i < nthreads; i++) {
    cout << gm.NeighbourSID(gm::SE, i) << " ";
  }
  cout << endl;

  for(int i = 0; i < nthreads; i++) {
    cout << gm.NeighbourSID(gm::SW, i) << " ";
  }
  cout << endl;

}

int test_31()
{
  int nthreads = 3;
  GridManager gm(3000, 3000, 3);

  cout << gm.GridDimensions() << endl;

  for(int i = 0; i < nthreads; i++) {
    cout << gm.NeighbourSID(gm::EAST, i) << " ";
  }
  cout << endl;
}

// vector<int> factorise(int n)
// {
//   vector<int> factors;
//   for (int i = 1; i <= sqrt(n); i++) {
//     if (n % i == 0) {
//       factors.push_back(i);
//     }
//   }

//   return factors;
// }

// GridRef best_grid_size(int n)
// {
//   assert(n > 0);

//   int f = factorise(n).back();

//   return GridRef(f, n / f);
// }

// void test_factorise()
// {
//   //  dump_vector(factorise(36));
//   // cout << factorise(36).back() << endl;

//   for(int i = 1; i < 16; i++) {
//     cout << best_grid_size(i) << endl;
//   }
// }

int main(int argc, char *argv[])
{
  //  test_factorise();
  //test_31();
  //test_neigh();
  //  test_construct();

  return 0;
}
