/*
  Creating a toplevel
*/

#include "toplevel.hh"
#include "memory.hh"
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
extern Memory mem;
bool end;

void prompt() {
  cout << "Lisp? " << flush;
}

void toplevel_eval(Object l, Environment& env) {
  if (listp(l) && symbolp(car(l)) && Object_to_string(car(l)) == "setq") {
    env.add_new_binding(Object_to_string(cadr(l)), eval(caddr(l), env));
  }
  else if (listp(l) && symbolp(car(l)) && Object_to_string(car(l)) == "printenv") {
    env.print(cout);
    cout << endl;
  }
  else if (listp(l) && symbolp(car(l)) && Object_to_string(car(l)) == "loadfile" && stringp(cadr(l))) {
    eval_file((Object_to_string(cadr(l)).c_str()), env);
  }
  else if (listp(l) && symbolp(car(l)) && Object_to_string(car(l)) == "exit") {
    end = true;
  }
  else {
    try {
      cout << mem.at(eval(l, env)) << endl;
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

void eval_file(const char* file, Environment& env) {
  FILE* fh = fopen(file, "r");
  if (fh != NULL) {
    yyrestart(fh);
    using_file = 1;
    main_loop(env);
    fclose(fh);
    yyrestart(stdin);
    using_file = 0;
  }
}

void main_loop(Environment& env) {

  unsigned i = 0;

  if (!using_file) {
    prompt();
  }

  while (!end && yyparse() == 0) {
    Object l = just_read;
    toplevel_eval(l, env);
    mem.print_vect();
    if (++i % 3 == 0) {

      mem.garbage_collection(env);
    }
    if (!using_file && !end) {
      prompt();
    }

  }

}

void toplevel() {
  end = false;
  Environment env; //creating environment

  if (using_file) {
    eval_file(filename, env);
  }
  end = false;
  main_loop(env);
}
