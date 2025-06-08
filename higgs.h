/*
This class allows the construction of Higgs boson objects,
each storing a vector of associated decay products.
*/

#ifndef HIGGS_H
#define HIGGS_H

#include"common.h"
#include"particle.h"

class HBoson: public Particle
{
  private:
    string decay_type{"default decay"};
    // Red and antired quark pairs by default
    vector<shared_ptr<Particle>> decay_products{vector<shared_ptr<Particle>>(2)}; 

    static const string valid_decay_types[4];

    void update_decay_products(const size_t& decay_index); // index in array of valid decays
    void validate_decay_products(string& decay_type_input);

  public:
    HBoson() : Particle{0, 126000, 0, 0, 0, 0, 0} {}

    HBoson(double x_momentum_input, double y_momentum_input, double z_momentum_input,
           string decay_type_input);

    HBoson(const HBoson& second_higgs); // copy constructor
    HBoson(HBoson&& second_higgs);// move constructor
    HBoson& operator=(const HBoson& second_higgs); // copy assignment
    HBoson& operator=(HBoson&& second_higgs); // move assignment

    ~HBoson() override {}

    vector<shared_ptr<Particle>> get_decay_products() const {return decay_products;}

    void print_particle_data(bool print_decay_products = false) override;
};

#endif