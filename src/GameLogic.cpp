#include "GameLogic.h"
#include "Editor.h"
#include "UserInput.h"

using namespace std;

GameLogic::GameLogic() {}
GameLogic::~GameLogic() {}

void GameLogic::start(char *file) {
  Editor e;
  UserInput ui;

  e.editorOpen(file);
  e.refreshScreen();

  while (1) {
    int c = (int)ui.processInput();

    if (c != 8 && c != 127) {
      e.moveCursor(Editor::Direction::FORWARD);
      if (e.getCurrentChar() == c) {
        e.currEvent = GameLogic::GameEvent::CORRECT;
      } else {
        e.currEvent = GameLogic::GameEvent::INCORRECT;
      }
    } else {
      e.moveCursor(Editor::Direction::BACKWARD);
      e.currEvent = GameLogic::GameEvent::REVERT;
    }

    e.refreshScreen();
  }
}
