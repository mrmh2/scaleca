#include"cppca.h"
#include<ctime>
#include<sys/time.h>

#include"omp.h"

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

void time_cavote(int nrows, int ncols)
{
  CAVote cawhole(nrows, ncols);
  cawhole.fill_random();

  int gen_count = 0;
  int count_freq = 10;
  double start = read_timer();

  int tid = omp_get_thread_num();
  while (1) {
    cawhole.update();
    gen_count++;
    if (gen_count%count_freq == 0) {
      double gen_time = (read_timer() - start) / (double) gen_count;
      cout << tid << ": " << gen_time << "ms per generation." << endl;
    }
  }
}

void report(CA *camaster, CA *caup, CA *cadown)
{
  cout << "Checksum: " << camaster->sum_state() << endl;
  cout << caup->sum_state() << "+" << cadown->sum_state() << " = " 
       << caup->sum_state() + cadown->sum_state() << endl;
}

void split_ca_check()
{
  CAVote camaster(4000, 4000);
  srand(0);
  camaster.fill_random();


  int rsplit = 2000;
  int csplit = 4000;

  CAVote caup(rsplit, csplit);
  CAVote cadown(rsplit, csplit);

  vector<int> master_data = camaster.copy_state();

  for(int r = 0; r < rsplit; r++) 
    for(int c = 0; c < csplit; c++) {
      caup.set_cell(r, c, camaster.get_cell(r, c));
      cadown.set_cell(r, c, camaster.get_cell(r + rsplit, c));
    }

  report(&camaster, &caup, &cadown);

  for(int g = 0; g < 5; g++) {
    camaster.raw_update();

    cadown.set_border(NORTH, caup.get_border(SOUTH));
    caup.set_border(SOUTH, cadown.get_border(NORTH));

    caup.raw_update();
    cadown.raw_update();
    report(&camaster, &caup, &cadown);
  }

}

int main(int argc, char *argv[])
{
  split_ca_check();
  // time_cavote(4000, 2000);

  return 0;
}
