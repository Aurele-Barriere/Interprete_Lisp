#pragma once

/*
  Subroutines
*/


#include <string>
#include <cassert>
#include "eval.hh"
#include "toplevel.hh"

Object do_plus(Object lvals);

Object do_minus(Object lvals);

Object do_times(Object lvals);

Object do_equal(Object lvals);
