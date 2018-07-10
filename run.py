import numpy as np
import readdy
import mypot as mp

system = readdy.ReactionDiffusionSystem([10, 10, 10])
system.add_species("A", 0.001)
system.potentials.add_custom_external("A", mp.MyExternalPotential)
system.potentials.add_custom_pair("A", "A", mp.MyPairPotential, .1)
sim = system.simulation(kernel="SingleCPU")

sim.add_particles("A", np.random.random((3000, 3)))
sim.run(10000, .1)


