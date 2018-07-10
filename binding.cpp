#include <pybind11/pybind11.h>
#include <readdy/model/potentials/PotentialOrder1.h>
#include <readdy/model/potentials/PotentialOrder2.h>

namespace py = pybind11;

class TestPotential : public readdy::model::potentials::PotentialOrder1{
public:
    explicit TestPotential(particle_type_type ptype) : PotentialOrder1(ptype) {}

    std::string describe() const override {
        return "Test potential of order 1";
    }

    std::string type() const override {
        return "Test potential";
    }

    readdy::scalar calculateEnergy(const readdy::Vec3 &position) const override {
        // @todo implement this
        return 0;
    }

    void calculateForce(readdy::Vec3 &force, const readdy::Vec3 &position) const override {
        // @todo implement this
        force += {.1, .1, .1};
    }

};

class MyPairPotential : public readdy::model::potentials::PotentialOrder2 {
public:
    MyPairPotential(particle_type_type type1, particle_type_type type2, readdy::scalar cutoff)
            : PotentialOrder2(type1, type2), cutoff(cutoff) {}

    std::string describe() const override {
        return "MyPairPotential of order 2";
    }

    std::string type() const override {
        return "MyPairPotential";
    }

    readdy::scalar calculateEnergy(const readdy::Vec3 &x_ij) const override {
        // @todo implement this
        return 2*x_ij * x_ij;
    }

    void calculateForce(readdy::Vec3 &force, const readdy::Vec3 &x_ij) const override {
        // @todo implement this
        const auto distSquared = x_ij*x_ij;
        force -= distSquared * readdy::Vec3{1., 1., 1.};
    }

    readdy::scalar getCutoffRadiusSquared() const override {
        // @todo implement this
        return cutoff*cutoff;
    }
private:
    readdy::scalar cutoff;
};

PYBIND11_MODULE (mypot, m) {
    py::module::import("readdy");
    py::class_<TestPotential, readdy::model::potentials::PotentialOrder1>(m, "MyExternalPotential")
            .def(py::init<readdy::particle_type_type>());
    py::class_<MyPairPotential, readdy::model::potentials::PotentialOrder2>(m, "MyPairPotential")
            .def(py::init<readdy::particle_type_type, readdy::particle_type_type, readdy::scalar>());
}

