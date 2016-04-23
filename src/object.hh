#pragma once

#include <iostream>
#include <cassert>
#include <string>
#include "memory.hh"
class Cell;

class Object{

  friend Object nil();
  friend bool null(Object l);
  friend Object cons(Object a, Object l);
  friend Object car(Object l);
  friend Object cdr(Object l);
  friend bool is_empty(Object l);
  friend Object number_to_Object(int n);
  friend Object string_to_Object(std::string s);
  friend Object symbol_to_Object(std::string s);
  friend int Object_to_number(Object l);
  friend std::string Object_to_string(Object l);
  friend void print(Object l);

private:
  unsigned id;

public:
  unsigned getID() {
    return id;
  }
};

Object nil();
Object empty();
Object number_to_Object(int n);
Object string_to_Object(std::string s);
Object symbol_to_Object(std::string s);
