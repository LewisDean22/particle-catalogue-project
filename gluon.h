/*
This class allows gluons to be constructed.
*/

#ifndef GLUON_H
#define GLUON_H

#include"common.h"
#include"particle.h"

class Gluon: public Particle
{
  private:
    string gluon_colour{"red"}, gluon_anticolour{"antired"};

    static const unordered_set<string> valid_colours;
    static const unordered_set<string> valid_anticolours;
    static string validate_colour(string& colour_input, const bool& is_anti_input);

  public:
    friend class Quark; // Allows quark class to use colour validation methods

    // Default gluon has zero energy
    Gluon() : Particle{0, 0, 0, 1, 0, 0, 0} {}

    Gluon(string gluon_colour_input, string gluon_anticolour_input,
          double x_momentum_input, double y_momentum_input, double z_momentum_input);

    Gluon(const Gluon& second_gluon); // copy constructor
    Gluon(Gluon&& second_gluon);// move constructor
    Gluon& operator=(const Gluon& second_gluon); // copy assignment
    Gluon& operator=(Gluon&& second_gluon); // move assignment

    ~Gluon() override {}

    void set_gluon_colour(string& gluon_colour_input) {validate_colour(gluon_colour_input, 0);}
    void set_gluon_anticolour(string& gluon_anticolour_input) {validate_colour(gluon_anticolour_input, 1);}

    void print_particle_data(bool print_decay_products = false) override;
};

#endif