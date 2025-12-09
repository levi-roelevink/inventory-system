#pragma once // Ensure this file is included only once during compilation

#include <string>
#include <vector>

class InventorySystem {
public:
  int selectIntBetweenBounds(int lowerBound, int upperBound);
  std::string promptUserForProduct();
  void addProduct();
  void loadMockData();
  std::vector<std::string> loadInventoryToVector();
  void writeVectorToFile(std::vector<std::string> v);
  void removeProduct();
  int listInventory(bool numbered);
  int menuSelection();
  int main();
};