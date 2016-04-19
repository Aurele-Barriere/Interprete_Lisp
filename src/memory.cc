#include "memory.hh"
#include <cstdlib>
#include "exceptions.hh"

using namespace std;

int memory_verbose = 0;

Memory::Memory() {
  size = BASE_MEMORY_SIZE;
  cout << "Creating Memory" << endl;
  cout << "Mem size : " << size << endl;

  cell_vect = (Cell*) malloc(size * sizeof(Cell));
  flags = (flag*) malloc(size * sizeof(flag));

  if (!cell_vect || !flags) {
    throw Memory_Exception();
  }

  for (unsigned i = 0; i< size; i++) {
    flags[i] = not_taken;
  }

  flags[0] = taken; // Empty cell
  cell_vect[0] = Cell();
}

Memory::~Memory() {
  free(cell_vect);
  free(flags);
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
  Cell* cell_vect_temp = (Cell*) realloc(cell_vect, (size+BASE_MEMORY_SIZE) * sizeof(Cell));
  flag* flags_temp = (flag*) realloc(flags, (size+BASE_MEMORY_SIZE) * sizeof(flag));

  if (!cell_vect_temp || !flags) {
    throw Memory_Exception();
  } else {
    cell_vect = cell_vect_temp;
    flags = flags_temp;
  }

  for (unsigned j = i; j< size+BASE_MEMORY_SIZE; j++) {
    flags[j] = not_taken;
  }

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

}
