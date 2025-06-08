#include"higgs.h"
#include"quark.h"
#include"zboson.h"
#include"wboson.h"
#include"photon.h"

const string HBoson::valid_decay_types[4]{"w bosons", "z bosons", "photons",
                                          "bottoms"};

void HBoson::update_decay_products(const size_t& decay_index)
{
  enum hboson_decay_indices{w_bosons = 0,
                            z_bosons = 1,
                            photons = 2,
                            bottoms = 3};

  switch(decay_index)
  {
    // Default tau decay because dominant branching fraction
    case w_bosons:
      decay_products.at(0) = make_shared<WBoson>(0, 0, 0, 0, "tau", "antitau neutrino");
      decay_products.at(1) = make_shared<WBoson>(1, 0, 0, 0, "antitau", "tau neutrino");
      break;

    // Default bottom decay because dominant branching fraction
    case z_bosons:
      decay_products.at(0) = make_shared<ZBoson>(0, 0, 0, "bottom", "antibottom");
      decay_products.at(1) = make_shared<ZBoson>(0, 0, 0, "bottom", "antibottom");
      break;

    case photons:
      decay_products.at(0)= make_shared<Photon>();
      decay_products.at(1) = make_shared<Photon>();
      break;

    case bottoms:
      decay_products.at(0)= make_shared<Quark>("bottom", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("bottom", "red", false, 0, 0, 0);
      break;
  }
}

void HBoson::validate_decay_products(string& decay_type_input)
{
  std::transform(decay_type_input.begin(), decay_type_input.end(), decay_type_input.begin(),
                [](unsigned char c) {return std::tolower(c);}); // Converts to lowercase
  try
  {
    for(size_t i{}; i<4; i++) 
    {
      if(valid_decay_types[i] == decay_type_input) {update_decay_products(i); return;}
    }
  throw std::invalid_argument("Invalid H boson decay products inputted. \n"
                              "Please input one of the following: \n"
                              "(w bosons, z bosons, photons, bottoms)");
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr<<endl<<"Error: " <<error.what()<<endl;
    exit(EXIT_FAILURE);
  }
}

HBoson::HBoson(double x_momentum_input, double y_momentum_input, double z_momentum_input,
               string decay_type_input) :

  Particle{0, 126000, 0, 0, x_momentum_input, y_momentum_input, z_momentum_input},
  decay_type{decay_type_input} {validate_decay_products(decay_type_input);}

void HBoson::print_particle_data(bool print_decay_products) 
{
  cout<<endl<<"H boson properties:\n" <<
  "------------------\n";
  Particle::print_particle_data();
  cout<<"Decay products = 2 "<<decay_type<<"\n";

  if(print_decay_products)
  {
    cout<<"\n---------------\n"
    "DECAY PRODUCTS: \n"<<
    "---------------\n"<<endl;
    for(shared_ptr<Particle> particle : decay_products)
    {
      particle->print_particle_data(print_decay_products); cout<<endl;
    }
  }
}

HBoson::HBoson(const HBoson& higgs_2) : Particle(higgs_2)
{
  cout<<"Calling Higgs boson copy constructor..."<<endl;
  decay_type = higgs_2.decay_type;
  decay_products = higgs_2.decay_products;
}

HBoson& HBoson::operator=(const HBoson& higgs_2)
{
  cout<<"Calling Higgs boson copy assignment..."<<endl;
  if(&higgs_2 != this)
  {
  Particle::operator=(higgs_2);
  decay_type = higgs_2.decay_type;
  decay_products = higgs_2.decay_products;
  }
  return *this;
}

HBoson::HBoson(HBoson&& higgs_2) : Particle(move(higgs_2))
{
  cout<<"Calling Higgs boson move constructor..."<<endl;
  decay_type = higgs_2.decay_type;
  decay_products = higgs_2.decay_products;
  higgs_2.decay_type = "default decay";
  higgs_2.decay_products = vector<shared_ptr<Particle>>(2);
}

HBoson& HBoson::operator=(HBoson&& higgs_2)
{
  cout<<"Calling Higgs boson move assignment..."<<endl;
  if(&higgs_2 != this)
  {
    Particle::operator=(move(higgs_2));
    decay_type = "default decay";
    decay_products = vector<shared_ptr<Particle>>(2);
    swap(decay_type, higgs_2.decay_type);
    swap(decay_products, higgs_2.decay_products);
  }
  return *this; 
}