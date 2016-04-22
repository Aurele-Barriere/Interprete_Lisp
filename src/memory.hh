#pragma once

#include "cell.hh"
#include "env.hh"
#include "object.hh"

#define BASE_MEMORY_SIZE 30

enum flag { not_taken , taken };


class Memory {

  friend Object cons(Object a, Object l);
  friend Object number_to_Object(int n);
  friend Object string_to_Object(std::string s);
  friend Object symbol_to_Object(std::string s);

private:
  Cell* cell_vect;
  flag* flags;
  unsigned size;
  void garbage_collection_aux(bool* seen, Object p);
  Object allocate_cell();

public:
  Memory();
  ~Memory();
  
  Cell* at(unsigned i);
  void garbage_collection(Environment env);
};
