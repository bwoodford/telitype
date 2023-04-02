#include "Editor.h"
#include "UserInput.h"
#include <iostream>
#include <stdexcept>
#include <cstdio>

using namespace std;

int main(int argc, char *argv[]) {
  try {
    Editor e;
    UserInput ui;

    if (argc >= 2) e.editorOpen(argv[1]);

    while (1) {
      e.refreshScreen();

      int c = (int)ui.processInput();

      // Also need to check if we should go back and not advance
      if (c != 8 && c != 127) {
        // Compare with current character

        if (e.getCurrentChar() != c) {
          
        } else {

        }
        e.moveCursor(Editor::direction::FORWARD);

      } else {
        // remove coloring past the cursor location
        e.moveCursor(Editor::direction::BACKWARD);
      }
    }

  } catch (std::exception& e) {
    cerr << e.what() << endl;
    return -1;
  }

  return 0;
}

