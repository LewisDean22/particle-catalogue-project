#include"muon.h"

Muon::Muon(bool is_anti_input, bool is_isolated_input, double x_momentum_input,
           double y_momentum_input, double z_momentum_input) :

         Lepton{is_anti_input, 106, (is_anti_input ? 1.0f: -1.0f), x_momentum_input,
         y_momentum_input, z_momentum_input},
         is_isolated{is_isolated_input} {}

void Muon::print_particle_data(bool print_decay_products)
{
  string flavour_string{"muon"};
  if(is_anti) {flavour_string = "antimuon";}

  cout<<endl<<flavour_string<<" properties:\n"<<
  "------------------------"<<endl;
  cout<<"Lepton number = "<<lepton_number<<endl;
  Particle::print_particle_data();
  cout<<setprecision(3)<<
  "Isolation status = "<<is_isolated<<endl;
}

Muon::Muon(const Muon& muon_2) : Lepton(muon_2)
{
  cout<<"Calling muon copy constructor..."<<endl;
  is_isolated = muon_2.is_isolated;
}

Muon& Muon::operator=(const Muon& muon_2)
{
  cout<<"Calling muon copy assignment..."<<endl;
  if(&muon_2 != this)
  {
  Lepton::operator=(muon_2);
  is_isolated = muon_2.is_isolated;
  }
  return *this;
}

Muon::Muon(Muon&& muon_2) : Lepton(move(muon_2))
{
  cout<<"Calling muon move constructor..."<<endl;
  is_isolated = muon_2.is_isolated;
  muon_2.is_isolated = 0;
}

Muon& Muon::operator=(Muon&& muon_2)
{
  cout<<"Calling muon move assignment..."<<endl;
  if(&muon_2 != this)
  {
    Lepton::operator=(move(muon_2));
    is_isolated = 0;
    swap(is_isolated, muon_2.is_isolated);
  }
  return *this; 
}