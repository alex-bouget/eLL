#include <string>
#include <vector>
#include <iostream>

int main(int argc, char** argv) {
    std::vector<std::string> argument(argc);
    for (int i = 0; i < argc; i++) {
        argument[i] = argv[i];
        std::cout << argument[i] << '\n';
    }
}