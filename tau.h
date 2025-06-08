/*
This class allows tau/antitau construction,
each storing a vector of associated decay products.
*/

#ifndef TAU_H
#define TAU_H

#include"common.h"
#include"lepton.h"

class Tau: public Lepton
{
  private:
    // Red and antired quark pairs by default
    vector<shared_ptr<Particle>> decay_products{vector<shared_ptr<Particle>>(3)};

    string decay_product_1{"default particle"}, decay_product_2{"default particle"};
    static const unordered_set<string> valid_tau_decays[6];
    static const unordered_set<string> valid_antitau_decays[6];

    void update_tau_decay_products(const size_t& decay_index); // index in array of valid decays
    void update_antitau_decay_products(const size_t& decay_index);
    void validate_decay_products(string& decay_product_1_input, string& decay_product_2_input,
                                 const bool& is_anti_input);

  public:
    Tau() : Lepton{0, 1800, -1, 0, 0, 0} {}

    Tau(bool is_anti_input, double x_momentum_input, double y_momentum_input,
        double z_momentum_input, string decay_product_1_input, string decay_product_2_input);

    Tau(const Tau& second_tau); // copy constructor
    Tau(Tau&& second_tau);// move constructor
    Tau& operator=(const Tau& second_tau); // copy assignment
    Tau& operator=(Tau&& second_tau); // move assignment

    ~Tau() override {}

    vector<shared_ptr<Particle>> get_decay_products() const {return decay_products;}

    void print_particle_data(bool print_decay_products = false) override;
};

#endif