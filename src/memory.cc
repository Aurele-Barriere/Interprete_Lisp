#include "memory.hh"
#include "exceptions.hh"
#include <iostream>
#include <cstdlib>

using namespace std;

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
}

Object Memory::allocate_cell() {
  unsigned i;
  for (i=0; i<size; i++) {
    if (flags[i] == not_taken) {
      cout << "allocated cell number " << i << endl;
      flags[i] = taken;
      return &(cell_vect[i]);
    }
  }

  cout << "increasing memory size" << endl;
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

  cout << "allocated cell number " << i << endl;
  flags[i] = taken;
  size += BASE_MEMORY_SIZE;
  return &(cell_vect[i]);
}
