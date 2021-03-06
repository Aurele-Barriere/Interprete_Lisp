#include "env.hh"
#include "exceptions.hh"
#include "memory.hh"

using namespace std;
extern Memory mem;

Binding::Binding(string _name, Object _value):
  name(_name), value(_value) {}
string  Binding::get_name() const {
  return name;
}
Object  Binding::get_value() const {
  return value;
}



Environment::Environment() {
  contents = vector<Binding>();
}

void Environment::add_new_binding(string name, Object value) {
  contents.push_back(Binding(name, value));
}
void Environment::extend_env(Object lpars, Object lvals) {
  if (null(lpars) && null(lvals)) return;
  if (null(lpars) && !null(lvals)) throw Zipping_Exception(lvals, "Too many arguments");
  if (!null(lpars) && null(lvals)) throw Zipping_Exception(lpars, "Not enough arguments");
  add_new_binding(Object_to_string(car(lpars)), car(lvals));
  extend_env(cdr(lpars), cdr(lvals));
}
Object Environment::find_value(string name) {
  for (int i = contents.size() - 1;; i--) {
    if (i < 0) throw No_Binding_Exception(name);
    if (contents.at(i).get_name() == name) return contents.at(i).get_value();
  }
}

void Environment::print(ostream& s) {
  s << "\t| ";
  for (int i = contents.size() - 1; i >= 0; i--) {
    s << contents.at(i).get_name() << ": " << mem.at(contents.at(i).get_value()) << "; " << endl << "\t  ";
  }
}

unsigned Environment::size() {
  return contents.size();
}

Binding Environment::at(unsigned i) {
  assert(i < size());
  return contents.at(i);
}

Binding Environment::operator[] (unsigned i) {
  return at(i);
}


ostream& operator << (ostream& s, Environment& env) {
  env.print(s);
  return s;
}
