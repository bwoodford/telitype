#ifndef USERINPUT_H 
#define USERINPUT_H 

#include "Editor.h"

class UserInput {
public:
  UserInput();
  ~UserInput();
  char getKey();

private:
  char readKey();
};
#endif
