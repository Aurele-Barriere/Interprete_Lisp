#pragma once

#include <stdexcept>
#include "object.hh"
#include "env.hh"

using namespace std;

bool numberp(Object l);
bool stringp(Object l);
bool symbolp(Object l);
bool listp(Object l);

Object cadr(Object l);
Object cddr(Object l);
Object caddr(Object l);
Object cdddr(Object l);
Object cadddr(Object l);

Object eval(Object l, Environment env);
Object apply(Object f, Object lvals, Environment env);
Object eval_list(Object largs, Environment env);

class Evaluation_Exception: public runtime_error {
private:
  Object obj;
  Environment env;
  string message;
public:
  Evaluation_Exception(Object _obj, Environment _env, string _message);
  virtual ~Evaluation_Exception() throw () {}
};
