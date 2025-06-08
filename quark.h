/*
This class allows all 12 quarks/antiquarks to be constructed.
*/


#ifndef QUARK_H
#define QUARK_H

#include"particle.h"
#include"common.h"
#include"gluon.h"

class Quark: public Particle
{
  private:
    string flavour{"up"}, quark_colour{"red"};
    float quark_number{1/3.0f};

    static const unordered_set<string> valid_flavours;
    static const map<string, const float> quark_rest_masses, quark_charges;

    string validate_flavour(string& flavour_input);

    float get_valid_quark_mass(string& flavour_input);
    float get_valid_quark_charge(string& flavour_input);

  public:
    // Default quark is a red up quark at rest
    Quark() : Particle{0, quark_rest_masses.at("up"), 2/3.0f, 0.5f, 0, 0, 0} {}

    Quark(string flavour_input, string colour_charge_input, bool is_anti_input,
          double x_momentum_input, double y_momentum_input, double z_momentum_input);

    Quark(const Quark& second_quark); // copy constructor
    Quark(Quark&& second_quark);// move constructor
    Quark& operator=(const Quark& second_quark); // copy assignment
    Quark& operator=(Quark&& second_quark); // move assignment

    ~Quark() override {}

    void set_colour(string& colour_input) {Gluon::validate_colour(colour_input, is_anti);}

    string get_flavour() const {return flavour;}
    string get_colour() const {return quark_colour;}
    float get_quark_number() const {return quark_number;}

    void print_particle_data(bool print_decay_products = false) override;
};

#endif