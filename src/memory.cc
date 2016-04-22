#include "memory.hh"
#include <cstdlib>
#include "exceptions.hh"

using namespace std;

int memory_verbose = 0;

Memory::Memory() : cell_vect(BASE_MEMORY_SIZE), flags(BASE_MEMORY_SIZE, not_taken) {
  size = BASE_MEMORY_SIZE;
  cout << "Creating Memory" << endl;
  cout << "Mem size : " << size << endl;


  flags[0] = taken; // Empty cell
}

Memory::~Memory() {
  for (unsigned i = 0; i < size; i++) {
    if (flags[i] == taken) {
      cell_vect[i].free_string();
    }
  }
}

Object Memory::allocate_cell() {
  unsigned i;
  for (i=0; i<size; i++) {
    if (flags[i] == not_taken) {
      if (memory_verbose) cout << "allocated cell number " << i << endl;
      flags[i] = taken;
      return i;
    }
  }

  if (memory_verbose) cout << "increasing memory size" << endl;
  cell_vect.resize(size + BASE_MEMORY_SIZE);
  flags.resize(size + BASE_MEMORY_SIZE, not_taken);

  if (memory_verbose) cout << "allocated cell number " << i << endl;
  flags[i] = taken;
  size += BASE_MEMORY_SIZE;
  return i;
}

Cell* Memory::at(unsigned i) {
  assert(i < size);
  return &(cell_vect[i]);
}

void Memory::garbage_collection_aux(bool* seen, Object p) {
  seen[p] = true;
  if (cell_vect[p].is_pair()) {
    garbage_collection_aux(seen, cell_vect[p].to_pair_item());
    garbage_collection_aux(seen, cell_vect[p].to_pair_next());
  }
}

void Memory::garbage_collection(Environment env) {
  if (memory_verbose) cout << "collecting garbage" << endl;
  bool* seen = (bool*) malloc(size * sizeof(bool));
  assert(seen);

  for (unsigned i = 0; i < size; i++) {
    seen[i] = false;
  }
  for (unsigned i = 0; i < env.size(); i++) {
    garbage_collection_aux(seen, env[i].get_value());
  }

  unsigned cnt = 0;
  // begins at 1 because we do not want to free the first cell (nil)
  for (unsigned i = 1; i < size; i++) {
    if (!seen[i] && flags[i] == taken) {
      cnt++;
      flags[i] = not_taken;
    }
  }
  if (memory_verbose) cout << "freed " << cnt << " cells" << endl;
  free(seen);

}
