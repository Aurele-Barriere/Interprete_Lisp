#pragma once

#include "cell.hh"
#include "object.hh"
#include <vector>

using namespace std;

#define MEMORY_SIZE 4096

enum flag { free , taken };


class Memory {
private:
Cell cell_vect[MEMORY_SIZE];
flag flags[MEMORY_SIZE];
public:
Memory();
  void allocate_cell();
};
