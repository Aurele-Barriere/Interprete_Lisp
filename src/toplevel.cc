/*
  Creating a toplevel
*/

#include <cstdio>
#include "object.hh"
#include "env.hh"
#include "eval.hh"
#include "read.hh"
#include "exceptions.hh"

using namespace std;

int using_file;
char filename[255];
extern "C" FILE* yyin;

void prompt() {
  cout << "Lisp? " << flush;
}

void main_loop(Environment& env, int* eof) {

  if (!using_file) {
    prompt();
  }
  Object l = read(eof);

  if (listp(l) && Object_to_string(car(l)) == "setq") {
    env.add_new_binding(Object_to_string(cadr(l)), eval(caddr(l), env));
  }
  else if (listp(l) && Object_to_string(car(l)) == "printenv") {
    env.print(cout);
    cout << endl;
  }
  else {
    try {
      cout << eval(l, env) << endl;
    } catch (const Evaluation_Exception except) {
      cout << except.what() << endl;
    } catch (const No_Binding_Exception except) {
      cout << except.what() << endl;
    } catch (const Zipping_Exception except) {
      cout << except.what() << endl;
    } catch (const Bad_Type_Exception except) {
      cout << except.what() << endl;
    }
  }
}

void toplevel() {
  Environment env; //creating environment
  int eof = 0; //boolean for end of file, modified by read

  if (using_file) {
    FILE* yyin_prev = yyin;
    yyin = fopen(filename, "r");
    do {
      cout << "main loop file" << endl;
      main_loop(env, &eof);
    } while (!eof);
    using_file = 0;
    fclose(yyin);
    yyin = yyin_prev;
  }
  eof = 0;

  do {
    cout << "main loop" << endl;
    main_loop(env, &eof);
  } while (!eof);
}
