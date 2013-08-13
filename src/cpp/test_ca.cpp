#include"cppca.h"

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

void test_vote()
{
  CAVote ca(900, 1200);
  srand(time(0));
  ca.fill_random();
  //  ca.dump();

  for (int i=0;i<10;i++) {
    ca.update();
    //    static_update(ca);
    //    ca.dump();			
  }
}


void test_dump()
{
  CAVote ca(10, 10);
  //srand(time(0));
  ca.fill_random();
  ca.dump();
  ca.wrap_boundary();
  ca.dump();

}

void test_timing(){
  CAVote ca(1000, 1000);
  ca.fill_random();

  int gen_count = 0;
  double start = read_timer();
  while (1) {
    ca.update();
    gen_count++;
    if (gen_count%50 == 0) {
      double gen_time = (read_timer() - start) / (double) gen_count;
      cout << gen_time << "ms per generation." << endl;
    }
  }
}
    
int main(int argc, char *argv[])
{
  //  test_glider();
  //  test_vote();
    //  test_dump();

  test_timing();
  return 0;
}
