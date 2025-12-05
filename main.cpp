#include <cstddef>
#include <fstream>
#include <iostream>

using namespace std;

const string PATH = "inventory.txt";

fstream openFile(string path) {
  // Open file for reading and writing
  fstream stream(path, ios::in | ios::out);
  if (!stream) {
    // File did not exist yet, so a file is created with an output file stream
    ofstream oStr(path);
    oStr.close();

    return fstream(path, ios::in | ios::out);
  }

  return stream;
}

void printFileContents(fstream *file) {
  string s;
  string prev;
  while (true) {
    prev = s;
    string s;
    getline(*file, s);

    if (s == prev) {
      break;
    }

    cout << s << endl;
  }
}

string promptUser() {
  cout << "Product name: ";

  string input;

  cin >> input;
  // TODO: What if there's a whitespace character?
  // Also try adding multiple items to see if they're formatted correctly in the
  // txt file

  return input;
}

void addItem(fstream *file) {
  string val = promptUser();
  *file << val;
}

int main() {
  fstream file = openFile(PATH);

  file << "Banana\n";
  file << "Blueberries\n";
  file << "Apple\n";
  file << "Mango\n";
  file << "Kiwi\n";

  addItem(&file);

  // Reset file position pointer before switching from write to read
  file.seekg(0);
  printFileContents(&file);

  file.close();

  return 0;
}