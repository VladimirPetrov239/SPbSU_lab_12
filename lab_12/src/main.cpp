#include <string>
#include <map>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "matrix.h"


typedef std::map<std::string, Matrix*> var_storage;

int main(int, char **) {
    std::string cmd, arg1, arg2;
    var_storage vars;
    for(int i = 0; i < 10; i++) {
      std::stringstream ss;
      ss << i;
      std::string arg = "$" + ss.str();
      vars[arg] = new Matrix(0, 0);
    }

    while (std::cin) {
        std::cin >> cmd;
        try {
          if (cmd == "exit") {
              return 0;
          } else if (cmd == "load") {
            std::cin >> arg1 >> arg2;
            const char* path = arg2.c_str();
            vars[arg1]->read(path);
          } else if (cmd == "elem") {
              std::size_t i, j;
              std::cin >> arg1 >> i >> j;
              int answer = vars[arg1]->get(i, j);
              std::cout << answer << std::endl;
          } else if (cmd == "print") {
              std::cin >> arg1;
              std::cout << (*vars[arg1]) << std::endl;
          } else if (cmd == "add") {
            std::cin >> arg1 >> arg2;
            *vars[arg1] += *vars[arg2];
          } else if (cmd == "mul") {
              std::cin >> arg1 >> arg2;
              *vars[arg1] *= *vars[arg2];
          }

          else if (cmd == "init") {
              std::size_t rows, cols;
              std::cin >> arg1 >> rows >> cols;
              vars[arg1] = new Matrix(rows, cols);
          }

        } catch (MatrixException& e) {
          std::cout << e.what() << '\n';
        }
    }

    for (var_storage::iterator it = vars.begin(); it != vars.end(); ++it) {
        delete it->second;
    }
}
