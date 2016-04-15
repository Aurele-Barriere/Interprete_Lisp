#include <cstdio>
#include <cstring>
#include <unistd.h>
#include "toplevel.hh"
#include "memory.hh"


using namespace std;
extern int verbose;
extern int using_file;
extern char filename[255];
extern Memory mem;


int parse_arguments(int argc, char * argv[]) {
  int c;
  while((c =  getopt(argc, argv, "hvf:")) != -1) {
    switch (c) {
      case 'v':
        verbose = 1;
        break;
      case 'f':
        using_file = 1;
        strcpy(filename, optarg);
        break;
      case 'h':
        cout << "Basic Lisp Interpreter by Aurele Barriere & Jeremy Thibault" << endl;
        cout << "Arguments:" << endl;
        cout << "-v \t\t -- Verbose mode" << endl;
        cout << "-h \t\t -- Prints this help" << endl;
        cout << "-f filename \t -- Loads the file filename" << endl;
        return 1;
      case '?':
        cout << "Wrong arguments. Use -h option for more informatin" << endl;
        return 1;
    }
  }
  return 0;
}

int main(int argc, char * argv[]) {
  if (parse_arguments(argc, argv) == 0) {
    cout << "Lisp Interpreter" << endl;
    cout << "Aurele Barriere & Jeremy Thibault" << endl;
    if (verbose) {
      cout << "Verbose mode " << endl;
    }
    toplevel();
  }
}
