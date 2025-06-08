#include"wboson.h"
#include"quark.h"
#include"electron.h"
#include"muon.h"
#include"tau.h"
#include"neutrino.h"

const unordered_set<string> WBoson::valid_w_plus_decays[9]{{"up", "antidown"}, {"up", "antistrange"},
                                                            {"up", "antibottom"}, {"charm", "antidown"},
                                                            {"charm", "antistrange"}, {"charm", "antibottom"},
                                                            {"antielectron", "electron neutrino"},
                                                            {"antimuon", "muon neutrino"},
                                                            {"antitau", "tau neutrino"}};

const unordered_set<string> WBoson::valid_w_minus_decays[9]{{"antiup", "down"}, {"antiup", "strange"},
                                                            {"antiup", "bottom"}, {"anticharm", "down"},
                                                            {"anticharm", "strange"}, {"anticharm", "bottom"},
                                                            {"electron", "antielectron neutrino"},
                                                            {"muon", "antimuon neutrino"},
                                                            {"tau", "antitau neutrino"}};

void WBoson::update_w_plus_decay_products(const size_t& decay_index)
{
  enum wboson_decay_indices{up_antidown = 0,
                            up_antistrange = 1,
                            up_antibottom = 2,
                            charm_antidown = 3,
                            charm_antistrange = 4,
                            charm_antibottom = 5,
                            antielectron = 6,
                            antimuon = 7,
                            antitau = 8};

  switch(decay_index)
  {
    case up_antidown:
      decay_products.at(0) = make_shared<Quark>("down", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("up", "red", false, 0, 0, 0);
      break;

    case up_antistrange:
      decay_products.at(0) = make_shared<Quark>("strange", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("up", "red", false, 0, 0, 0);
      break;

    case up_antibottom:
      decay_products.at(0)= make_shared<Quark>("bottom", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("up", "red", false, 0, 0, 0);
      break;

    case charm_antidown:
      decay_products.at(0) = make_shared<Quark>("down", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("charm", "red", false, 0, 0, 0);
      break;

    case charm_antistrange:
      decay_products.at(0) = make_shared<Quark>("strange", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("charm", "red", false, 0, 0, 0);
      break;

    case charm_antibottom:
      decay_products.at(0) = make_shared<Quark>("bottom", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("charm", "red", false, 0, 0, 0);
      break;

    case antielectron:
      decay_products.at(0) = make_shared<Electron>(true, 0, 0, 0, 0, 0, 0, 0);
      decay_products.at(1) = make_shared<Neutrino>("electron", false, false, 0, 0, 0);
      break;
    
    case antimuon:
      decay_products.at(0) = make_shared<Muon>(true, false, 0, 0, 0);
      decay_products.at(1) = make_shared<Neutrino>("muon", false, false, 0, 0, 0);
      break;

    // Electronic branching fraction is the largest, hence default
    case antitau:
      decay_products.at(0) = make_shared<Tau>(true, 0, 0, 0, "antielectron", "electron neutrino");
      decay_products.at(1) = make_shared<Neutrino>("tau", false, false, 0, 0, 0);
      break;
  }
}

void WBoson::update_w_minus_decay_products(const size_t& decay_index)
{
  enum wboson_decay_indices{antiup_down = 0,
                            antiup_strange = 1,
                            antiup_bottom = 2,
                            anticharm_down = 3,
                            anticharm_strange = 4,
                            anticharm_bottom = 5,
                            electron = 6,
                            muon = 7,
                            tau = 8};

  switch(decay_index)
  {
    case antiup_down:
      decay_products.at(0) = make_shared<Quark>("up", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("down", "red", false, 0, 0, 0);
      break;

    case antiup_strange:
      decay_products.at(0) = make_shared<Quark>("up", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("strange", "red", false, 0, 0, 0);
      break;

    case antiup_bottom:
      decay_products.at(0)= make_shared<Quark>("up", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("bottom", "red", false, 0, 0, 0);
      break;

    case anticharm_down:
      decay_products.at(0) = make_shared<Quark>("charm", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("down", "red", false, 0, 0, 0);
      break;

    case anticharm_strange:
      decay_products.at(0) = make_shared<Quark>("charm", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("strange", "red", false, 0, 0, 0);
      break;

    case anticharm_bottom:
      decay_products.at(0) = make_shared<Quark>("charm", "antired", true, 0, 0, 0);
      decay_products.at(1) = make_shared<Quark>("bottom", "red", false, 0, 0, 0);
      break;

    case electron:
      decay_products.at(0) = make_shared<Electron>();
      decay_products.at(1) = make_shared<Neutrino>("electron", true, false, 0, 0, 0);
      break;
    
    case muon:
      decay_products.at(0) = make_shared<Muon>();
      decay_products.at(1) = make_shared<Neutrino>("muon", true, false, 0, 0, 0);
      break;

    // Electronic branching fraction is the largest, hence default
    case tau:
      decay_products.at(0) = make_shared<Tau>(false, 0, 0, 0, "electron", "antielectron neutrino");
      decay_products.at(1) = make_shared<Neutrino>("tau", true, false, 0, 0, 0);
      break;
  }
}

void WBoson::validate_decay_products(string& decay_product_1_input, string& decay_product_2_input,
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
      for(size_t i{}; i<9; i++) 
      {
        if(valid_w_plus_decays[i] == decay_product_input) {update_w_plus_decay_products(i); return;}
      }
    throw std::invalid_argument("Invalid W+ decay products inputted. \n"
                                "Please check conservation laws are respected!");
    }
    else
    {
      for(size_t i{}; i<9; i++) 
      {
        if(valid_w_minus_decays[i] == decay_product_input) {update_w_minus_decay_products(i); return;}
      }
    throw std::invalid_argument("Invalid W- decay products inputted. \n"
                                "Please check conservation laws are respected!");
    }
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr<<endl<<"Error: " <<error.what()<<endl;
    exit(EXIT_FAILURE);
  }
}

WBoson::WBoson(bool is_anti_input, double x_momentum_input, double y_momentum_input,
               double z_momentum_input, string decay_product_1_input, string decay_product_2_input) :

  Particle{is_anti_input, 80000, (is_anti_input ? 1.0f : -1.0f), 1,
           x_momentum_input, y_momentum_input, z_momentum_input},
           decay_product_1{decay_product_1_input}, decay_product_2{decay_product_2_input}
           
          {validate_decay_products(decay_product_1_input, decay_product_2_input, is_anti_input);}

void WBoson::print_particle_data(bool print_decay_products) 
{
  string charge_sign{"-"};
  if(is_anti) {charge_sign = "+";}

  cout<<endl<<"W"<<charge_sign<<" boson properties:" <<endl<<
  "--------------------" <<endl;
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

WBoson::WBoson(const WBoson& w_boson_2) : Particle(w_boson_2)
{
  cout<<"Calling W Boson copy constructor..."<<endl;
  decay_product_1 = w_boson_2.decay_product_1;
  decay_product_2 = w_boson_2.decay_product_2;
  decay_products = w_boson_2.decay_products;
}

WBoson& WBoson::operator=(const WBoson& w_boson_2)
{
  cout<<"Calling W Boson copy assignment..."<<endl;
  if(&w_boson_2 != this)
  {
  Particle::operator=(w_boson_2);
  decay_product_1 = w_boson_2.decay_product_1;
  decay_product_2 = w_boson_2.decay_product_2;
  decay_products = w_boson_2.decay_products;
  }
  return *this;
}

WBoson::WBoson(WBoson&& w_boson_2) : Particle(move(w_boson_2))
{
  cout<<"Calling W Boson move constructor..."<<endl;
  decay_product_1 = w_boson_2.decay_product_1;
  decay_product_2 = w_boson_2.decay_product_2;
  decay_products = w_boson_2.decay_products;
  w_boson_2.decay_product_1 = "default particle";
  w_boson_2.decay_product_2 = "default particle";
  w_boson_2.decay_products = vector<shared_ptr<Particle>>(2);
}

WBoson& WBoson::operator=(WBoson&& w_boson_2)
{
  cout<<"Calling W Boson move assignment..."<<endl;
  if(&w_boson_2 != this)
  {
    Particle::operator=(move(w_boson_2));
    decay_product_1 = "default particle";
    decay_product_2 = "default particle";
    decay_products = vector<shared_ptr<Particle>>(2);;
    swap(decay_product_2, w_boson_2.decay_product_2);
    swap(decay_products, w_boson_2.decay_products);
  }
  return *this; 
}