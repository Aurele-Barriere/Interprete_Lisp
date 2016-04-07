#include <cstdio>
#include "object.hh"
#include "env.hh"
#include "eval.hh"

extern Object just_read;
extern "C" int yyparse();
extern "C" FILE *yyin;

Object read(int * eof) {
  yyparse();
  if (feof(yyin)) { //taking care of end of file
    *eof = 1;
  }
  return just_read;
}
