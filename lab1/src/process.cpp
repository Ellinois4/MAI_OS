#include "../include/process.hpp"


std::string& str_invert(std::string& str) {
    for(size_t i = 0; i < str.size()/2; ++i) {
        std::swap(str[i], str[(str.size() - 1) - i]);
    }
    return str;
}

void process_handler() {
 std::string buf;

  while(true) {
    getline(std::cin, buf);
    std::string new_str;
    new_str = str_invert(buf);

    std::cout << new_str.c_str() << std::endl;
  }
}