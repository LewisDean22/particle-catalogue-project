#include"lepton.h"
#include"particle.h"



Lepton::Lepton(const bool& is_anti_input, const float& rest_mass_input, const float& charge_input,
               const double& x_momentum_input, const double& y_momentum_input, const double& z_momentum_input) : 

           Particle{is_anti_input, rest_mass_input, charge_input, 0.5, x_momentum_input, y_momentum_input,
           z_momentum_input}, lepton_number{is_anti_input ? -1 : 1} {}


Lepton::Lepton(const Lepton& lepton_2) : Particle(lepton_2)
{
  cout<<"Calling lepton copy constructor..."<<endl;
  lepton_number = lepton_2.lepton_number;
}

Lepton& Lepton::operator=(const Lepton& lepton_2)
{
  cout<<"Calling lepton copy assignment..."<<endl;
  if(&lepton_2 != this)
  {
  Particle::operator=(lepton_2);
  lepton_number = lepton_2.lepton_number;
  }
  return *this;
}

Lepton::Lepton(Lepton&& lepton_2) : Particle(move(lepton_2))
{
  cout<<"Calling lepton move constructor..."<<endl;
  lepton_number = lepton_2.lepton_number;
  lepton_2.lepton_number = 0;
}

Lepton& Lepton::operator=(Lepton&& lepton_2)
{
  cout<<"Calling lepton move assignment..."<<endl;
  if(&lepton_2 != this)
  {
    Particle::operator=(move(lepton_2));
    lepton_number = 0;
    swap(lepton_number, lepton_2.lepton_number);
  }
  return *this; 
}
