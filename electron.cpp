#include"electron.h"

vector<double> Electron::validate_calorimeter_deposits(const double& EM_1_input,
                                                       const double& EM_2_input, 
                                                       const double& HAD_1_input,
                                                       const double& HAD_2_input)
{
  double electron_energy{four_momentum->get_energy()};
  vector<double> calorimeter_deposits_input{EM_1_input, EM_2_input, HAD_1_input, HAD_2_input};
  double total_energy_deposited{};
  double tolerance{10e-3};

  for(size_t i{}; i<4; i++) {total_energy_deposited += calorimeter_deposits_input.at(i);}
  if(std::fabs(total_energy_deposited - electron_energy) > tolerance)
  {
    bool EM_1_check{EM_1_input == 0};
    bool EM_2_check{EM_2_input == 0};
    bool HAD_1_check{HAD_1_input == 0};
    bool HAD_2_check{HAD_2_input == 0};
    if(EM_1_check && EM_2_check && HAD_1_check && HAD_2_check)
    {
      double equal_energy_deposit{electron_energy / 4};
      for(size_t i{}; i<4; i++) {calorimeter_deposits_input.at(i) = equal_energy_deposit;}
      cout<<"Electron energy shared equally amongst calorimeter layers..."<<endl;
    }
    else
    {
      for(size_t i{}; i<4; i++) {calorimeter_deposits_input.at(i) *= electron_energy/total_energy_deposited;}
      cout<<"Calorimeter deposits scaled to sum to the electron's energy..."<<endl;
    }
  }
  return calorimeter_deposits_input;
}

Electron::Electron(bool is_anti_input, double x_momentum_input,
                   double y_momentum_input, double z_momentum_input,
                   double EM_1_input, double EM_2_input, double HAD_1_input,
                   double HAD_2_input) :

        Lepton{is_anti_input, 0.51f, (is_anti_input ? 1.0f: -1.0f), x_momentum_input,
        y_momentum_input, z_momentum_input}
        
        {calorimeter_deposits = validate_calorimeter_deposits(EM_1_input, EM_2_input, 
                                                               HAD_1_input, HAD_2_input);}

    void Electron::set_EM_1(const double& EM_1_input) 
    {
      calorimeter_deposits = validate_calorimeter_deposits(EM_1_input, calorimeter_deposits[1], 
                                                           calorimeter_deposits[2],
                                                           calorimeter_deposits[3]);
    }

    void Electron::set_EM_2(const double& EM_2_input) 
    {
      calorimeter_deposits = validate_calorimeter_deposits(calorimeter_deposits[0], EM_2_input, 
                                                           calorimeter_deposits[2],
                                                           calorimeter_deposits[3]);
    }

    void Electron::set_HAD_1(const double& HAD_1_input) 
    {
      calorimeter_deposits = validate_calorimeter_deposits(calorimeter_deposits[0],
                                                           calorimeter_deposits[1], 
                                                           HAD_1_input, 
                                                           calorimeter_deposits[3]);
    }

    void Electron::set_HAD_2(const double& HAD_2_input) 
    {
      calorimeter_deposits = validate_calorimeter_deposits(calorimeter_deposits[0],
                                                           calorimeter_deposits[1], 
                                                           calorimeter_deposits[2], 
                                                           HAD_2_input);
    }

void Electron::print_particle_data(bool print_decay_products)
{
  string flavour_string{"electron"};
  if(is_anti) {flavour_string = "antielectron";}

  cout<<endl<<flavour_string<<" properties:" <<endl<<
  "------------------------" <<endl;
  cout<<"Lepton number = "<<lepton_number<<endl;
  Particle::print_particle_data();
  cout<<setprecision(3)<<
  "Calorimeter energy deposits [EM_1, EM_2, HAD_1, HAD_2] = "<<
  "["<<calorimeter_deposits[0]<<", "<<calorimeter_deposits[1]<<", "<<
  calorimeter_deposits[2]<<", "<<calorimeter_deposits[3]<<"]"<<endl;
}

Electron::Electron(const Electron& electron_2) : Lepton(electron_2)
{
  cout<<"Calling electron copy constructor..."<<endl;
  calorimeter_deposits = electron_2.calorimeter_deposits;
}

Electron& Electron::operator=(const Electron& electron_2)
{
  cout<<"Calling electron copy assignment..."<<endl;
  if(&electron_2 != this)
  {
  Lepton::operator=(electron_2);
  calorimeter_deposits = electron_2.calorimeter_deposits;
  }
  return *this;
}

Electron::Electron(Electron&& electron_2) : Lepton(move(electron_2))
{
  cout<<"Calling electron move constructor..."<<endl;
  calorimeter_deposits = electron_2.calorimeter_deposits;
  electron_2.calorimeter_deposits = vector<double>(4);
}

Electron& Electron::operator=(Electron&& electron_2)
{
  cout<<"Calling electron move assignment..."<<endl;
  if(&electron_2 != this)
  {
    Lepton::operator=(move(electron_2));
    calorimeter_deposits = vector<double>(4);
    swap(calorimeter_deposits, electron_2.calorimeter_deposits);
  }
  return *this; 
}