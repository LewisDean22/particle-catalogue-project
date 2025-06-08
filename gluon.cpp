#include"gluon.h"

const unordered_set<string> Gluon::valid_colours{"red", "blue", "green"};
const unordered_set<string> Gluon::valid_anticolours{"antired", "antiblue", "antigreen"};

string Gluon::validate_colour(string& colour_input, const bool& is_anti_input)
{
  std::transform(colour_input.begin(), colour_input.end(), colour_input.begin(),
                [](unsigned char c) {return std::tolower(c);});
  try
  {
    if(is_anti_input)
    {
      if(valid_anticolours.count(colour_input) != 1) 
      {
        colour_input = "antired"; // Returns something valid but exception still thrown
        throw std::invalid_argument("Invalid anticolour inputted. \n"
                                    "Please input one of the following anticolours: \n"
                                    "(antired/antiblue/antigreen)");
      }
    }
    else
    {
      if(valid_colours.count(colour_input) != 1)
      {
        colour_input = "red";
        throw std::invalid_argument("Invalid colour inputted. \n"
                                    "Please input one of the following colours: \n"
                                    "(red/blue/green)");
      }
    }
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr<<endl<<"Error: " <<error.what()<<endl;
    exit(EXIT_FAILURE);
  }
  return colour_input;
}

Gluon::Gluon(string gluon_colour_input, string gluon_anticolour_input,
             double x_momentum_input, double y_momentum_input, double z_momentum_input) :

  Particle{0, 0, 0, 1, x_momentum_input, y_momentum_input, z_momentum_input},
  gluon_colour{validate_colour(gluon_colour_input, 0)},
  gluon_anticolour{validate_colour(gluon_anticolour_input, 1)} {}

  void Gluon::print_particle_data(bool print_decay_products)
  {
    cout<<endl<<"gluon properties:" <<endl<<
    "-----------------" <<endl;
    Particle::print_particle_data();
    cout<<"Gluon colour = "<<gluon_colour<<endl;
    cout<<"Gluon anticolour = "<<gluon_anticolour<<endl;
  }

Gluon::Gluon(const Gluon& gluon_2) : Particle(gluon_2)
{
  cout<<"Calling gluon copy constructor..."<<endl;
  gluon_colour = gluon_2.gluon_colour;
  gluon_anticolour = gluon_2.gluon_anticolour;
}

Gluon& Gluon::operator=(const Gluon& gluon_2)
{
  cout<<"Calling gluon copy assignment..."<<endl;
  if(&gluon_2 != this)
  {
  Particle::operator=(gluon_2);
  gluon_colour = gluon_2.gluon_colour;
  gluon_anticolour = gluon_2.gluon_anticolour;
  }
  return *this;
}

Gluon::Gluon(Gluon&& gluon_2) : Particle(move(gluon_2))
{
  cout<<"Calling gluon move constructor..."<<endl;
  gluon_colour = gluon_2.gluon_colour;
  gluon_anticolour = gluon_2.gluon_anticolour;
  gluon_2.gluon_colour = "red";
  gluon_2.gluon_anticolour = "antired";
}

Gluon& Gluon::operator=(Gluon&& gluon_2)
{
  cout<<"Calling gluon move assignment..."<<endl;
  if(&gluon_2 != this)
  {
    Particle::operator=(move(gluon_2));
    gluon_colour = "red";
    gluon_anticolour = "antired";
    swap(gluon_colour, gluon_2.gluon_colour);
    swap(gluon_anticolour, gluon_2.gluon_anticolour);
  }
  return *this; 
}