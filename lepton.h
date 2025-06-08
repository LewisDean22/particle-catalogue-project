/*
This is another abstract base class, which specifically
Electron, Neutrino, Muon and Tau derive from.
*/


#ifndef LEPTON_H
#define LEPTON_H

#include"particle.h"
#include"common.h"

class Lepton: public Particle
{
  protected:
    int lepton_number{};

  public:
    Lepton(const bool& is_anti_input, const float& rest_mass_input, const float& charge_input,
           const double& x_momentum_input, const double& y_momentum_input, const double& z_momentum_input);

    Lepton(const Lepton& second_lepton); // copy constructor
    Lepton(Lepton&& second_lepton);// move constructor
    Lepton& operator=(const Lepton& second_lepton); // copy assignment
    Lepton& operator=(Lepton&& second_lepton); // move assignment

    virtual ~Lepton() override {}

    int get_lepton_number() const {return lepton_number;}

    virtual void print_particle_data(bool print_decay_products = false)=0;
};

#endif