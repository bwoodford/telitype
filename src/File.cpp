#include "File.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

using namespace std;

File::File(char* path): path(path) {
  numrows = 0;
  load(path);
}

File::~File() {

}

void File::load(char* path) {
  fstream file;
  file.open(path, ios::in);

  if (file.is_open()) {
    string buff = "";

    while (getline(file, buff)) {
      rows.push_back(FileRow(buff, buff.length()));
      numrows++;
    }

    file.close();
  }
}

vector<FileRow> File::getRows() {
  return rows;
}

char* File::getPath() {
  return path;
}
