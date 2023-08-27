#include "Editor.h"
#include "GameLogic.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string.h>
#include <sys/ioctl.h>

using namespace std;

Editor::Editor(File file, Terminal term)
    : m_file(file.getPath()), m_term(term) {

  // Change to thick cursor using DECSCUSR
  write(STDOUT_FILENO, "\e[2 q", 5);

  E.rowoff = 0;
  E.coloff = 0;
  E.rows = m_file.getRows();
  E.numrows = E.rows.size();
  E.windowRows = m_term.getWindowRows();
  E.windowCols = m_term.getWindowColumns();

  draw();

  m_term.enableRawMode();
};

Editor::~Editor() {
  draw();
}

// TODO: This should change to paginate instead of scrolling
void Editor::scroll() {

  auto cursorRow = getCursorRow();
  auto cursorCol = getCursorColumn();

  if (cursorRow < E.rowoff) {
    E.rowoff = cursorRow;
  }
  if (cursorRow >= E.rowoff + E.windowRows) {
    E.rowoff = cursorRow - E.windowRows + 1;
  }
  if (cursorCol < E.coloff) {
    E.coloff = cursorCol;
  }
  if (cursorCol >= E.coloff + E.windowCols) {
    E.coloff = cursorCol - E.windowCols + 1;
  }
}

void Editor::moveCursor(Direction d) {

  int cY = getCursorRow();
  int cX = getCursorColumn();

  if (cY >= E.numrows) return;
  FileRow row = E.rows[cY];

  switch (d) {
  case Direction::BACKWARD:
    if (cX > 0) {
      setCursorColumn(--cX);
    } else if (cY > 0) {
      cY -= 1;
      setCursorRow(cY);
      setCursorColumn(E.rows[cY].length);
    }
    break;
  default: // FORWARD
    if (cX < row.length) {
      setCursorColumn(++cX);
    } else if (cY < E.numrows) {
      setCursorRow(++cY);
      setCursorColumn(0);
    }
    break;
  }
}

void Editor::draw() {
  int y;
  TextBuffer tb;

  scroll();

  for (y = 0; y < m_term.getWindowRows(); y++) {
    int filerow = y + E.rowoff;
    int len = E.rows[filerow].length - E.coloff;

    if (len < 0) {
      len = 0;
    } else if (len > m_term.getWindowColumns()) {
      len = m_term.getWindowColumns();
    }

    char *c = &E.rows[filerow].chars[E.coloff];
    //unsigned char *hl = &E.row[filerow].hl[E.coloff];

    for (int j = 0; j < len; j++) {
      //int color = syntaxToColor(static_cast<Highlight>(hl[j]));
      //char buf[16];
      //int clen = snprintf(buf, sizeof(buf), "\x1b[%dm", color);
      //tb.append(buf, clen);
      tb.append(&c[j], 1);
      //tb.append("\x1b[39m", 5);
    }
    //tb.append("\x1b[39m", 5);
    tb.append("\x1b[K", 3);
    if (y < m_term.getWindowRows() - 1) {
      tb.append("\r\n", 2);
    }
  }

  m_term.writeBuffer(&tb);
}

/*
void Editor::highlight() {
  erow *currRow = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];
  if (currRow) {
    switch (currEvent) {


    case GameLogic::GameEvent::CORRECT:
      currRow->hl[E.rx-1] = (unsigned char)Editor::Highlight::HL_GREEN;
      break;
    case GameLogic::GameEvent::INCORRECT:
      currRow->hl[E.rx-1] = (unsigned char)Editor::Highlight::HL_RED;
      break;
    default:
      currRow->hl[E.rx] = (unsigned char)Editor::Highlight::HL_WHITE;
      break;
    }
  }
}

char Editor::getCurrentChar() {
  erow *row = (E.cy >= E.numrows) ? NULL : &E.row[E.cy];
  if (row)
    return row->chars[E.rx];
  return '\0';
}
*/

int Editor::syntaxToColor(Highlight hl) {
  switch (hl) {
  case Highlight::HL_GREEN:
    return 32;
  case Highlight::HL_RED:
    return 31;
  default:
    return 37;
  }
}

void Editor::setCursorRow(int cY) {
  //m_term.setCursorRow((cY - E.rowoff) + 1);
  m_term.setCursorRow((cY - E.rowoff));
}

void Editor::setCursorColumn(int cX) {
  //m_term.setCursorColumn((cX - E.coloff) + 1);
  m_term.setCursorColumn((cX - E.coloff));
}

int Editor::getCursorRow() {
  //return (m_term.getCursorRow() + E.rowoff) - 1;
  return (m_term.getCursorRow() + E.rowoff);
}

int Editor::getCursorColumn() {
  //return (m_term.getCursorColumn() + E.coloff) - 1;
  return (m_term.getCursorColumn() + E.coloff);
}




