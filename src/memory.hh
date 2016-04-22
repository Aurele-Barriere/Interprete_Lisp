#pragma once

#include "cell.hh"
#include "env.hh"
#include "object.hh"

#define BASE_MEMORY_SIZE 30

enum flag { not_taken , taken };


class Memory {
  /*
    All friends that are allowed to access the memory
   */

  // from object.cc
  friend Object cons(Object a, Object l);
  friend Object car(Object l);
  friend Object cdr(Object l);
  friend Object empty();
  friend bool is_empty(Object l);
  friend Object number_to_Object(int n);
  friend Object string_to_Object(std::string s);
  friend Object symbol_to_Object(std::string s);
  friend int Object_to_number(Object l);
  friend std::string Object_to_string(Object l);
  friend void print(Object l);

  // from eval.cc
  friend bool numberp(Object l);
  friend bool stringp(Object l);
  friend bool symbolp(Object l);
  friend bool listp(Object l);

  // from cell.cc
  friend ostream& print_cell_pointer(ostream& s, const Cell *p);
  friend ostream& print_cell_pointer_aux(ostream& s, const Cell *p);

  // from toplevel.cc
  friend void main_loop(Environment& env);
  friend void toplevel_eval(Object l, Environment& env);

  // from env.cc
  friend Environment;

private:
  Cell* cell_vect;
  flag* flags;
  unsigned size;
  void garbage_collection_aux(bool* seen, Object p);
  Object allocate_cell();
  void garbage_collection(Environment env);
  Cell* at(unsigned i);

public:
  Memory();
  ~Memory();
};
