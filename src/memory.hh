#pragma once

#include "cell.hh"
#include "env.hh"

#define BASE_MEMORY_SIZE 30

enum flag { not_taken , taken };


class Memory {
private:
  Cell* cell_vect;
  flag* flags;
  unsigned size;
  void garbage_collection_aux(bool* seen, Object p);

public:
  Memory();
  ~Memory();
  Object allocate_cell();
  Cell* at(unsigned i);
  void garbage_collection(Environment env);
};
