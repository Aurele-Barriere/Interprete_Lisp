/*
  Creating a toplevel
*/

#include <cstdio>
#include "object.hh"
#include "env.hh"
#include "eval.hh"
#include "exceptions.hh"

using namespace std;

int using_file;
char filename[255];
extern "C" FILE* yyin;
extern "C" int yylineno;
void yyrestart(FILE *new_file);
extern Object just_read;
extern "C" int yyparse();

void prompt() {
  cout << "Lisp? " << flush;
}

void toplevel_eval(Object l, Environment& env) {
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

void main_loop(Environment& env) {

  if (!using_file) {
    prompt();
  }

  while (yyparse() == 0) {
    Object l = just_read;
    toplevel_eval(l, env);
    if (!using_file) {
      prompt();
    }
  }

}

void toplevel() {
  Environment env; //creating environment

  if (using_file) {
    FILE* fh = fopen(filename, "r");
    yyrestart(fh);

    main_loop(env);

    using_file = 0;
    fclose(fh);
    yyrestart(stdin);
  }

  main_loop(env);
}
