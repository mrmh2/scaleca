#include<iostream>
#include<ctime>
#include<sys/time.h>
#include<mpi.h>

#include"cppca.h"
#include"gridmanager.h"

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

void dump_vector(vector<int> v)
{
  copy(v.begin(), v.end(), ostream_iterator<int>(cout, ""));
  cout << endl;
}

void mpi_ca(int nrows, int ncols, int sid, int nshards)
{
  CAVote camaster(nrows, ncols);
  srand(0);
  camaster.fill_random();

  //  if (sid == 0) camaster.dump();

  GridManager gm(nrows, ncols, nshards);
  int snrows = gm.TileDimensions().r;
  int sncols = gm.TileDimensions().c;
  int tr = gm.TilePosition(sid).r;
  int tc = gm.TilePosition(sid).c;

  CAVote cashard(snrows, sncols);

  // Populate our shard with data from the master
  for(int r = 0; r < snrows; r++) 
    for(int c = 0; c < sncols; c++) {
      cashard.set_cell(r, c, 
		       camaster.get_cell(r + tr * snrows, c + tc * sncols));
    }

  int gen_count = 0;
  int count_freq = 10;
  double start = read_timer();

  for(int g = 0; g < 10; g++) {
    vector<int> border_n = cashard.get_border(NORTH);
    vector<int> border_s = cashard.get_border(SOUTH);
    vector<int> border_w = cashard.get_border(WEST);
    vector<int> border_e = cashard.get_border(EAST);
    vector<int> new_border_n(sncols);
    vector<int> new_border_s(sncols);
    vector<int> new_border_w(snrows);
    vector<int> new_border_e(snrows);
    int my_n = gm.NeighbourSID(gm::NORTH, sid);
    int my_s = gm.NeighbourSID(gm::SOUTH, sid);
    int my_w = gm.NeighbourSID(gm::WEST, sid);
    int my_e = gm.NeighbourSID(gm::EAST, sid);

    int my_nw = gm.NeighbourSID(gm::NW, sid);
    int my_ne = gm.NeighbourSID(gm::NE, sid);
    int my_se = gm.NeighbourSID(gm::SE, sid);
    int my_sw = gm.NeighbourSID(gm::SW, sid);

    //  if (sid == 0) cout << "My NW is " << my_nw << endl;

    int corner_nw = cashard.get_corner(NW);
    int corner_ne = cashard.get_corner(NE);
    int corner_se = cashard.get_corner(SE);
    int corner_sw = cashard.get_corner(SW);
    int new_corner_nw, new_corner_ne, new_corner_se, new_corner_sw;

    MPI_Request req[16];
    MPI_Status stats[16];

    MPI_Isend(&border_n.front(), sncols, MPI_INT, my_n, 0, MPI_COMM_WORLD, &req[0]);
    MPI_Isend(&border_s.front(), sncols, MPI_INT, my_s, 1, MPI_COMM_WORLD, &req[1]);
    MPI_Isend(&border_w.front(), snrows, MPI_INT, my_w, 2, MPI_COMM_WORLD, &req[2]);
    MPI_Isend(&border_e.front(), snrows, MPI_INT, my_e, 3, MPI_COMM_WORLD, &req[3]);
    MPI_Irecv(&new_border_n.front(), sncols, MPI_INT, my_n, 1, MPI_COMM_WORLD, &req[8]);
    MPI_Irecv(&new_border_s.front(), sncols, MPI_INT, my_s, 0, MPI_COMM_WORLD, &req[9]);
    MPI_Irecv(&new_border_w.front(), snrows, MPI_INT, my_w, 3, MPI_COMM_WORLD, &req[10]);
    MPI_Irecv(&new_border_e.front(), snrows, MPI_INT, my_w, 2, MPI_COMM_WORLD, &req[11]);

    MPI_Isend(&corner_nw, 1, MPI_INT, my_nw, 4, MPI_COMM_WORLD, &req[4]);
    MPI_Isend(&corner_ne, 1, MPI_INT, my_ne, 5, MPI_COMM_WORLD, &req[5]);
    MPI_Isend(&corner_se, 1, MPI_INT, my_se, 6, MPI_COMM_WORLD, &req[6]);
    MPI_Isend(&corner_sw, 1, MPI_INT, my_sw, 7, MPI_COMM_WORLD, &req[7]);
    MPI_Irecv(&new_corner_nw, 1, MPI_INT, my_nw, 6, MPI_COMM_WORLD, &req[12]);
    MPI_Irecv(&new_corner_ne, 1, MPI_INT, my_ne, 7, MPI_COMM_WORLD, &req[13]);
    MPI_Irecv(&new_corner_se, 1, MPI_INT, my_se, 4, MPI_COMM_WORLD, &req[14]);
    MPI_Irecv(&new_corner_sw, 1, MPI_INT, my_sw, 5, MPI_COMM_WORLD, &req[15]);

    MPI_Waitall(16, req, stats);

    cashard.set_border(NORTH, new_border_n);
    cashard.set_border(SOUTH, new_border_s);
    cashard.set_border(WEST, new_border_w);
    cashard.set_border(EAST, new_border_e);

    cashard.set_corner(NW, new_corner_nw);
    cashard.set_corner(NE, new_corner_ne);
    cashard.set_corner(SE, new_corner_se);
    cashard.set_corner(SW, new_corner_sw);
    //  if (sid == 0) cashard.dump();

    cashard.raw_update();
    // printf("(%d) %d\n", sid, cashard.sum_state());
    // camaster.update();
    // if (sid == 0) printf("%d\n", camaster.sum_state());

    // if (sid == 0) {
    //   gen_count++;
    //   if (gen_count%count_freq == 0) {
    // 	double gen_time = (read_timer() - start) / (double) gen_count;
    // 	cout << gen_time << "ms per generation." << endl;
    //   }
    // } /* timing block */

    int allsum;
    int mysum = cashard.sum_state();
    MPI_Reduce(&mysum, &allsum, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    camaster.update();
    if (sid == 0) printf("Allsum: %d == %d\n", allsum, camaster.sum_state());

  } /* generation loop */
}

int main(int argc, char *argv[])
{
  int rank, size;

  MPI_Init(&argc, &argv);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  mpi_ca(6000, 6000, rank, size);

  // printf("Rank %d of %d\n", rank, size);

  // int myval = rank + 5;
  // int rval;
  // int next = (rank + 1) % size;
  // int prev = (size + rank - 1) % size;

  // printf("(%d) will send to %d and %d\n", rank, next, prev);

  // MPI_Request req[2];
  // MPI_Status stats[2];

  // MPI_Isend(&myval, 1, MPI_INT, next, 0, MPI_COMM_WORLD, &req[0]);
  // MPI_Irecv(&rval, 1, MPI_INT, prev, 0, MPI_COMM_WORLD, &req[1]);

  // MPI_Waitall(2, req, stats);

  // printf("(%d) received %d\n", rank, rval);

  MPI_Finalize();

  return 0;
}
