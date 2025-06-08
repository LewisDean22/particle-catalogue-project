#include"tau.h"
#include"quark.h"
#include"neutrino.h"
#include"muon.h"
#include"electron.h"

const unordered_set<string> Tau::valid_tau_decays[6]{{"antiup", "down"}, {"anticharm", "down"},
                                                     {"antiup", "strange"}, {"anticharm", "strange"},
                                                     {"muon", "antimuon neutrino"},
                                                     {"electron", "antielectron neutrino"}};

const unordered_set<string> Tau::valid_antitau_decays[6]{{"up", "antidown"}, {"charm", "antidown"},
                                                         {"up", "antistrange"}, {"charm", "antistrange"},
                                                         {"antimuon", "muon neutrino"},
                                                         {"antielectron", "electron neutrino"}};

void Tau::update_tau_decay_products(const size_t& decay_index)
{
  decay_products.at(0) = make_shared<Neutrino>("tau", false, false, 0, 0, 0);
  enum tau_decay_indices{antiup_down = 0,
                         anticharm_down = 1,
                         antiup_strange = 2,
                         anticharm_strange = 3,
                         muon = 4,
                         electron = 5};

  switch(decay_index)
  {
    case antiup_down:
      decay_products.at(1) = make_shared<Quark>("up", "antired", true, 0, 0, 0);
      decay_products.at(2) = make_shared<Quark>("down", "red", false, 0, 0, 0);
      break;

    case anticharm_down:
      decay_products.at(1) = make_shared<Quark>("charm", "antired", true, 0, 0, 0);
      decay_products.at(2) = make_shared<Quark>("down", "red", false, 0, 0, 0);
      break;

    case antiup_strange:
      decay_products.at(1) = make_shared<Quark>("up", "antired", true, 0, 0, 0);
      decay_products.at(2) = make_shared<Quark>("strange", "red", false, 0, 0, 0);
      break;

    case anticharm_strange:
      decay_products.at(1) = make_shared<Quark>("charm", "antired", true, 0, 0, 0);
      decay_products.at(2) = make_shared<Quark>("strange", "red", false, 0, 0, 0);
      break;

    case muon:
      decay_products.at(1) = make_shared<Muon>();
      decay_products.at(2) = make_shared<Neutrino>("muon", true, false, 0, 0, 0);
      break;

    case electron:
      decay_products.at(1) = make_shared<Electron>();
      decay_products.at(2) = make_shared<Neutrino>("electron", true, false, 0, 0, 0);
      break;
  }
}

void Tau::update_antitau_decay_products(const size_t& decay_index)
{
  decay_products.at(0) = make_shared<Neutrino>("tau", true, false, 0, 0, 0);
  enum antitau_decay_indices{up_antidown = 0,
                             charm_antidown = 1,
                             up_antistrange = 2,
                             charm_antistrange = 3,
                             antimuon = 4,
                             antielectron = 5};

  switch(decay_index)
{
  case up_antidown:
    decay_products.at(1) = make_shared<Quark>("up", "red", false, 0, 0, 0);
    decay_products.at(2) = make_shared<Quark>("down", "antired", true, 0, 0, 0);
    break;

  case charm_antidown:
    decay_products.at(1) = make_shared<Quark>("charm", "red", false, 0, 0, 0);
    decay_products.at(2) = make_shared<Quark>("down", "antired", true, 0, 0, 0);
    break;

  case up_antistrange:
    decay_products.at(1) = make_shared<Quark>("up", "red", false, 0, 0, 0);
    decay_products.at(2) = make_shared<Quark>("strange", "antired", true, 0, 0, 0);
    break;

  case charm_antistrange:
    decay_products.at(1) = make_shared<Quark>("charm", "red", false, 0, 0, 0);
    decay_products.at(2) = make_shared<Quark>("strange", "antired", true, 0, 0, 0);
    break;

  case antimuon:
    decay_products.at(1) = make_shared<Muon>(true, false, 0, 0, 0);
    decay_products.at(2) = make_shared<Neutrino>("muon", false, false, 0, 0, 0);
    break;

  case antielectron:
    decay_products.at(1) = make_shared<Electron>(true, 0, 0, 0, 0, 0, 0, 0);
    decay_products.at(2) = make_shared<Neutrino>("electron", false, false, 0, 0, 0);
    break;
}
}

