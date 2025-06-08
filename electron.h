/*
This class allows electron/antielectron construction.
*/

#ifndef ELECTRON_H
#define ELECTRON_H

#include"common.h"
#include"particle.h"
#include"lepton.h"

class Electron: public Lepton
{
  private:
    vector<double> calorimeter_deposits{vector<double>(4)};
    vector<double> validate_calorimeter_deposits(const double& EM_1_input,
                                                 const double& EM_2_input, 
                                                 const double& HAD_1_input,
                                                 const double& HAD_2_input);
  public:
    // Need calorimeter layers each with rest_mass energy/4 ??
    Electron() : Lepton{0, 0.51f, -1, 0, 0, 0} {}

    Electron(bool is_anti_input, double x_momentum_input,
             double y_momentum_input, double z_momentum_input,
             double EM_1_input, double EM_2_input, double HAD_1_input,
             double HAD_2_input);

    Electron(const Electron& second_electron); // copy constructor
    Electron(Electron&& second_electron);// move constructor
    Electron& operator=(const Electron& second_electron); // copy assignment
    Electron& operator=(Electron&& second_electron); // move assignment

    ~Electron() override {}

    double get_EM_1() const {return calorimeter_deposits[0];}
    double get_EM_2() const {return calorimeter_deposits[2];}
    double get_HAD_1() const {return calorimeter_deposits[2];}
    double get_HAD_2() const {return calorimeter_deposits[3];}

    void set_EM_1(const double& EM_1_input);
    void set_EM_2(const double& EM_2_input);
    void set_HAD_1(const double& HAD_1_input);
    void set_HAD_2(const double& HAD_2_input);

    void print_particle_data(bool print_decay_products = false) override;
};

#endif