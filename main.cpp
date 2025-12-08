#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const string PATH = "inventory.txt";

const int LIST_INVENTORY = 1;
const int ADD_PRODUCT = 2;
const int REMOVE_PRODUCT = 3;
const int EXIT = 4;
const string PRINT_MENU = "**********\n(1) List inventory\n(2) Add "
                          "product\n(3) Remove product\n(4) Exit "
                          "program\n**********\nSelect an option: ";

int selectIntBetweenBounds(int lowerBound, int upperBound) {
  int result;

  cin >> result;
  // TODO: What if input is not an integer
  while (result < lowerBound || result > upperBound) {
    cout << "\nOption must be between " << lowerBound << " and " << upperBound
         << ".\nSelect an option: ";
    cin >> result;
  }

  cout << "\n";
  return result;
}

string promptUserForProduct() {
  cout << "Product name: ";

  string input;
  cin >> input;
  // TODO: What if there's a whitespace character?
  // Also try adding multiple items to see if they're formatted correctly in the
  // txt file

  return input;
}

void addProduct(string path) {
  ofstream of;

  // Opening file using ofstream
  of.open(path, ios::app);
  if (!of) {
    cout << "Unable to find inventory. Please try again." << endl;
    return;
  }

  string val = promptUserForProduct();

  of << val << ",";
  of.close();

  cout << "Added " << val << " to inventory." << endl;
}

int getProductPosition(int productIndex) {
  ifstream file(PATH);
  if (!file.is_open()) {
    throw runtime_error("Error opening file.");
  }

  int pos = 0;
  string line;

  for (int i = 0; i < productIndex; i++) {
    getline(file, line);
    pos += line.length() + 2; // 2 extra for newline \n
  }

  return pos;
}

void loadMockData(string path) {
  // Open file for reading and writing
  ofstream of;
  of.open(path);
  if (!of) {
    cout << "Unable to find inventory. Please try again." << endl;
    return;
  }

  of << "Banana\n";
  of << "Kiwi\n";
  of << "Apple\n";
  of << "Mango\n";

  of.close();
  cout << "Loaded mock data.\n" << endl;
}

vector<string> loadInventoryToVector() {
  vector<string> products;

  ifstream file(PATH);
  if (!file.is_open()) {
    throw runtime_error("Error opening inventory.");
  }

  string line;

  while (getline(file, line)) {
    if (line != "") {
      products.push_back(line);
    }
  }

  return products;
}

void writeVectorToFile(vector<string> v) {
  ofstream file(PATH, ios::trunc);
  if (!file.is_open()) {
    throw runtime_error("Error opening inventory.");
  }

  for (string s : v) {
    file << s + "\n";
  }

  file.close();
}

void removeProduct() {
  vector<string> products = loadInventoryToVector();

  int size = products.size();
  if (size == 0) {
    cout << "Inventory is already empty." << endl;
    return;
  }

  for (int i = 0; i < size; i++) {
    cout << "(" << i + 1 << ") " << products[i] << endl;
  }

  cout << "\nSelect a product to remove (0 to cancel): ";
  int input = selectIntBetweenBounds(0, size);
  if (input == 0) { // Cancel removal
    return;
  }

  products.erase(products.begin() + (input - 1));
  // Write the whole vector without the removed element back to the file
  writeVectorToFile(products);
}

int listInventory(bool numbered) {
  vector<string> products = loadInventoryToVector();
  int size = products.size();

  if (size == 0) {
    cout << "There are currently no items in inventory." << endl;
    cout << "*********";
    return 0;
  }

  cout << "Current inventory:\n**********\n";
  if (numbered) {
    for (int i = 0; i < size; i++) {
      cout << "(" << i + 1 << ") " << products[i] << endl;
    }
  } else {
    for (string p : products) {
      cout << p << endl;
    }
  }

  cout << "*********";

  return size;
}

// 1. Print menu options
// 2. Prompt user for menu selection
// 3. Call selected functionality
int menuSelection() {
  while (true) {
    cout << PRINT_MENU;
    int input = selectIntBetweenBounds(1, 4);

    switch (input) {
    case LIST_INVENTORY:
      listInventory(false);
      break;
    case ADD_PRODUCT:
      addProduct(PATH);
      break;
    case REMOVE_PRODUCT:
      removeProduct();
      break;
    case EXIT:
      return 0;
    }

    cout << "\n";
  }
}

int main() {
  loadMockData(PATH);

  int menuSelector = menuSelection();

  cout << "Goodbye!" << endl;
  return 0;
}