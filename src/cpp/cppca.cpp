
#include"cppca.h"

using namespace std;

int convert(char in);
void supdate(int *sd, int *ns, int nrows, int ncols);

void CALife::update()
{
  nwrap_boundary();
  raw_update();
}

void CALife::raw_update()
{
  int h8[8][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

  for(int r=0; r<nrows; r++)
    for(int c=0; c<ncols; c++) {
      int nsum = 0;
      for (int i=0; i<8; i++) {
	int ro = h8[i][0];
	int co = h8[i][1];
	nsum += state_data[(1 + c + co) + (1 + r + ro) * real_ncols];
      }
      next_state[(1 + c) + (1 + r) * real_ncols] = (nsum == 3 || (nsum == 2 && state_data[(1 + c) + (1 + r) * real_ncols]));
    }

  swap(next_state, state_data);
}

void CAVote::update()
{
  nwrap_boundary();

  supdate(&state_data.front(), &next_state.front(), nrows, ncols);

  swap(next_state, state_data);
}

void CAVote::raw_update()
{
  supdate(&state_data.front(), &next_state.front(), nrows, ncols);

  swap(next_state, state_data);
}  

void supdate(int *sd, int *ns, int nrows, int ncols)
{
  int h9[9][2] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 0}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
  int ur[10] = {0, 0, 0, 0, 1, 0, 1, 1, 1, 1};
  int real_nrows = nrows + 2;
  int real_ncols = ncols + 2;
  int *state_data = sd;
  int *next_state = ns;

  int ro, co, r, c, nsum, i;

  //#pragma omp parallel for private(c, nsum, ro, co, i) schedule(guided, 10)
  for(r=0; r<nrows; r++)
    for(c=0; c<ncols; c++) {
      nsum = 0;
      for (i=0; i<9; i++) {
        ro = h9[i][0];
        co = h9[i][1];
        nsum += state_data[(1 + c + co) + (1 + r + ro) * real_ncols];
      }
      next_state[(1 + c) + (1 + r) * real_ncols] = ur[nsum];
    }
}

CA::CA(int in_nrows, int in_ncols) : 
nrows(in_nrows), 
ncols(in_ncols),
state_data((in_nrows + 2) * (in_ncols + 2)),
next_state((in_nrows + 2) * (in_ncols + 2))
{
  real_nrows = in_nrows + 2;
  real_ncols = in_ncols + 2;
  
  //  cout << "Constructing " << nrows << "x" << ncols << endl;
}

CA::CA(string filename)
{
  ifstream ifile(filename.c_str());

  ifile >> nrows;
  ifile >> ncols;

  real_nrows = nrows + 2;
  real_ncols = ncols + 2;

  //  cout << "Read " << nrows << "x" << ncols << endl;
  istream_iterator<char> start(ifile), end;
  vector<char> file_state(start, end);
  state_data.reserve(file_state.size());
  next_state.reserve(file_state.size());
  transform(file_state.begin(), file_state.end(), state_data.begin(), convert);

}

CA::CA(const CA &orig)
{
  state_data = orig.state_data;
  next_state = orig.next_state;
  nrows = orig.nrows;
  ncols = orig.ncols;
  real_nrows = orig.real_nrows;
  real_ncols = orig.real_ncols;
  cout << "copy" << endl;
  cout << orig.nrows;
  cout << state_data.size() << endl;
  cout << orig.state_data.size() << endl;
}

int CA::sum_state()
{
  int sum = 0;
  for(int r=0; r<nrows; r++)
    for(int c=0; c<ncols; c++)
      sum += get_cell(r, c);
  //  return accumulate(state_data.begin(), state_data.end(), 0);
  return sum;
}

void CA::set_cell(int row, int col, int value)
{
  int crow = row + 1;
  int ccol = col + 1;

  state_data[crow * real_ncols + ccol] = value;
}

int CA::get_cell(int row, int col)
{
  int crow = row + 1;
  int ccol = col + 1;

  return state_data[crow * real_ncols + ccol];
}

void CA::dump()
{
  // Dump CA state to terminal, including border regions

  // Top row of ghost region
  cout << get_cell(-1, -1) << "|";
  for(int c=0; c<ncols; c++) cout << get_cell(-1, c);
  cout << "|" << get_cell(-1, ncols) << endl;

  // Separator (purely visual)
  cout << "-+";
  for(int c=0; c<ncols; c++) cout << "-";
  cout << "+-" << endl;

  // Main part of CA state
  for(int r=0; r<nrows; r++) {
    cout << get_cell(r, -1) << "|";		
    for(int c=0; c<ncols; c++) cout << get_cell(r, c);
    cout << "|" << get_cell(r, ncols) << endl;
  }

  // Lower separator (visual again)
  cout << "-+";
  for(int c=0; c<ncols; c++) cout << "-";
  cout << "+-" << endl;

  // Bottom row of ghost region
  cout << get_cell(nrows, -1) << "|";
  for (int c=0; c<ncols; c++) cout << get_cell(nrows, c);
  cout << "|" << get_cell(nrows, ncols);

  cout << endl;
}

