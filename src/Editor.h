#ifndef EDITOR_H
#define EDITOR_H

#include "File.h"
#include "GameLogic.h"
#include "Terminal.h"
#include "iostream"
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

class Editor {
public:
  Editor(File file, Terminal term);
  ~Editor();

  enum class Direction { FORWARD, BACKWARD };

  void draw();
  char getCurrentChar();
  void moveCursor(Direction d);

private:
  File m_file;
  Terminal m_term;

  enum class Highlight : unsigned char {
    HL_WHITE,
    HL_GREEN,
    HL_RED,
  };

  struct Config {
    int coloff;
    int rowoff;
    int windowRows;
    int windowCols;
    int numrows;
    vector<FileRow> rows;
  };

  Config E;

  //void updateRow(File::FileRow row);
  void scroll();

  int syntaxToColor(Highlight hl);

  void highlight();
  void updateSyntaxRow(FileRow row);
  void colorCharacters();


  void setCursorColumn(int cX);
  void setCursorRow(int cY);

  int getCursorRow();
  int getCursorColumn();

};
#endif
