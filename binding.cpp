#include <pybind11/pybind11.h>
#include <readdy/model/potentials/PotentialOrder1.h>
#include <readdy/model/potentials/PotentialOrder2.h>
#include <iostream>

namespace py = pybind11;
using ParticleType = readdy::model::Particle::type_type;

class MyExternalPotential : public readdy::model::potentials::PotentialOrder1{
public:
    explicit MyExternalPotential(ParticleType ptype) : PotentialOrder1(ptype) {}

    std::string describe() const override {
        return "MyExternalPotential of order 1";
    }

    std::string type() const override {
        return "MyExternalPotential";
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
    MyPairPotential(ParticleType type1, ParticleType type2, readdy::scalar cutoff)
            : PotentialOrder2(type1, type2), cutoff(cutoff) {}

    std::string describe() const override {
        //py::gil_scoped_release release;
        //std::cout << "pair force" << std::endl;
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
    //py::module::import("readdy._internal.readdybinding.api");
    //py::object potO1 = (py::object) py::module::import("readdy._internal.readdybinding.api").attr("PotentialOrder1");
    //py::object potO2 = (py::object) py::module::import("readdy._internal.readdybinding.api").attr("PotentialOrder1");

    //py::class_<MyExternalPotential>(m, "MyExternalPotential", potO1).def(py::init<ParticleType>());
    //py::class_<MyPairPotential>(m, "MyPairPotential", potO2).def(py::init<ParticleType, ParticleType, readdy::scalar>());

    //py::class_<readdy::model::potentials::PotentialOrder1>(m, "PotentialOrder1");
    py::class_<MyExternalPotential, readdy::model::potentials::PotentialOrder1>(m, "MyExternalPotential")
            .def(py::init<ParticleType>());

    //py::class_<readdy::model::potentials::PotentialOrder2>(m, "PotentialOrder2");
    py::class_<MyPairPotential, readdy::model::potentials::PotentialOrder2>(m, "MyPairPotential")
            .def(py::init<ParticleType, ParticleType, readdy::scalar>());
}


