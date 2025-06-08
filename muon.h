/*
This class allows muon/antimuon construction.
*/

#ifndef MUON_H
#define MUON_H

#include"common.h"
#include"particle.h"
#include"lepton.h"

class Muon: public Lepton
{
  private:
    bool is_isolated{};

  public:

    Muon() : Lepton{0, 106, -1, 0, 0, 0} {}

    Muon(bool is_anti_input, bool is_isolated_input, double x_momentum_input,
         double y_momentum_input, double z_momentum_input);

    Muon(const Muon& second_muon); // copy constructor
    Muon(Muon&& second_muon);// move constructor
    Muon& operator=(const Muon& second_muon); // copy assignment
    Muon& operator=(Muon&& second_muon); // move assignment

    ~Muon() override {}

    bool get_isolation_status() const {return is_isolated;}
    void set_isolation_status(const bool& is_isolated_input) {is_isolated = is_isolated_input;}  

    void print_particle_data(bool print_decay_products = false) override;
};

#endif