void Tau::validate_decay_products(string& decay_product_1_input, string& decay_product_2_input,
                                  const bool& is_anti_input)
{
  std::transform(decay_product_1_input.begin(), decay_product_1_input.end(), decay_product_1_input.begin(),
                [](unsigned char c) {return std::tolower(c);}); // Converts to lowercase
  std::transform(decay_product_2_input.begin(), decay_product_2_input.end(), decay_product_2_input.begin(),
                [](unsigned char c) {return std::tolower(c);}); // Converts to lowercase

  unordered_set<string> decay_product_input{{decay_product_1_input, decay_product_2_input}};
  try
  {
    if(is_anti_input)
    {
      for(size_t i{}; i<6; i++) 
      {
        if(valid_antitau_decays[i] == decay_product_input) {update_antitau_decay_products(i); return;}
      }
    throw std::invalid_argument("Invalid antitau decay products inputted. \n"
                                "Please input one of the following pairs: \n"
                                "(antiup-down/charm-antidown/up-antistrange/charm-antistrange/"
                                "antimuon-muon neutrino/antielectron-electron neutrino)");
    }
    else
    {
      for(size_t i{}; i<6; i++) 
      {
        if(valid_tau_decays[i] == decay_product_input) {update_tau_decay_products(i); return;}
      }
    throw std::invalid_argument("Invalid tau decay products inputted. \n"
                                "Please input one of the following pairs: \n"
                                "(up-antidown/anticharm-down/antiup-strange/anticharm-strange/"
                                "muon-antimuon neutrino/electron-antielectron neutrino)");
    }
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr<<endl<<"Error: " <<error.what()<<endl;
    exit(EXIT_FAILURE);
  }
}

Tau::Tau(bool is_anti_input, double x_momentum_input, double y_momentum_input,
         double z_momentum_input, string decay_product_1_input, string decay_product_2_input) :
         
  Lepton{is_anti_input, 1800, (is_anti_input ? 1.0f : -1.0f), x_momentum_input,
         y_momentum_input, z_momentum_input}, decay_product_1{decay_product_1_input},
         decay_product_2{decay_product_2_input}
  {validate_decay_products(decay_product_1_input, decay_product_2_input, is_anti_input);}

void Tau::print_particle_data(bool print_decay_products)
{
  string flavour_string{"tau"};
  if(is_anti) {flavour_string = "antitau";}

  cout<<endl<<flavour_string<<" properties: \n"<<
  "------------------------"<<endl;
  cout<<"Lepton number = "<<lepton_number<<endl;
  Particle::print_particle_data();
  cout<<"Decay products =  "<<flavour_string<<" neutrino, "<<
  decay_product_1<<", "<<decay_product_2<<"\n";

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

Tau::Tau(const Tau& tau_2) : Lepton(tau_2)
{
  cout<<"Calling tau copy constructor..."<<endl;
  decay_product_1 = tau_2.decay_product_1;
  decay_product_2 = tau_2.decay_product_2;
  decay_products = tau_2.decay_products;
}

Tau& Tau::operator=(const Tau& tau_2)
{
  cout<<"Calling tau copy assignment..."<<endl;
  if(&tau_2 != this)
  {
  Lepton::operator=(tau_2);
  decay_product_1 = tau_2.decay_product_1;
  decay_product_2 = tau_2.decay_product_2;
  decay_products = tau_2.decay_products;
  }
  return *this;
}

Tau::Tau(Tau&& tau_2) : Lepton(move(tau_2))
{
  cout<<"Calling tau move constructor..."<<endl;
  decay_product_1 = tau_2.decay_product_1;
  decay_product_2 = tau_2.decay_product_2;
  decay_products = tau_2.decay_products;
  tau_2.decay_product_1 = "default particle";
  tau_2.decay_product_2 = "default particle";
  tau_2.decay_products = vector<shared_ptr<Particle>>(3);
}

Tau& Tau::operator=(Tau&& tau_2)
{
  cout<<"Calling tau move assignment..."<<endl;
  if(&tau_2 != this)
  {
    Lepton::operator=(move(tau_2));
    decay_product_1 = "default particle";
    decay_product_2 = "default particle";
    decay_products = vector<shared_ptr<Particle>>(3);
    swap(decay_product_1, tau_2.decay_product_1);
    swap(decay_product_2, tau_2.decay_product_2);
    swap(decay_products, tau_2.decay_products);
  }
  return *this; 
}