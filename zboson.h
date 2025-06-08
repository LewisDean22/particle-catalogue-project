/*
This class allows for the construction of Z boson objects,
each storing a vector of associated decay products.
*/

#ifndef ZBOSON_H
#define ZBOSON_H

#include"common.h"
#include"particle.h"

class ZBoson: public Particle
{
  private:
    string decay_product_1{"default particle"}, decay_product_2{"default particle"};
    // Red and antired quark pairs by default
    vector<shared_ptr<Particle>> decay_products{vector<shared_ptr<Particle>>(2)};

    static const unordered_set<string> valid_decay_products[11];

    void update_decay_products(const size_t& decay_index); // index in array of valid decays
    void validate_decay_products(string& decay_product_1_input, string& decay_product_2_input);

  public:
    ZBoson() : Particle{0, 91000, 0, 1, 0, 0, 0} {}

    ZBoson(double x_momentum_input, double y_momentum_input, double z_momentum_input,
           string decay_product_1_input, string decay_product_2_input);
    
    ZBoson(const ZBoson& second_z_boson); // copy constructor
    ZBoson(ZBoson&& second_z_boson);// move constructor
    ZBoson& operator=(const ZBoson& second_z_boson); // copy assignment
    ZBoson& operator=(ZBoson&& second_z_boson); // move assignment

    ~ZBoson() override {}

    vector<shared_ptr<Particle>> get_decay_products() const {return decay_products;}

    void print_particle_data(bool print_decay_products = false) override;
};

#endif