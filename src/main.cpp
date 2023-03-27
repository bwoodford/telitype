#include "Editor.h"
#include <iostream>
#include <stdexcept>

using namespace std;

int main(int argc, char *argv[]) {
  try {

    Editor e;

  } catch (std::exception& e) {

    cerr << e.what() << endl;
    return -1;

  }

  return 0;
}

