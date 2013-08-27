#include"cppca.h"

void create_test_ca(string filename)
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

  ca.save_state(filename);
}

void create_large_vote(string filename)
{
  CAVote ca(3500, 3500);
  srand(0);
  ca.fill_random();

  ca.save_state(filename);
  cout << "Created with sum " << ca.sum_state() << endl;
}

int test_glider(string filename)
{
  CALife ca(10, 10);

  ca.set_cell(5, 5, 1);
  ca.set_cell(5, 4, 1);
  ca.set_cell(5, 6, 1);
  ca.set_cell(4, 6, 1);
  ca.set_cell(3, 5, 1);

  ca.save_state(filename);
}

int main()
{
  create_test_ca("edge-test.cas");
  create_large_vote("vote.cas");
}
