#include"common.h"
#include"catalogue.h"
#include"four_momentum.h"
#include"particle.h"

const string Catalogue::particle_catalogue_title{
 "\n _____           _   _      _         _____      _        _                        \n"
   "|  __ \\         | | (_)    | |       / ____|    | |      | |                       \n"
   "| |__) __ _ _ __| |_ _  ___| | ___  | |     __ _| |_ __ _| | ___   __ _ _   _  ___ \n"
   "|  ___/ _` | '__| __| |/ __| |/ _ \\ | |    / _` | __/ _` | |/ _ \\ / _` | | | |/ _ \\\n"
   "| |  | (_| | |  | |_| | (__| |  __/ | |___| (_| | || (_| | | (_) | (_| | |_| |  __/\n"
   "|_|   \\__,_|_|   \\__|_|\\___|_|\\___|  \\_____\\__,_|\\__\\__,_|_|\\___/ \\__, |\\__,_|\\___|\n"
   "                                                                   __/ |           \n"
   "                                                                  |___/            \n\n"
   "~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~^~~^~^~^~^~^~^~^~^~^~^~^"};

Catalogue::Catalogue(const multimap<string, shared_ptr<Particle>>& catalogue_input) : 

          catalogue{catalogue_input}, particle_count{catalogue_input.size()} {}

void Catalogue::add_particle(const string& key_input, const shared_ptr<Particle>& particle_input)
{
  catalogue.emplace(key_input, particle_input); 
  particle_count++;
}

FourMomentum Catalogue::get_total_four_momentum()
{
  FourMomentum temporary_four_momentum;
  for(const std::pair<string, shared_ptr<Particle>>& pair : catalogue)
  {
    temporary_four_momentum = temporary_four_momentum + *(pair.second->four_momentum);
  }
  return temporary_four_momentum;
}

vector<shared_ptr<Particle>> Catalogue::get_particles_with_key(const string& key_input)
{
  vector<shared_ptr<Particle>> vector_of_particles;
  auto particle_range = catalogue.equal_range(key_input); // iterator over indices with this key
  try
  {
    if(particle_range.first == particle_range.second) // True if iterator has size zero
    {
      throw std::invalid_argument("No particles with the key: " + key_input);
    }
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr<<endl<<"Error: " <<error.what()<<endl;
    exit(EXIT_FAILURE);
  }

  for(auto iterator = particle_range.first; iterator != particle_range.second; ++iterator) 
  {
    vector_of_particles.push_back(iterator->second);
  }
  return vector_of_particles;
}

void Catalogue::print_particles_with_key(const string& key_input)
{
  auto particle_range = catalogue.equal_range(key_input); // iterator over indices with this key
  try
  {
    if(particle_range.first == particle_range.second) // True if iterator has size zero
    {
      throw std::invalid_argument("No particles with the key: " + key_input);
    }
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr<<endl<<"Error: " <<error.what()<<endl;
    exit(EXIT_FAILURE);
  }
  
  for(auto iterator = particle_range.first; iterator != particle_range.second; ++iterator) 
  {
    iterator->second->print_particle_data();
  }
  cout<<endl;
}

void Catalogue::print_catalogue()
{
  cout<<particle_catalogue_title<<"\n\n";
  for(auto iterator = catalogue.begin(); iterator != catalogue.end(); ++iterator) 
  {
    iterator->second->print_particle_data();
  }
  cout<<endl;
}

Catalogue::Catalogue(const Catalogue& second_catalogue)
{
  cout<<"Calling catalogue copy constructor..."<<endl;
  catalogue = second_catalogue.catalogue;
  particle_count = second_catalogue.particle_count;
}

Catalogue& Catalogue::operator=(const Catalogue& second_catalogue)
{
  cout<<"Calling catalogue copy assignment..."<<endl;
  if(&second_catalogue != this) 
  {
    catalogue = second_catalogue.catalogue;
    particle_count = second_catalogue.particle_count;
  }
  return *this;
}

Catalogue::Catalogue(Catalogue&& second_catalogue)
{
  cout<<"Calling catalogue move constructor..."<<endl;
  particle_count = second_catalogue.particle_count;
  second_catalogue.particle_count = 0;
  catalogue = move(second_catalogue.catalogue);
}

Catalogue& Catalogue::operator=(Catalogue&& second_catalogue)
{
  cout<<"Calling catalogue move assignment..."<<endl;
  if(&second_catalogue != this)
  {
    particle_count = 0;
    swap(particle_count, second_catalogue.particle_count);
    catalogue = move(second_catalogue.catalogue);
  }
  return *this; 
}
