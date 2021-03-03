#include <iostream>
#include <layout.hpp>

std::string slurp(std::istream& in) {
    std::string out, tmp;

    while(std::getline(in, tmp)) {
        out += tmp;
        out += '\n';
    }

    return out;
}

int main() {
    std::cout << "Running klopt..." << std::endl;

    Layout qwerty = Layout::get_qwerty();

    std::string text = slurp(std::cin);
    std::cout << qwerty.score_text(text);
}
