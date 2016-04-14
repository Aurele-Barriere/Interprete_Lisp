#include "memory.hh"
#include "exceptions.hh"
#include <iostream>

using namespace std;

Memory::Memory() {
  cout << "Creating Memory" << endl;
  cout << "Mem size : " << MEMORY_SIZE << endl;
  int i;
  for (i = 0; i< MEMORY_SIZE; i++) {
    flags[i] = free;
  }
}

Object Memory::allocate_cell() {
  int i;
  for (i=0; i<MEMORY_SIZE; i++) {
    if (flags[i] == free) {
      return &(cell_vect[i]);
    }
  }
  throw Memory_Exception();
}
