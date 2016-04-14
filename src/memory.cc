#include "memory.hh"
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

void Memory::allocate_cell() {
}