void CA::save_state(string filename)
{
  cout << "Saving state to " << filename << endl;

  ofstream ofile;
  ofile.open(filename.c_str());
  ofile << nrows << endl;
  ofile << ncols << endl;
  copy(state_data.begin(), state_data.end(), ostream_iterator<int>(ofile));
  ofile.close();
}

int convert(char in) { return (int) in - 48; }

void CA::read_state(string filename)
{
  cout << "Reading state from " << filename << endl;

  ifstream ifile(filename.c_str());

  if (!ifile) {
    cout << "ERROR: Couldn't open " << filename << endl;
    exit(2);
  }

  int in_nrows;
  int in_ncols;

  ifile >> in_nrows;
  ifile >> in_ncols;

  if ( !(in_nrows == nrows && in_ncols == ncols) ) {
    cout << "Size mismatch" << endl;
  }

  cout << "Read " << in_nrows << "x" << in_ncols << endl;
  istream_iterator<char> start(ifile), end;
  vector<char> file_state(start, end);
  transform(file_state.begin(), file_state.end(), state_data.begin(), convert);
}

void CA::fill_random()
{
  for(int r=0; r<nrows; r++) 
    for(int c=0; c<ncols; c++)
      state_data[1 + c + (r + 1) * (real_ncols)] = rand() % 2;
}

void CA::nwrap_boundary()
{
  set_border(NORTH, get_border(SOUTH));
  set_border(SOUTH, get_border(NORTH));
  set_border(EAST, get_border(WEST));
  set_border(WEST, get_border(EAST));

  set_corner(NW, get_corner(SE));
  set_corner(SE, get_corner(NW));
  set_corner(NE, get_corner(SW));
  set_corner(SW, get_corner(NE));
}

void CA::wrap_boundary()
{
  /* Implement wrapped bounday conditions by set_cellting top row of ghost region
     to bottom row of CA state and so on */
     
  // Bottom row of ghost region
  for(int c=1; c<ncols+1; c++) {
    state_data[c + (real_nrows - 1) * real_ncols] = state_data[c + real_ncols];
  }

  // Top row of ghost region
  for(int c=1; c<ncols+1; c++) {
     state_data[c] = state_data[c + (nrows) * real_ncols];
  }

  // Left column of ghost region
  for(int r=1; r<nrows+1; r++) {
    state_data[r * real_ncols] = state_data[(ncols) + r * real_ncols];
  }

  // Right column of ghost region
  for(int r=1; r<nrows+1; r++) {
    state_data[real_ncols - 1 + r * real_ncols] = state_data[1 + r * real_ncols];
  }

  // Top left corner
  state_data[0] = state_data[ncols + nrows * real_ncols];

  // Bottom right corner
  state_data[(real_ncols - 1) + (real_nrows - 1) * real_ncols] = state_data[1 + real_ncols];

  // Top right corner
  state_data[real_ncols - 1] = state_data[1 + (real_nrows - 2) * real_ncols];

  // Bottom left corner
  state_data[(real_nrows - 1) * real_ncols] = state_data[(real_ncols - 2) + real_ncols];

}

vector<int> CA::get_border(border b)
{
  vector<int> border_vals;
  int start, stride, size;

  switch (b) 
    {
    case NORTH:
      start = 1 + real_ncols;
      stride = 1;
      size = ncols;
      break;
    case SOUTH:
      start = 1 + nrows * real_ncols;
      stride = 1;
      size = ncols;
      break;
    case EAST:
      start = ncols + real_ncols;
      stride = real_ncols;
      size = nrows;
      break;
    case WEST:
      start = 1 + real_ncols;
      stride = real_ncols;
      size = nrows;
      break;
    }
    
  for(int i=0;i<size;i++) {
    border_vals.push_back(state_data[start + i * stride]);
  }

  return border_vals;
}

void CA::set_border(border b, vector<int> new_border)
{
  int start, stride, size;

  switch (b) 
    {
    case NORTH:
      start = 1;
      stride = 1;
      size = ncols;
      break;
    case SOUTH:
      start = 1 + (1 + nrows) * real_ncols;
      stride = 1;
      size = ncols;
      break;
    case EAST:
      start = 1 + ncols + real_ncols;
      stride = real_ncols;
      size = nrows;
      break;
    case WEST:
      start = real_ncols;
      stride = real_ncols;
      size = nrows;
      break;
    default:
      assert(0);
    }
    
  for(int i=0;i<size;i++) {
    //    border_vals.push_back(state_data[start + i * stride]);
    state_data[start + i * stride] = new_border[i];
  }
}

int CA::get_corner(corner co)
{
  switch (co)
    {
    case NW:
      return get_cell(0, 0);
    case NE:
      return get_cell(0, ncols-1);
    case SW:
      return get_cell(nrows-1, 0);
    case SE:
      return get_cell(nrows-1, ncols-1);
    }
}

void CA::set_corner(corner co, int new_val)
{
  switch (co)
    {
    case NW:
      set_cell(-1, -1, new_val);
      break;
    case NE:
      set_cell(-1, ncols, new_val);
      break;
    case SW:
      set_cell(nrows, -1, new_val);
      break;
    case SE:
      set_cell(nrows, ncols, new_val);
      break;
    }
}

vector<int> CA::copy_state()
{
  vector<int> state_copy = state_data;

  return state_copy;
}
