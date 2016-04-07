/*
  Creating a toplevel
*/

#include <cstdio>
#include "object.hh"
#include "env.hh"
#include "eval.hh"

extern Object just_read;
extern "C" int yyparse();
extern "C" FILE *yyin;

using namespace std;

void prompt() {
  cout << "Lisp? " << flush;
}


void toplevel() {
  Environment env; //creating environment

  do {
    prompt();
    yyparse();
    Object l = just_read;
    if (listp(l) && Object_to_string(car(l)) == "setq") {
      env.add_new_binding(Object_to_string(cadr(l)), caddr(l));
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
  } while (!feof(yyin));
}
