#include <cstdio>
#include "object.hh"
#include "env.hh"
#include "eval.hh"

extern Object just_read;
extern "C" int yyparse();
extern "C" FILE *yyin;

Object read() {
  yyparse();
  return just_read;
}
