#include "GameLogic.h"
#include <stdexcept>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
  try {
      
    if (argc >= 2)
      GameLogic::start(argv[1]);
      
  } catch (std::exception &e) {
    cerr << e.what() << endl;
    return -1;
  }
  return 0;
}

