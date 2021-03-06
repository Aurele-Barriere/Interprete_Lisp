#include <stdexcept>
#include <string>
#include <cassert>
#include "eval.hh"
#include "memory.hh"
#include "exceptions.hh"
#include "subr.hh"

using namespace std;

int verbose = 0;
extern Memory mem;

bool numberp(Object l) {
  return mem.at(l)->is_number();
}

bool stringp(Object l) {
  return mem.at(l)->is_string();
}

bool symbolp(Object l) {
  return mem.at(l)->is_symbol();
}

bool listp(Object l) {
  return mem.at(l)->is_pair();
}

Object cadr(Object l) {
  return car(cdr(l));
}

Object cddr(Object l) {
  return cdr(cdr(l));
}

Object caddr(Object l) {
  return car(cddr(l));
}

Object cdddr(Object l) {
  return cdr(cddr(l));
}

Object cadddr(Object l) {
  return car(cdddr(l));
}



Object eval(Object l, Environment env);
Object apply(Object f, Object lvals, Environment env);
Object eval_list(Object largs, Environment env);

Object eval(Object l, Environment env) {
  if (verbose) clog << "\teval: " << l << env << endl;

  if (null(l)) return l;
  if (numberp(l)) return l;
  if (stringp(l)) return l;
  if (symbolp(l)) return env.find_value(Object_to_string(l));
  assert(listp(l));
  Object f = car(l);
  if (symbolp(f)) {
    if (Object_to_string(f) == "quote") return cadr(l);
    if (Object_to_string(f) == "if") {
      Object test_part = cadr(l);
      Object then_part = caddr(l);
      Object else_part = cadddr(l);
      Object test_value = eval(test_part, env);
      if (null(test_value)) return eval(else_part, env);
      return eval(then_part, env);
    }
    if (Object_to_string(f) == "lambda") {
      return l;
    }

  }
  // It is a function applied to arguments
  Object vals = eval_list(cdr(l), env);
  return apply(f, vals, env);
}

Object eval_list(Object largs, Environment env) {
  if (null(largs)) return largs;
  return cons(eval(car(largs), env), eval_list(cdr(largs), env));
}

Object apply(Object f, Object lvals, Environment env) {
  if (verbose) clog << "\tapply: " << f << " " << lvals << env << endl;

  if (null(f)) throw Evaluation_Exception(f, env, "Cannot apply nil");
  if (numberp(f)) throw Evaluation_Exception(f, env, "Cannot apply a number");
  if (stringp(f)) throw Evaluation_Exception(f, env, "Cannot apply a string");
  if (symbolp(f)) {

    if (Object_to_string(f) == "+") return do_plus(lvals);
    if (Object_to_string(f) == "*") return do_times(lvals);
    if (Object_to_string(f) == "-") return do_minus(lvals);
    if (Object_to_string(f) == "=") return do_equal(lvals);
    if (Object_to_string(f) == "read") return do_read();
    Object new_f = env.find_value(Object_to_string(f));
    return apply(new_f, lvals, env);
  }
  assert(listp(f));
  if (Object_to_string(car(f)) == "lambda") {
    Object lpars = cadr(f);
    Object body = caddr(f);
    Environment new_env = env;
    new_env.extend_env(lpars, lvals);
    return eval(body, new_env);
  }
  throw Evaluation_Exception(f, env, "Cannot apply a list");
  assert(false);
}
