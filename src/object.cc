#include <iostream>
#include <cassert>
#include <string>
#include "object.hh"
#include "memory.hh"

using namespace std;

Memory mem;

Object nil() {
  return Cell::nil();
}

bool null(Object l) {
  return l == nil();
}

Object cons(Object a, Object l) {
  //Object p = new Cell();
  Object p = mem.allocate_cell();
  p -> make_cell_pair(a, l);
  return p;
}

Object car(Object l) {
  assert(!null(l));
  return l -> to_pair_item();
}

Object cdr(Object l) {
  assert(!null(l));
  return l -> to_pair_next();
}

Object empty() {
  return nil();;
}

bool is_empty(Object l) {
  return null(l);
}

Object number_to_Object(int n) {
  //Object p = new Cell();
  Object p = mem.allocate_cell();
  p -> make_cell_number(n);
  return p;
}

Object string_to_Object(string s) {
  //Object p = new Cell();
  Object p = mem.allocate_cell();
  p -> make_cell_string(s);
  return p;
}

Object symbol_to_Object(string s) {
  //Object p = new Cell();
  Object p = mem.allocate_cell();
  p -> make_cell_symbol(s);
  return p;
}

int Object_to_number(Object l) {
  return l -> to_number();
}

string Object_to_string(Object l) {
  assert(l -> is_string() || l -> is_symbol());
  if (l -> is_string()) return l -> to_string();
  if (l -> is_symbol()) return l -> to_symbol();
  assert(false);
}

void print(Object l) {
  if (l -> is_string()) {
    cout << l->to_string();
  } else if (l -> is_symbol()) {
    cout << l->to_symbol();
  } else if (l -> is_number()) {
    cout << l->to_number();
  } else if (l -> is_pair()) {
    cout << "(";
    print(l -> to_pair_item());
    cout << " ";
    print(l -> to_pair_next());
    cout << ")";
  }
}
