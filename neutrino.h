/*
This class allows all 6 neutrino/antinuetrinos
to be built.
*/

#ifndef NEUTRINO_H
#define NEUTRINO_H

#include"common.h"
#include"particle.h"
#include"lepton.h"

class Neutrino: public Lepton
{
  private:
    string flavour{"electron"};
    bool has_interacted{};

    static const unordered_set<string> valid_flavours;
    string validate_flavour(string& flavour_input);

  public:
    // default neutrino is a zero energy electron neutrino
    Neutrino() : Lepton{0, 0, 0, 0, 0, 0} {}

    Neutrino(string flavour_input, bool is_anti_input, bool has_interacted_input,
             double x_momentum_input, double y_momentum_input, double z_momentum_input);

    Neutrino(const Neutrino& second_neutrino); // copy constructor
    Neutrino(Neutrino&& second_neutrino);// move constructor
    Neutrino& operator=(const Neutrino& second_neutrino); // copy assignment
    Neutrino& operator=(Neutrino&& second_neutrino); // move assignment

    ~Neutrino() override {}

    void set_interaction_status(const bool& has_interacted_input) {has_interacted=has_interacted_input;}
    
    string get_flavour() const {return flavour;}
    bool get_interaction_status() const {return has_interacted;}

    void print_particle_data(bool print_decay_products = false) override;
};

#endif