/*
Main script of the particle catalogue project which demonstrates the usage of the key features of 
this framework.
*/

#include"common.h"
#include"quark.h"
#include"muon.h"
#include"electron.h"
#include"neutrino.h"
#include"photon.h"
#include"gluon.h"
#include"tau.h"
#include"zboson.h"
#include"wboson.h"
#include"higgs.h"
#include"catalogue.h"

int main()
{
  Catalogue particle_catalogue;

  // Adding quarks to catalogue
  particle_catalogue.add_particle("up quark", make_shared<Quark>("up", "green", false, 2, 3, 4));
  particle_catalogue.add_particle("antiup quark", make_shared<Quark>("up", "antired", true, 2, 3, 4));
  particle_catalogue.add_particle("down quark", make_shared<Quark>("down", "blue", false, 5, 6, 7));
  particle_catalogue.add_particle("antidown quark", make_shared<Quark>("down", "antired", true, 5, 6, 7));
  particle_catalogue.add_particle("charm quark", make_shared<Quark>("charm", "blue", false, 5, 6, 7));
  particle_catalogue.add_particle("anticharm quark", make_shared<Quark>("charm", "antigreen", true, 5, 6, 7));
  particle_catalogue.add_particle("strange quark", make_shared<Quark>("strange", "blue", false, 5, 6, 7));
  particle_catalogue.add_particle("antistrange quark", make_shared<Quark>("strange", "antired", true, 5, 6, 7));
  particle_catalogue.add_particle("top quark", make_shared<Quark>("top", "blue", false, 5, 6, 7));
  particle_catalogue.add_particle("antitop quark", make_shared<Quark>("top", "antiblue", true, 5, 6, 7));
  particle_catalogue.add_particle("bottom quark", make_shared<Quark>("bottom", "red", false, 5, 6, 7));
  particle_catalogue.add_particle("antibottom quark", make_shared<Quark>("bottom", "antigreen", true, 5, 6, 7));
  // Adding charged leptons to catalogue, electrons have calorimeter energy deposits modified
  particle_catalogue.add_particle("electron", make_shared<Electron>(false, 100, 200, 300, 1, 2, 3, 4));
  particle_catalogue.add_particle("antielectron", make_shared<Electron>(true, 100, 200, 300, 1, 2, 3, 4));
  particle_catalogue.add_particle("muon", make_shared<Muon>(false, true, 0, 0, 0));
  particle_catalogue.add_particle("antimuon", make_shared<Muon>(true, true, 0, 0, 0));
  particle_catalogue.add_particle("tau", make_shared<Tau>(false, 10 , 20 , 30, "anticharm", "strange"));
  particle_catalogue.add_particle("antitau", make_shared<Tau>(true, 10 , 20 , 30, "antimuon", "muon neutrino"));
  // Adding neutrinos to catalogue
  particle_catalogue.add_particle("electron neutrino", make_shared<Neutrino>("electron", false, false, 100, 200, 500));
  particle_catalogue.add_particle("antielectron neutrino", make_shared<Neutrino>("electron", true, false, 100, 200, 500));
  particle_catalogue.add_particle("muon neutrino", make_shared<Neutrino>("muon", false, true, 100, 200, 500));
  particle_catalogue.add_particle("antimuon neutrino", make_shared<Neutrino>("muon", true, true, 100, 200, 500));
  particle_catalogue.add_particle("tau neutrino", make_shared<Neutrino>("tau", false, true, 100, 200, 500));
  particle_catalogue.add_particle("antitau neutrino", make_shared<Neutrino>("tau", true, false, 100, 200, 500));
  // Adding bosons to catalogue
  particle_catalogue.add_particle("photon", make_shared<Photon>(1, 2, 3));
  particle_catalogue.add_particle("gluon", make_shared<Gluon>("green", "antiblue", 10, 20, 30));
  particle_catalogue.add_particle("z boson", make_shared<ZBoson>(100, 200, 300, "antiup", "up"));
  particle_catalogue.add_particle("w- boson", make_shared<WBoson>(0, 100, 200, 300, "antiup", "down"));
  particle_catalogue.add_particle("w+ boson", make_shared<WBoson>(1, 100, 200, 300, "antielectron", "electron neutrino"));
  particle_catalogue.add_particle("higgs boson", make_shared<HBoson>(100, 200, 300, "w bosons"));

  // Example of extracting particles from catalogue by their type
  vector<shared_ptr<Particle>> quarks_in_catalogue{particle_catalogue.get_particles_of_type<Quark>()};

  // Extracting from catalogue by key, then showing set_energy corrects momenta to be on-shell,
  // and then using optional boolean argument into print_particle_data to print full decay product info
  vector<shared_ptr<Particle>> particles_extracted{particle_catalogue.get_particles_with_key("tau")};
  shared_ptr<Particle> extracted_tau{particles_extracted.at(0)};
  extracted_tau->set_energy(2e3);
  extracted_tau->print_particle_data(true); cout<<endl;

  particle_catalogue.print_catalogue();
  cout<<"\nNumber of particles in the catalogue is "<<particle_catalogue.get_particle_count()<<".\n"<<endl;

  // Demonstrating the total catalogue four momentum can be calculated
  FourMomentum total_catalogue_four_momentum{particle_catalogue.get_total_four_momentum()};
  cout<<"\nTotal catalogue four momentum has the components: \n"<<
  "P_0) "<<total_catalogue_four_momentum.get_energy()<<"\n"<<
  "P_1) "<<total_catalogue_four_momentum.get_x_momentum()<<"\n"<<
  "P_2) "<<total_catalogue_four_momentum.get_y_momentum()<<"\n"<<
  "P_3) "<<total_catalogue_four_momentum.get_z_momentum()<<"\n"<<
  "Total catalogue four momentum has a magnitude of "<<
  std::sqrt(dotProduct(total_catalogue_four_momentum, total_catalogue_four_momentum))<<".\n"<<endl;

  return 0;
}