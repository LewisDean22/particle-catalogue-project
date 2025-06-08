#include"particle.h"
#include"quark.h"
#include"gluon.h"

const unordered_set<string> Quark::valid_flavours{"up", "down", "charm", "strange",
                                                  "top", "bottom"};

const map<string, const float> Quark::quark_rest_masses{{{"up", 2.3}, {"down", 4.8},
                                                       {"charm", 1300}, {"strange", 95},
                                                       {"top", 170000}, {"bottom", 4200}}};

const map<string, const float> Quark::quark_charges{{{"up", 2.0/3}, {"down", -1.0/3},
                                                  {"charm", 2.0/3}, {"strange", -1.0/3},
                                                  {"top", 2.0/3}, {"bottom", -1.0/3}}};

string Quark::validate_flavour(string& flavour_input)
{
 std::transform(flavour_input.begin(), flavour_input.end(), flavour_input.begin(),
                [](unsigned char c) {return std::tolower(c);}); // Converts to lowercase
  try
  {
    if(valid_flavours.count(flavour_input) != 1) 
    {
    flavour_input = "up"; // Returns something valid but exception still thrown
    throw std::invalid_argument("Invalid flavour inputted. \n"
                                "Please input one of the following flavours: \n"
                                "(up/down/charm/strange/top/bottom)");
    }
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr<<endl<<"Error: " <<error.what()<<endl;
    exit(EXIT_FAILURE);
  }
  return flavour_input;
}

float Quark::get_valid_quark_mass(string& flavour_input)
{
  string valid_flavour{validate_flavour(flavour_input)};
  return quark_rest_masses.at(valid_flavour);
}

float Quark::get_valid_quark_charge(string& flavour_input)
{
  string valid_flavour{validate_flavour(flavour_input)};
  return quark_charges.at(valid_flavour);
}

Quark::Quark(string flavour_input, string colour_charge_input, bool is_anti_input,
             double x_momentum_input, double y_momentum_input, double z_momentum_input) : 
             
    Particle{is_anti_input, get_valid_quark_mass(flavour_input),
    (is_anti_input ? -1 : 1) * get_valid_quark_charge(flavour_input), 0.5f,
    x_momentum_input, y_momentum_input, z_momentum_input},
    flavour{validate_flavour(flavour_input)},
    quark_colour{Gluon::validate_colour(colour_charge_input, is_anti_input)},
    quark_number{(is_anti_input ? -1/3.0f : 1/3.0f)} {}
    
void Quark::print_particle_data(bool print_decay_products)
{
  string flavour_string{flavour};
  if(is_anti) {flavour_string = "anti"+ flavour;}

  cout<<endl<<flavour_string<<" quark properties:" <<endl<<
  "------------------------" <<endl;
  cout<<"Quark number = "<<quark_number<<endl;
  cout<<"Colour charge = "<<quark_colour<<endl;
  Particle::print_particle_data();
}

Quark::Quark(const Quark& quark_2) : Particle(quark_2)
{
  cout<<"Calling quark copy constructor..."<<endl;
  flavour = quark_2.flavour;
  quark_colour = quark_2.quark_colour;
  quark_number = quark_2.quark_number;
}

Quark& Quark::operator=(const Quark& quark_2)
{
  cout<<"Calling quark copy assignment..."<<endl;
  if(&quark_2 != this)
  {
  Particle::operator=(quark_2);
  flavour = quark_2.flavour;
  quark_colour = quark_2.quark_colour;
  quark_number = quark_2.quark_number;
  }
  return *this;
}

Quark::Quark(Quark&& quark_2) : Particle(move(quark_2))
{
  cout<<"Calling quark move constructor..."<<endl;
  flavour = quark_2.flavour;
  quark_colour = quark_2.quark_colour;
  quark_number = quark_2.quark_number;

  // These are the default initialised values (red up quark)
  quark_2.flavour = "up";
  quark_2.quark_colour = "red";
  quark_2.quark_number = 1/3.0f;
}

Quark& Quark::operator=(Quark&& quark_2)
{
  cout<<"Calling quark move assignment..."<<endl;
  if(&quark_2 != this)
  {
    Particle::operator=(move(quark_2));
    // These are the default initialised values (red up quark)
    flavour = "up";
    quark_colour = "red";
    quark_number = 1/3.0f;

    swap(flavour, quark_2.flavour);
    swap(quark_colour, quark_2.quark_colour);
    swap(quark_number, quark_2.quark_number);
  }
  return *this; 
}