#pragma once

#include <cstdio>
#include "object.hh"
#include "env.hh"

void prompt();
void toplevel_eval(Object l, Environment& env);
void eval_file(const char* file, Environment& env);
void main_loop(Environment& env);
void toplevel();
