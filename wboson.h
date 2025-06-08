/*
This class allows W^+/"^- objects to be constructed,
each storing a vector of associated decay products.
*/

#ifndef WBOSON_H
#define WBOSON_H

#include"common.h"
#include"particle.h"

class WBoson: public Particle
{
  private:
    string decay_product_1{"default particle"}, decay_product_2{"default particle"};
    // Red and antired quark pairs by default
    vector<shared_ptr<Particle>> decay_products{vector<shared_ptr<Particle>>(2)};

    static const unordered_set<string> valid_w_minus_decays[9];
    static const unordered_set<string> valid_w_plus_decays[9];

    void update_w_minus_decay_products(const size_t& decay_index); // index in array of valid decays
    void update_w_plus_decay_products(const size_t& decay_index); // index in array of valid decays
    void validate_decay_products(string& decay_product_1_input, string& decay_product_2_input,
                                 const bool& is_anti_input);

  public:
    // By convention, W+ is the antiparticle of W-
    WBoson() : Particle{0, 80000, -1, 1, 0, 0, 0} {}

    WBoson(bool is_anti_input, double x_momentum_input, double y_momentum_input, 
           double z_momentum_input, string decay_product_1_input, string decay_product_2_input);
    
    WBoson(const WBoson& second_w_boson); // copy constructor
    WBoson(WBoson&& second_w_boson);// move constructor
    WBoson& operator=(const WBoson& second_w_boson); // copy assignment
    WBoson& operator=(WBoson&& second_w_boson); // move assignment

    ~WBoson() override {}

    vector<shared_ptr<Particle>> get_decay_products() const {return decay_products;}

    void print_particle_data(bool print_decay_products = false) override;
};

#endif