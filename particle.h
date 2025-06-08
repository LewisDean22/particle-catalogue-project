/*
This is the abstract base class from which all particle types are derived.
*/


#ifndef PARTICLE_H
#define PARTICLE_H

#include"common.h"
#include"four_momentum.h"

class Particle
{
  protected:
    bool is_anti{};
    float spin{}, charge{}, rest_mass{};
    // Unique so cannot be modified outside of class, hence validation cannot be bypassed
    unique_ptr<FourMomentum> four_momentum;
    
    double calculate_valid_energy(const float& rest_mass_input,
                                  const double& x_momentum_input,
                                  const double& y_momentum_input,
                                  const double& z_momentum_input);
    template<typename setter> void set_i_momentum(
      const double& i_momentum_input, setter&& setter_input);

  public:
    friend class Catalogue; // Needed so overloaded addition can be used in catalogue

    Particle(const bool& is_anti_input, const float& rest_mass_input, const float& charge_input,
             const float& spin_input, const double& x_momentum_input, const double&  y_momentum_input,
             const double& z_momentum_input);

    Particle(const Particle& second_particle); // copy constructor
    Particle(Particle&& second_particle);// move constructor
    Particle& operator=(const Particle& second_particle); // copy assignment
    Particle& operator=(Particle&& second_particle); // move assignment

    virtual ~Particle() {} // Virtual because abstract base class
    
    bool is_antiparticle() const {return is_anti;}
    double get_energy() const {return four_momentum->get_energy();}
    double get_x_momentum() const {return four_momentum->get_x_momentum();}
    double get_y_momentum() const {return four_momentum->get_y_momentum();}
    double get_z_momentum() const {return four_momentum->get_z_momentum();}
    double get_rest_mass() const {return rest_mass;}
    int get_charge() const {return charge;}
    float get_spin() const {return spin;}

    void set_energy(const double& energy_input);
    void set_x_momentum(const double& x_momentum_input) {
      set_i_momentum(x_momentum_input, &FourMomentum::set_x_momentum);}
    void set_y_momentum(const double& y_momentum_input) {
      set_i_momentum(y_momentum_input, &FourMomentum::set_y_momentum);}
    void set_z_momentum(const double& z_momentum_input) {
      set_i_momentum(z_momentum_input, &FourMomentum::set_z_momentum);}

    virtual void print_particle_data(bool print_decay_products = false)=0; // default value of false
    void print_momentum_vector() const {four_momentum->print_data();}
};

template<typename setter> void Particle::set_i_momentum(
      const double& i_momentum_input, setter&& setter_input)
{
   (four_momentum.get()->*setter_input)(i_momentum_input); // Uses template setter to set momentum component
   if(four_momentum->get_invariant_mass() != rest_mass) // Checks if special relativity is respected
   {
     double required_energy = std::sqrt(pow(rest_mass, 2) +
                                        pow(four_momentum->get_3_momentum_magnitude(), 2));
     four_momentum->set_energy(required_energy); // Corrects energy so particle is on-shell
   }
}

#endif