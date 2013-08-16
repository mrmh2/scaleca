#include"gridmanager.h"

using namespace std;

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

int main(int argc, char *argv[])
{
  test_construct();

  return 0;
}
