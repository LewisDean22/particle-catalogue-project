#include"neutrino.h"
#include"common.h"

const unordered_set<string> Neutrino::valid_flavours{"electron", "muon", "tau"};

string Neutrino::validate_flavour(string& flavour_input)
{
 std::transform(flavour_input.begin(), flavour_input.end(), flavour_input.begin(),
                [](unsigned char c) {return std::tolower(c);}); // Converts to lowercase
  try
  {
    if(valid_flavours.count(flavour_input) != 1) 
    {
    throw std::invalid_argument("Invalid flavour inputted. \n"
                                "Please input one of the following flavours: \n"
                                "(electron/muon/tau)");
    }
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr<<endl<<"Error: " <<error.what()<<endl;
    exit(EXIT_FAILURE);
  }
  return flavour_input;
}

Neutrino::Neutrino(string flavour_input, bool is_anti_input, bool has_interacted_input,
                   double x_momentum_input, double y_momentum_input, double z_momentum_input) :
                   
  Lepton{is_anti_input, 0, 0, x_momentum_input, y_momentum_input, z_momentum_input},
  flavour{validate_flavour(flavour_input)}, has_interacted{has_interacted_input} {}

void Neutrino::print_particle_data(bool print_decay_products)
{
  string flavour_string{flavour};
  if(is_anti) {flavour_string = "anti" + flavour;}

  cout<<endl<<flavour_string<<" neutrino properties:" <<endl<<
  "-----------------------------" <<endl;
  cout<<"Lepton number = "<<lepton_number<<endl;
  Particle::print_particle_data();
  cout<<setprecision(3)<<
  "Interaction status = "<<has_interacted<<endl;
}

Neutrino::Neutrino(const Neutrino& neutrino_2) : Lepton(neutrino_2)
{
  cout<<"Calling neutrino copy constructor..."<<endl;
  flavour = neutrino_2.flavour;
  has_interacted = neutrino_2.has_interacted;
}

Neutrino& Neutrino::operator=(const Neutrino& neutrino_2)
{
  cout<<"Calling neutrino copy assignment..."<<endl;
  if(&neutrino_2 != this)
  {
  Lepton::operator=(neutrino_2);
  flavour = neutrino_2.flavour;
  has_interacted = neutrino_2.has_interacted;
  }
  return *this;
}

Neutrino::Neutrino(Neutrino&& neutrino_2) : Lepton(move(neutrino_2))
{
  cout<<"Calling neutrino move constructor..."<<endl;
  flavour = neutrino_2.flavour;
  has_interacted = neutrino_2.has_interacted;
  neutrino_2.flavour = "electron";
  neutrino_2.has_interacted = 0;
}

Neutrino& Neutrino::operator=(Neutrino&& neutrino_2)
{
  cout<<"Calling neutrino move assignment..."<<endl;
  if(&neutrino_2 != this)
  {
    Lepton::operator=(move(neutrino_2));
    flavour = "electron";
    has_interacted = 0;
    swap(flavour, neutrino_2.flavour);
    swap(has_interacted, neutrino_2.has_interacted);
  }
  return *this; 
}