#include <iostream>
#include <layout.hpp>
#include <model.hpp>
#include <optimizer.hpp>
#include <phys_layout.hpp>

std::string slurp(std::istream& in) {
    std::string out, tmp;

    while(std::getline(in, tmp)) {
        out += tmp;
        out += '\n';
    }

    return out;
}

int main() {
    std::cout << "Running klopt... (reading from stdin)" << std::endl;
    std::cout << "---" << std::endl;
    std::string text = slurp(std::cin);

    Model m;

    auto phys = PhysLayout::get_iso_gb();
    auto qwerty = Layout::get_qwerty();
    auto qwerty_score = m.score_text(qwerty, text);

    Optimizer o(qwerty_score / 200.0f, 50000);
    auto best = o.compute_optimal(m, 3, 10, text);

    std::cout << phys.stringify(best.layout);
    std::cout << best.score << std::endl;

    std::cout << "QWERTY scores " << qwerty_score << std::endl;;
}
