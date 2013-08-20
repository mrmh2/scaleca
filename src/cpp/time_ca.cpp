#include"cppca.h"
#include<ctime>
#include<sys/time.h>
#include<tclap/CmdLine.h>

using namespace std;

double read_timer( )
{
  static bool initialized = false;
  static struct timeval start, end;
  if( !initialized )
    {
      gettimeofday( &start, NULL );
      initialized = true;
    }
  gettimeofday( &end, NULL );
  return (end.tv_sec - start.tv_sec) + 1.0e-6 * (end.tv_usec - start.tv_usec);
}

void test_timing(int nrows, int ncols)
{
  //  CAVote ca(3500, 3500);
  CAVote ca(nrows, ncols);
  ca.fill_random();

  int gen_count = 0;
  int count_freq = 10;
  double start = read_timer();
  while (1) {
    //ca.update();
    ca.inner_update();
    ca.border_update();
    gen_count++;
    if (gen_count%count_freq == 0) {
      double gen_time = (read_timer() - start) / (double) gen_count;
      cout << gen_time << "ms per generation." << endl;
    }
  }
}

int main(int argc, char *argv[])
{
  //test_timing();

  try {
    TCLAP::CmdLine cmd("stuff", ' ', "0.1");

    TCLAP::ValueArg<int> rowsArg("r", "rows", "Number of rows", false, 3000, "int");
    TCLAP::ValueArg<int> colsArg("c", "cols", "Number of cols", false, 3000, "int");

    cmd.add( rowsArg );
    cmd.add( colsArg );

    cmd.parse(argc, argv);

    cout << "Testing timing with " << rowsArg.getValue() << "x" << colsArg.getValue() << endl;

    test_timing(rowsArg.getValue(), colsArg.getValue());

  } catch (TCLAP::ArgException &e) {
    cerr << "error: " << e.error() << " for arg " << e.argId() << endl;
  }
}
