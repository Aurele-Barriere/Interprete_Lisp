#pragma once

#include "cell.hh"

#define BASE_MEMORY_SIZE 30

enum flag { not_taken , taken };


class Memory {
private:
  Cell* cell_vect;
  flag* flags;
  unsigned size;

public:
  Memory();
  Object allocate_cell();
  Cell* at(unsigned i);
};
