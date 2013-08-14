#include"cppca.h"
#include<ctime>
#include<sys/time.h>

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

void test_timing()
{
  CAVote ca(3500, 3500);
  ca.fill_random();

  int gen_count = 0;
  int count_freq = 10;
  double start = read_timer();
  while (1) {
    ca.update();
    gen_count++;
    if (gen_count%count_freq == 0) {
      double gen_time = (read_timer() - start) / (double) gen_count;
      cout << gen_time << "ms per generation." << endl;
    }
  }
}

int main()
{
  test_timing();
}
