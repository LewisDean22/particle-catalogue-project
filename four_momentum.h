/*
This is the interface of the FourMomentum class. Instances of this
are included within all Particle instances.
*/

#ifndef FOUR_MOMENTUM_H
#define FOUR_MOMENTUM_H

#include"common.h"

class FourMomentum
{
  friend FourMomentum operator+(const FourMomentum& vector_1, const FourMomentum& vector_2);
  friend FourMomentum operator-(const FourMomentum& vector_1, const FourMomentum& vector_2);
  friend double dotProduct(const FourMomentum& vector_1, const FourMomentum& vector_2); // Minkowski product

  private:
    // Natural units here, so all components have units MeV
    vector<double> four_momentum{vector<double>(4)};

    // Checks energy is positive
    double validate_energy_input(const double& energy_input);

  public:
    FourMomentum() {};

    FourMomentum(double energy_input, double x_momentum_input, double y_momentum_input,
                 double z_momentum_input);
    
    FourMomentum(const FourMomentum& second_momentum); // copy constructor
    FourMomentum(FourMomentum&& second_momentum); // move constructor
    FourMomentum& operator=(const FourMomentum& second_momentum); // copy assignment
    FourMomentum& operator=(FourMomentum&& second_momentum); // move assignment

    ~FourMomentum() {} 

    double get_energy() const {return four_momentum[0];}
    double get_x_momentum() const {return four_momentum[1];}
    double get_y_momentum() const {return four_momentum[2];}
    double get_z_momentum() const {return four_momentum[3];}
    double get_3_momentum_magnitude();
    double get_invariant_mass();
    
    void set_energy(const double& energy_input);
    void set_x_momentum(const double& x_momentum_input) {four_momentum[1]=x_momentum_input;}
    void set_y_momentum(const double& y_momentum_input) {four_momentum[2]=y_momentum_input;}
    void set_z_momentum(const double& z_momentum_input) {four_momentum[3]=z_momentum_input;}

    void print_data();
};

#endif