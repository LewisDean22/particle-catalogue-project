/*
This class allows photon construction.
*/

#ifndef PHOTON_H
#define PHOTON_H

#include"common.h"
#include"particle.h"

class Photon: public Particle
{
  public:
    // Default photon has zero energy
    Photon() : Particle{0, 0, 0, 1, 0, 0, 0} {}

    Photon(double x_momentum_input, double y_momentum_input, double z_momentum_input) :
    Particle{0, 0, 0, 1, x_momentum_input, y_momentum_input, z_momentum_input} {}

    ~Photon() override {}

    void print_particle_data(bool print_decay_products = false) override
    {
      cout<<endl<<"photon properties:" <<endl<<
      "------------------" <<endl;
      Particle::print_particle_data();
    }
};

#endif