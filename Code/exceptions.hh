#pragma once

#include <stdexcept>
#include <string>
#include "object.hh"
#include "env.hh"

/*
  Exceptions 
*/

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

class Evaluation_Exception: public runtime_error {
private:
  Object obj;
  Environment env;
  string message;
public:
  Evaluation_Exception(Object _obj, Environment _env, string _message);
  virtual ~Evaluation_Exception() throw () {}
};

class Bad_Type_Exception: public runtime_error {
private:
  Object obj;
  string message;
public:
  Bad_Type_Exception(Object _obj, string _message);
  virtual ~Bad_Type_Exception() throw () {}
};
