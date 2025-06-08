#include"common.h"
#include"four_momentum.h"
#include"particle.h"

void Particle::set_energy(const double& energy_input)
{   
    try
    {
      if(energy_input < rest_mass) // Checks energy never below rest mass energy
      {
        throw std::invalid_argument("Inputted energy below rest mass energy.");
      }
    }
    catch(const std::invalid_argument& error)
    {
      std::cerr<<endl<<"Error: " <<error.what()<<endl;
      exit(EXIT_FAILURE);
    }

    double old_momentum_magnitude{four_momentum->get_3_momentum_magnitude()};
    four_momentum->set_energy(energy_input);

    if(four_momentum->get_invariant_mass() != rest_mass)
    {
      double required_momentum_magnitude{std::sqrt(pow(energy_input, 2) - 
                                         pow(rest_mass, 2))};

      bool x_check{four_momentum->get_x_momentum() == 0};
      bool y_check{four_momentum->get_y_momentum() == 0};
      bool z_check{four_momentum->get_z_momentum() == 0};
      if(x_check && y_check && z_check)
      {
        four_momentum->set_x_momentum(required_momentum_magnitude / 3);
        four_momentum->set_y_momentum(required_momentum_magnitude / 3);
        four_momentum->set_z_momentum(required_momentum_magnitude / 3);
      }
      
      else
      {
        four_momentum->set_x_momentum(four_momentum->get_x_momentum() * 
                                      required_momentum_magnitude / old_momentum_magnitude);
        four_momentum->set_y_momentum(four_momentum->get_y_momentum() * 
                                      required_momentum_magnitude / old_momentum_magnitude);
        four_momentum->set_z_momentum(four_momentum->get_z_momentum() * 
                                      required_momentum_magnitude / old_momentum_magnitude);
      }
    }
}

double Particle::calculate_valid_energy(const float& rest_mass_input, const double& x_momentum_input,
                                        const double& y_momentum_input, const double& z_momentum_input)
{
  double squared_valid_energy{pow(rest_mass_input, 2) + pow(x_momentum_input, 2) + pow(y_momentum_input, 2) + 
                              pow(z_momentum_input, 2)};
  return std::sqrt(squared_valid_energy);
}

Particle::Particle(const bool& is_anti_input, const float& rest_mass_input, const float& charge_input,
                   const float& spin_input, const double& x_momentum_input, const double&  y_momentum_input,
                   const double& z_momentum_input) :

    is_anti{is_anti_input}, rest_mass{rest_mass_input}, charge{charge_input}, spin{spin_input},
    four_momentum{make_unique<FourMomentum>(calculate_valid_energy(rest_mass_input, x_momentum_input,
                                                                   y_momentum_input, z_momentum_input),
    x_momentum_input, y_momentum_input, z_momentum_input)} {}

void Particle::print_particle_data(bool print_decay_products)
{
  cout<<setprecision(3)<<
  "Rest mass (MeV) = "<<rest_mass<<endl<<
  "Charge (e) = "<<charge<<endl<<
  "Spin = "<<spin<<endl<<
  "Energy (MeV) = "<<four_momentum->get_energy()<<endl;
  four_momentum->print_data();
}

Particle::Particle(const Particle& particle_2)
{
  cout<<"Calling particle copy constructor..."<<endl;
  is_anti = particle_2.is_anti;
  rest_mass = particle_2.rest_mass;
  charge = particle_2.charge;
  four_momentum = make_unique<FourMomentum>(*particle_2.four_momentum);
}

Particle& Particle::operator=(const Particle& particle_2)
{
  cout<<"Calling particle copy assignment..."<<endl;
  if(&particle_2 != this)
  {
  is_anti = particle_2.is_anti;
  rest_mass = particle_2.rest_mass;
  charge = particle_2.charge;
  four_momentum = make_unique<FourMomentum>(*particle_2.four_momentum);
  }
  return *this;
}

Particle::Particle(Particle&& particle_2)
{
  cout<<"Calling particle move constructor..."<<endl;
  is_anti = particle_2.is_anti;
  rest_mass = particle_2.rest_mass;
  charge = particle_2.charge;
  four_momentum = make_unique<FourMomentum>(*particle_2.four_momentum);

  particle_2.is_anti = 0;
  particle_2.rest_mass = 0;  
  particle_2.charge = 0; 
  *particle_2.four_momentum = FourMomentum();
}

Particle& Particle::operator=(Particle&& particle_2)
{
  cout<<"Calling particle move assignment..."<<endl;
  if(&particle_2 != this)
  {
    is_anti = 0;
    rest_mass = 0; 
    charge = 0; 
    *four_momentum = FourMomentum();

    swap(is_anti, particle_2.is_anti);
    swap(rest_mass, particle_2.rest_mass);
    swap(charge, particle_2.charge);
    swap(four_momentum, particle_2.four_momentum);
  }
  return *this; 
}