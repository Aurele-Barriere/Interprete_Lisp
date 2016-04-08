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

void prompt() {
  cout << "Lisp? " << flush;
}


void toplevel() {
  Environment env; //creating environment
  int eof = 0; //boolean for end of file, modified by read


  do {
    prompt();

    Object l = read(&eof);

    if (listp(l) && Object_to_string(car(l)) == "setq") {
      env.add_new_binding(Object_to_string(cadr(l)), eval(caddr(l), env));
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
  } while (!eof);
}
