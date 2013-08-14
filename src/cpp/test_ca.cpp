#include"cppca.h"
#include<ctime>
#include<sys/time.h>
#include<assert.h>

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
  ca.set_cell(5, 5, 1);
  ca.set_cell(5, 4, 1);
  ca.set_cell(5, 6, 1);
  ca.set_cell(4, 6, 1);
  ca.set_cell(3, 5, 1);
  //  ca.fill_random();
  ca.dump();
  for (int i=0; i<150; i++) {
    ca.update();
    ca.dump();
    cout << ca.sum_state() << endl;
  }
}

void test_wrap()
{
  CA ca(5, 5);
  ca.set_cell(0, 0, 1);
  ca.set_cell(0, 2, 2);
  ca.set_cell(0, 4, 3);
  ca.set_cell(2, 0, 4);
  ca.set_cell(2, 4, 5);
  ca.set_cell(4, 0, 6);
  ca.set_cell(4, 2, 7);
  ca.set_cell(4, 4, 8);
  ca.dump();
  ca.wrap_boundary();
  ca.dump();

}

void test_vote()
{
  CAVote ca(10, 10);
  srand(time(0));
  //  ca.fill_random();

  ca.set_cell(5, 5, 1);
  ca.set_cell(5, 6, 1);
  ca.set_cell(6, 5, 1);
  ca.set_cell(6, 6, 1);
  ca.dump();
  //  for (int i=0;i<10;i++) {
    ca.update();
    //    static_update(ca);
    ca.dump();			
    //  }
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

void test_save_state()
{
  CAVote ca(10, 10);
  srand(0);
  ca.fill_random();
  ca.dump();
  ca.save_state("vstate.cas");
}
    
void test_read_state()
{
  CAVote ca(10, 10);

  ca.read_state("vstate.cas");
  ca.dump();
}

void test_construct_from_file()
{
  CAVote ca("vstate.cas");
  ca.dump();
}

void test_life()
{
  CALife ca(5, 5);
  ca.set_cell(1, 2, 1);
  ca.set_cell(2, 2, 1);
  ca.set_cell(3, 2, 1);
  ca.dump();
  ca.update();
  ca.dump();

  assert(ca.sum_state() == 3);
}

void test_copy()
{
  CALife original("glider.cas");
  original.dump();
  CALife cacopy = original;
  cacopy.dump();
}

void create_large_vote()
{
  CAVote ca(3500, 3500);
  ca.fill_random();
  ca.save_state("vote-3k5-3k5.cas");
  cout << "Created with sum " << ca.sum_state() << endl;
}

int main(int argc, char *argv[])
{
  //  create_large_vote();
  // test_wrap();

  //  test_copy();
  test_vote();
    //  test_dump();

  //test_timing();
  //test_save_state();
  //  test_read_state();
  //  test_construct_from_file();
  //test_life();
  return 0;
}
