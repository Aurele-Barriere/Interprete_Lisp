#include <cstdio>
#include "object.hh"
#include "env.hh"
#include "eval.hh"
#include "toplevel.hh"

using namespace std;
extern int verbose;


int main(int argc, char * argv[]) {
  cout << "Lip Interpreter" << endl;
  cout << "Aurele Barriere & Jeremy Thibault" << endl;
  if ((argc == 2)) {
    if (argv[1][0] == '-' && argv[1][1] == 'v') {
      verbose = 1;
      cout << "Verbose mode" << endl;
    }
  }
  toplevel();
}
