#include <pybind11/pybind11.h>
#include <optimizer.hpp>
#include <phys_layout.hpp>

namespace py = pybind11;

class PyOptimizer {
    Optimizer o;

public:
    PyOptimizer(float initial_temp, int k_max) : o(initial_temp, k_max) {}

    std::string compute_optimal(int time_s, const std::string &text) {
        Model m;
        auto [best, score] = o.compute_optimal(m, 1, time_s, text);
        return PhysLayout::get_iso_gb().stringify(best);
    }
};

PYBIND11_MODULE(kloptpy, m) {
    py::class_<PyOptimizer>(m, "Optimizer")
        .def(py::init<float, int>())
        .def("compute_optimal", &PyOptimizer::compute_optimal);
}
