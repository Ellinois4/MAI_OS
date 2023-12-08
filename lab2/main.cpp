#include <iostream>
#include <string>
#include <fstream>

#include "include/solution.h"
#include "src/solution.cpp"

int main(int argc, char** argv) {
  std::ifstream file("/home/b_eli/Desktop/MAI_OS/lab2/input_files/input.txt");

  std::vector<std::string> vec;
  std::string str;

  while (file >> str && str.size() != 0) {
    vec.push_back(str);
  }
  
  if (std::atoi(argv[1]) <= 0) {
    std::cerr << "Number of threads <= 0!" << std::endl;
    return -1;
  }
 
  lab2::solution(vec, std::atoi(argv[1]));

  return 0;
}