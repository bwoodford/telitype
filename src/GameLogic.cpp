#include "GameLogic.h"
#include "File.h"
#include "Editor.h"
#include "UserInput.h"

using namespace std;

GameLogic::GameLogic() {}
GameLogic::~GameLogic() {}

void GameLogic::start(char *filePath) {

  File file(filePath);

  Terminal terminal;
  terminal.setCursorColumn(0);
  terminal.setCursorRow(0);

  Editor editor(file, terminal);

  UserInput input;

  while (1) {
    int c = (int)input.getKey();

    if (c != 8 && c != 127) {
      editor.moveCursor(Editor::Direction::FORWARD);
      /*
      if (editor.getCurrentChar() == c) {
        //e.currEvent = GameLogic::GameEvent::CORRECT;
      } else {
        //e.currEvent = GameLogic::GameEvent::INCORRECT;
      }
      */
    } else {
      editor.moveCursor(Editor::Direction::BACKWARD);
      //e.currEvent = GameLogic::GameEvent::REVERT;
    }

    editor.draw();
  }
}
