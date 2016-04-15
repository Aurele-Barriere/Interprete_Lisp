#include "object.hh"
#include "memory.hh"

using namespace std;

Memory mem;


Object nil() {
  return 0;
}

bool null(Object l) {
  return l == nil();
}

Object cons(Object a, Object l) {
  //Object p = new Cell();
  Object p = mem.allocate_cell();
  mem.at(p)->make_cell_pair(a, l);
  return p;
}

Object car(Object l) {
  assert(!null(l));
  Object p = mem.at(l)->to_pair_item();
  return p;
}

Object cdr(Object l) {
  assert(!null(l));
  Object p = mem.at(l)->to_pair_next();
  return p;
}

Object empty() {
  return nil();
}

bool is_empty(Object l) {
  return null(l);
}

Object number_to_Object(int n) {
  //Object p = new Cell();
  Object p = mem.allocate_cell();
  mem.at(p)->make_cell_number(n);
  return p;
}

Object string_to_Object(string s) {
  //Object p = new Cell();
  Object p = mem.allocate_cell();
  mem.at(p)->make_cell_string(s);
  return p;
}

Object symbol_to_Object(string s) {
  //Object p = new Cell();
  Object p = mem.allocate_cell();
  mem.at(p)->make_cell_symbol(s);
  return p;
}

int Object_to_number(Object l) {
  return mem.at(l)->to_number();
}

string Object_to_string(Object l) {
  assert(mem.at(l)->is_string() || mem.at(l)->is_symbol());
  if (mem.at(l)->is_string()) return mem.at(l)->to_string();
  if (mem.at(l)->is_symbol()) return mem.at(l)->to_symbol();
  assert(false);
}

void print(Object l) {
  if (mem.at(l)->is_string()) {
    cout << mem.at(l)->to_string();
  } else if (mem.at(l)->is_symbol()) {
    cout << mem.at(l)->to_symbol();
  } else if (mem.at(l)->is_number()) {
    cout << mem.at(l)->to_number();
  } else if (mem.at(l)->is_pair()) {
    cout << "(";
    print(car(l));
    cout << " ";
    print(cdr(l));
    cout << ")";
  }
}
