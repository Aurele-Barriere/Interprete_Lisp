#include <stdexcept>
#include <string>
#include <cassert>
#include "eval.hh"
#include "subr.hh"
#include "exceptions.hh"



Object do_plus(Object lvals) {
  if (null(lvals) || null(cdr(lvals))) {
    throw Zipping_Exception(lvals, "Not enough arguments for subroutine +");
  }
  if (!numberp(car(lvals)) || !numberp(cadr(lvals))){
    throw Bad_Type_Exception(car(lvals), "Exception in +: not a number" );
  }
  int a = Object_to_number(car(lvals));
  int b = Object_to_number(cadr(lvals));
  return number_to_Object(a + b);
}

Object do_minus(Object lvals) {
  if (null(lvals) || null(cdr(lvals))) {
    throw Zipping_Exception(lvals, "Not enough arguments for subroutine -");
  }
  if (!numberp(car(lvals)) || !numberp(cadr(lvals))){
    throw Bad_Type_Exception(car(lvals), "Exception in -: not a number" );
  }
  int a = Object_to_number(car(lvals));
  int b = Object_to_number(cadr(lvals));
  return number_to_Object(a - b);
}


Object do_times(Object lvals) {
  if (null(lvals) || null(cdr(lvals))) {
    throw Zipping_Exception(lvals, "Not enough arguments for subroutine *");
  }
  if (!numberp(car(lvals)) || !numberp(cadr(lvals))){
    throw Bad_Type_Exception(car(lvals), "Exception in *: not a number" );
  }
  int a = Object_to_number(car(lvals));
  int b = Object_to_number(cadr(lvals));
  return number_to_Object(a * b);
}

Object do_equal(Object lvals) {
  if (null(lvals) || null(cdr(lvals))) {
    throw Zipping_Exception(lvals, "Not enough arguments for subroutine =");
  }
  if (numberp(car(lvals)) && numberp(cadr(lvals))) {
    int a = Object_to_number(car(lvals));
    int b = Object_to_number(cadr(lvals));
    if (a==b) { return number_to_Object(1);}
    else { return nil();}
  }
  else if (stringp(car(lvals)) && stringp(cadr(lvals))) {
    string a = Object_to_string(car(lvals));
    string b = Object_to_string(cadr(lvals));
    if (!a.compare(b)) { return number_to_Object(1);}
    else {return nil();}
  }

  throw Bad_Type_Exception(car(lvals), "Exception in =: not 2 numbers or 2 strings" );

}
