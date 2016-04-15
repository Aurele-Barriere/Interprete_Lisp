#pragma once

#include <iostream>
#include <cassert>
#include <string>

typedef unsigned Object;

Object nil();
bool null(Object l);

Object cons(Object a, Object l);
Object car(Object l);
Object cdr(Object l);
Object empty();
bool is_empty(Object l);

Object number_to_Object(int n);
Object string_to_Object(std::string s);
Object symbol_to_Object(std::string s);

int Object_to_number(Object l);
std::string Object_to_string(Object l);

void print(Object l);
