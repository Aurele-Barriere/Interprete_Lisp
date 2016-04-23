#include "cell.hh"
#include "memory.hh"
#include <cstdlib>

using namespace std;

extern Memory mem;

void Cell::check() {} // To be filled up!

Cell::cell_sort Cell::get_sort() const {
  return sort;
}

bool Cell::is_number() const {
  return sort == NUMBER;
}
bool Cell::is_string() const {
  return sort == STRING;
}
bool Cell::is_symbol() const {
  return sort == SYMBOL;
}
bool Cell::is_pair() const {
  return sort == PAIR;
}

int Cell::to_number() const {
  assert(is_number());
  return value.as_number;
}

string Cell::to_string() const {
  assert(is_string());
  return string(value.as_string);
}

string Cell::to_symbol() const {
  assert(is_symbol());
  return string(value.as_symbol);
}

Object Cell::to_pair_item() const {
  assert(is_pair());
  return *value.as_pair.item;
}

Object Cell::to_pair_next() const {
  assert(is_pair());
  return *value.as_pair.next;
}

// Cell *Cell::nil() {
//   return &cell_nil;
// }

Cell::Cell() {
  make_cell_number(0);
}

void Cell::free_string() {
  if (is_string()) {
    free (value.as_string);
  }
  if (is_symbol()) {
    free (value.as_symbol);
  }
}

void Cell::make_cell_number(int a) {
  sort = NUMBER;
  value.as_number = a;
}

void Cell::make_cell_string(string s) {
  sort = STRING;
  char *p = strdup(s.c_str());	// Watch it! Allocated by malloc
  value.as_string = p;
}

void Cell::make_cell_symbol(string s) {
  sort = SYMBOL;
  char *p = strdup(s.c_str());	// Watch it! Allocated by malloc
  value.as_symbol = p;
}

void Cell::make_cell_pair(Object p, Object q) {
  sort = PAIR;
  cell_pair c;
  c.item = &p;
  c.next = &q;
  value.as_pair = c;
}

Cell Cell::cell_nil = Cell();

/*static*/ ostream& print_cell_pointer(ostream& s, const Cell *p);

/*static*/ ostream& print_cell_pointer_aux(ostream& s, const Cell *p) {
  assert(p -> is_pair());
  for (const Cell *pp = p;; pp = mem.at(pp->to_pair_next().getID())) {
    if (pp == mem.at(0)) break;
    print_cell_pointer(s, mem.at(pp->to_pair_item().getID()));
    if (mem.at(pp->to_pair_next().getID()) == mem.at(0)) break;
    s << " " << flush;
  }
  return s;
}

/*static*/ ostream& print_cell_pointer(ostream& s, const Cell *p) {
  if (p == mem.at(0)) return s << "nil" << flush;
  if (p -> is_number()) return s << p -> to_number() << flush;
  if (p -> is_string()) return s << p -> to_string() << flush;
  if (p -> is_symbol()) return s << p -> to_symbol() << flush;
  if (p -> is_pair()) {
    s << "(" << flush;
    print_cell_pointer_aux(s, p);
    s << ")" << flush;
    return s;
  }
  assert(false);
}

ostream& operator << (ostream& s, const Cell *p) {
  return print_cell_pointer(s, p);
}
