#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>
#include "object.hh"

using namespace std;

class Binding {
private:
  string name;
  Object value;
public:
  Binding(string _name, Object _value);
  string get_name() const;
  Object get_value() const;
};

class Environment {
private:
  vector<Binding> contents;
public:
  Environment();
  void add_new_binding(string name, Object value);
  void extend_env(Object lpars, Object lvals);
  Object find_value(string name);
  void print(ostream& s);
};

ostream& operator << (ostream& s, Environment& env);

class No_Binding_Exception: public runtime_error {
private:
  string name;
public:
  No_Binding_Exception(string _name);
  virtual ~No_Binding_Exception() throw () {}
};

class Zipping_Exception: public runtime_error {
private:
  string message;
  Object lobjs;
public:
  Zipping_Exception(Object _lobjs, string _message);
  virtual ~Zipping_Exception() throw () {}
};
