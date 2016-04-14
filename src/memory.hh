#pragma once

#include "cell.hh"
#include "object.hh"
#include <vector>

using namespace std;

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
};
