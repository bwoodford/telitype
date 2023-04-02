#include "UserInput.h"
#include <cerrno>
#include <unistd.h>
#include <stdexcept>

#define CTRL_KEY(k) ((k) & 0x1f)

using namespace std;

UserInput::UserInput() {}
UserInput::~UserInput() {}

char UserInput::processInput() {
  char key = readKey();
  // check if user input is in ASCII range
  switch (key) {
  case CTRL_KEY('q'):
    // Figure out a way to clean this up with a control event of some sort
    exit(0);
    return '0';
  default:
    return key;
  }
}

char UserInput::readKey() {
    int nread;
    char c;
    while ((nread = read(STDIN_FILENO, &c, 1)) != 1) {
        if (nread == -1 && errno != EAGAIN) throw std::runtime_error("readKey");
    }
    return c;
}
