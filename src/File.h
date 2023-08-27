#ifndef FILE_H
#define FILE_H

#include <string>
#include <vector>
#include "FileRow.h"

using namespace std;

class File {
public:
  File(char* filePath);
  ~File();

  char* getPath(); 
  vector<FileRow> getRows();

private:
  std::vector<FileRow> rows;
  int numrows;
  char* path;

  void load(char* path);
};
#endif
