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

  while (1) {
    cawhole.update();
    gen_count++;
    if (gen_count%count_freq == 0) {
      double gen_time = (read_timer() - start) / (double) gen_count;
      cout << gen_time << "ms per generation." << endl;
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

void dump_vector(vector<int> v)
{
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, ""));
  cout << endl;
}

void split_ca_omp()
{
  int nrows = 4000, ncols = 4000;
  CAVote camaster(nrows, ncols);
  srand(0);
  camaster.fill_random();

  //  camaster.dump();

  int rsplit = nrows / 2;
  int csplit = ncols;

  vector<int> master_data = camaster.copy_state();
  vector<int> border_exchange1(2 * csplit, 0);
  vector<int> border_exchange2(2 * csplit, 0);
  vector<int> border_exchange3(2 * rsplit, 0);
  vector<int> border_exchange4(2 * rsplit, 0);

#pragma omp parallel shared(master_data, rsplit, csplit)
  {
    int tid = omp_get_thread_num();
    CAVote cashard(rsplit, csplit);

    for(int r = 0; r < rsplit; r++) 
      for(int c = 0; c < csplit; c++) {
	cashard.set_cell(r, c, camaster.get_cell(r + tid * rsplit, c));
      }

    printf("%d: I have %d\n", tid, cashard.sum_state());

    // int gen_count = 0;
    // int count_freq = 10;
    // double start = read_timer();
    //  while(1) {
    for(int g = 0; g < 1; g++) {
      vector<int> nb = cashard.get_border(NORTH);
      vector<int> sb = cashard.get_border(SOUTH);
      vector<int> wb = cashard.get_border(WEST);
      vector<int> eb = cashard.get_border(EAST);
      // Populate north/south border exchange vectors
      for(int i=0;i<ncols;i++) {
	border_exchange1[i + tid * ncols] = nb[i];
	border_exchange2[i + tid * ncols] = sb[i];
      }
      // Populate east/west border exchange vectors
      for(int i = 0; i < rsplit; i++) {
	border_exchange3[i + tid * rsplit] = wb[i];
	border_exchange4[i + tid * rsplit] = eb[i];
      }
#pragma omp barrier /* Make sure we've filled our exchange vectors */
      /* Read our new north/south borders */
      for(int i = 0; i < ncols; i++) {
	sb[i] = border_exchange1[i + (1 - tid) * ncols];
	nb[i] = border_exchange2[i + (1 - tid) * ncols];
      }
      
      /* Read our new east/west borders */
      for(int i = 0; i < rsplit; i++) {
	eb[i] = border_exchange3[i + (1 - tid) * rsplit];
	wb[i] = border_exchange4[i + (1 - tid) * rsplit];
      }

      //if (tid == 1 ) dump_vector(sb);
      cashard.set_border(SOUTH, sb);
      cashard.set_border(NORTH, nb);
      cashard.set_border(EAST, eb);
      cashard.set_border(WEST, wb);
      //    if (tid == 1 ) cashard.dump();

      cashard.raw_update();

      // if (tid == 0) {
      // 	gen_count++;
      // 	if (gen_count%count_freq == 0) {
      // 	  double gen_time = (read_timer() - start) / (double) gen_count;
      // 	  cout << gen_time << "ms per generation." << endl;
      // 	}
      // } /* timing block */
      printf("%d: I have %d\n", tid, cashard.sum_state());
    }

  }

  //  dump_vector(border_exchange1);
  //  dump_vector(border_exchange2);

  CAVote caup(rsplit, csplit);
  CAVote cadown(rsplit, csplit);

  for(int r = 0; r < rsplit; r++) 
    for(int c = 0; c < csplit; c++) {
      caup.set_cell(r, c, camaster.get_cell(r, c));
      cadown.set_cell(r, c, camaster.get_cell(r + rsplit, c));
    }

  report(&camaster, &caup, &cadown);

  // int gen_count = 0;
  // int count_freq = 10;
  // double start = read_timer();


  //  while (1) {
  for(int g = 0; g < 1; g++) {
    camaster.raw_update();

    cadown.set_border(NORTH, caup.get_border(SOUTH));
    caup.set_border(SOUTH, cadown.get_border(NORTH));

    cadown.set_border(SOUTH, caup.get_border(NORTH));
    caup.set_border(NORTH, cadown.get_border(SOUTH));

    cadown.set_border(WEST, caup.get_border(EAST));
    caup.set_border(EAST, cadown.get_border(WEST));

    cadown.set_border(EAST, caup.get_border(WEST));
    caup.set_border(WEST, cadown.get_border(EAST));

    //    cadown.dump();

    caup.raw_update();
    cadown.raw_update();
    report(&camaster, &caup, &cadown);

    // gen_count++;
    // if (gen_count%count_freq == 0) {
    //   double gen_time = (read_timer() - start) / (double) gen_count;
    //   cout << gen_time << "ms per generation." << endl;
    // }

  }

}

int main(int argc, char *argv[])
{
  split_ca_omp();
  //  time_cavote(4000, 4000);

  return 0;
}
