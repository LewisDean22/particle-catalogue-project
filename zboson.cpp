#include"zboson.h"
#include"quark.h"
#include"electron.h"
#include"muon.h"
#include"tau.h"
#include"neutrino.h"

const unordered_set<string> ZBoson::valid_decay_products[11]{{"up", "antiup"}, {"down", "antidown"},
                                                            {"charm", "anticharm"}, {"strange", "antistrange"},
                                                            {"bottom", "antibottom"}, {"electron", "antielectron"},
                                                            {"muon", "antimuon"}, {"tau, antitau"},
                                                            {"electron neutrino", "antielectron neutrino"},
                                                            {"muon neutrino", "antimuon neutrino"},
                                                            {"tau neutrino", "antitau neutrino"}};

void ZBoson::update_decay_products(const size_t& decay_index)
{
  enum zboson_decay_indices{up = 0,
                            down = 1,
                            charm = 2,
                            strange = 3,
                            bottom = 4,
                            electron = 5,
                            muon = 6,
                            tau = 7,
                            electron_neutrino = 8,
                            muon_neutrino = 9,
                            tau_neutrino = 10};

  switch(decay_index)
  {
    case up:
      decay_products.at(0) = make_shared<Quark>("up", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("up", "red", false, 0, 0, 0);
      break;

    case down:
      decay_products.at(0) = make_shared<Quark>("down", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("down", "red", false, 0, 0, 0);
      break;

    case charm:
      decay_products.at(0)= make_shared<Quark>("charm", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("charm", "red", false, 0, 0, 0);
      break;

    case strange:
      decay_products.at(0) = make_shared<Quark>("strange", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("strange", "red", false, 0, 0, 0);
      break;

    case bottom:
      decay_products.at(0) = make_shared<Quark>("bottom", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("bottom", "red", false, 0, 0, 0);
      break;

    case electron:
      decay_products.at(0) = make_shared<Electron>(true, 0, 0, 0, 0, 0, 0, 0);
      decay_products.at(1) = make_shared<Electron>(false, 0, 0, 0, 0, 0, 0, 0);
      break;

    case muon:
      decay_products.at(0) = make_shared<Muon>(true, false, 0, 0, 0);
      decay_products.at(1) = make_shared<Muon>(false, false, 0, 0, 0);
      break;
    
    // Electronic branching fraction is the largest, hence default
    case tau:
      decay_products.at(0) = make_shared<Tau>(true, 0, 0, 0, "antielectron", "electron neutrino");
      decay_products.at(1) = make_shared<Tau>(false, 0, 0, 0, "electron", "antielectron neutrino");
      break;

    case electron_neutrino:
      decay_products.at(0) = make_shared<Neutrino>("electron", true, false, 0, 0, 0);
      decay_products.at(1) = make_shared<Neutrino>("electron", false, false, 0, 0, 0);
      break;
    
    case muon_neutrino:
      decay_products.at(0) = make_shared<Neutrino>("muon", true, false, 0, 0, 0);
      decay_products.at(1) = make_shared<Neutrino>("muon", false, false, 0, 0, 0);
      break;

    case tau_neutrino:
      decay_products.at(0) = make_shared<Neutrino>("tau", true, false, 0, 0, 0);
      decay_products.at(1) = make_shared<Neutrino>("tau", false, false, 0, 0, 0);
      break;
  }
}

void ZBoson::validate_decay_products(string& decay_product_1_input, string& decay_product_2_input)
{
  std::transform(decay_product_1_input.begin(), decay_product_1_input.end(), decay_product_1_input.begin(),
                [](unsigned char c) {return std::tolower(c);}); // Converts to lowercase
  std::transform(decay_product_2_input.begin(), decay_product_2_input.end(), decay_product_2_input.begin(),
                [](unsigned char c) {return std::tolower(c);}); // Converts to lowercase

  unordered_set<string> decay_product_input{{decay_product_1_input, decay_product_2_input}};
  try
  {
    for(size_t i{}; i<11; i++) 
    {
      if(valid_decay_products[i] == decay_product_input) {update_decay_products(i); return;}
    }
  throw std::invalid_argument("Invalid Z boson decay products inputted. \n"
                              "Please input one of the following pairs: \n"
                              "(lepton/antilepton, quark/antiquark of the same flavour)");
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr<<endl<<"Error: " <<error.what()<<endl;
    exit(EXIT_FAILURE);
  }
}

ZBoson::ZBoson(double x_momentum_input, double y_momentum_input, double z_momentum_input,
               string decay_product_1_input, string decay_product_2_input) :

  Particle{0, 91000, 0, 1, x_momentum_input, y_momentum_input, z_momentum_input},
  decay_product_1{decay_product_1_input}, decay_product_2{decay_product_2_input}
  {validate_decay_products(decay_product_1_input, decay_product_2_input);}

void ZBoson::print_particle_data(bool print_decay_products) 
{
  cout<<endl<<"Z boson properties:" <<endl<<
  "------------------" <<endl;
  Particle::print_particle_data();
  cout<<"Decay products =  "<<decay_product_1<<
  ", "<<decay_product_2<<"\n";

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

ZBoson::ZBoson(const ZBoson& z_boson_2) : Particle(z_boson_2)
{
  cout<<"Calling Z Boson copy constructor..."<<endl;
  decay_product_1 = z_boson_2.decay_product_1;
  decay_product_2 = z_boson_2.decay_product_2;
  decay_products = z_boson_2.decay_products;
}

ZBoson& ZBoson::operator=(const ZBoson& z_boson_2)
{
  cout<<"Calling Z Boson copy assignment..."<<endl;
  if(&z_boson_2 != this)
  {
  Particle::operator=(z_boson_2);
  decay_product_1 = z_boson_2.decay_product_1;
  decay_product_2 = z_boson_2.decay_product_2;
  decay_products = z_boson_2.decay_products;
  }
  return *this;
}

ZBoson::ZBoson(ZBoson&& z_boson_2) : Particle(move(z_boson_2))
{
  cout<<"Calling Z Boson move constructor..."<<endl;
  decay_product_1 = z_boson_2.decay_product_1;
  decay_product_2 = z_boson_2.decay_product_2;
  decay_products = z_boson_2.decay_products;
  z_boson_2.decay_product_1 = "default particle";
  z_boson_2.decay_product_2 = "default particle";
  z_boson_2.decay_products = vector<shared_ptr<Particle>>(2);
}

ZBoson& ZBoson::operator=(ZBoson&& z_boson_2)
{
  cout<<"Calling Z Boson move assignment..."<<endl;
  if(&z_boson_2 != this)
  {
    Particle::operator=(move(z_boson_2));
    decay_product_1 = "default particle";
    decay_product_2 = "default particle";
    decay_products = vector<shared_ptr<Particle>>(2);;
    swap(decay_product_2, z_boson_2.decay_product_2);
    swap(decay_products, z_boson_2.decay_products);
  }
  return *this; 
}