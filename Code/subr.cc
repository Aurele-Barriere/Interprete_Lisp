#include <stdexcept>
#include <string>
#include <cassert>
#include "eval.hh"
#include "subr.hh"


Object do_plus(Object lvals) {
  if (!numberp(car(lvals)) || !numberp(cadr(lvals))){
    throw Bad_Type_Exception(car(lvals), "Exception in +: not a number" );
  }
  int a = Object_to_number(car(lvals));
  int b = Object_to_number(cadr(lvals));
  return number_to_Object(a + b);
}

Object do_minus(Object lvals) {
  if (!numberp(car(lvals)) || !numberp(cadr(lvals))){
    throw Bad_Type_Exception(car(lvals), "Exception in -: not a number" );
  }
  int a = Object_to_number(car(lvals));
  int b = Object_to_number(cadr(lvals));
  return number_to_Object(a - b);
}


Object do_times(Object lvals) {
  if (!numberp(car(lvals)) || !numberp(cadr(lvals))){
    throw Bad_Type_Exception(car(lvals), "Exception in *: not a number" );
  }
  int a = Object_to_number(car(lvals));
  int b = Object_to_number(cadr(lvals));
  return number_to_Object(a * b);
}
