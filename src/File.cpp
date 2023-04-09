#include "File.h"
#include <stdexcept>
#include <fstream>
#include <iostream>

using namespace std;

File::File(char* path) {
  load(path);
}

File::~File() {

}

void File::load(char* path) {
  fstream file;
  file.open(path, ios::in);

  if (file.is_open()) {
    string buff;

    while (getline(file, buff)) {
      // Add null termination character
      buff.push_back('\0');

      frow newRow = {
        buff,
        buff.size()
      };

      rows.push_back(newRow);
      numrows++;
    }

    file.close();
  }
}
