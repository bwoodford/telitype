#ifndef USERINPUT_H 
#define USERINPUT_H 

#include "Editor.h"

class UserInput {
public:
  UserInput();
  ~UserInput();
  char processInput();

private:
  char readKey();
};
#endif
