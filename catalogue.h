/*
Catalogue is a wrapped multimap which stores any objects derived from Particle,
each linked to a user-inputted string key.
*/

#ifndef CATALOGUE_H
#define CATALOGUE_H

#include"common.h"
#include"four_momentum.h"
#include"particle.h"

class Catalogue
{
  private:
    static const string particle_catalogue_title;
    multimap<string, shared_ptr<Particle>> catalogue{};
    size_t particle_count{};

  public:
    Catalogue() {}

    Catalogue(const multimap<string, shared_ptr<Particle>>& catalogue_input);

    Catalogue(const Catalogue& second_catalogue); // copy constructor
    Catalogue(Catalogue&& second_catalogue); // move constructor
    Catalogue& operator=(const Catalogue& second_catalogue); // copy assignment
    Catalogue& operator=(Catalogue&& second_catalogue); // move assignment

    ~Catalogue() {} 

    void add_particle(const string& key_input, const shared_ptr<Particle>& particle_input);

    size_t get_particle_count() const {return particle_count;}
    FourMomentum get_total_four_momentum();
    vector<shared_ptr<Particle>> get_particles_with_key(const string& key_input);
    template<typename type_input> vector<shared_ptr<Particle>> get_particles_of_type();

    void print_particles_with_key(const string& key_input);
    template<typename type_input> void print_particles_of_type();
    void print_catalogue();
};

template<typename type_input> void Catalogue::print_particles_of_type()
{
  for(auto iterator = catalogue.begin(); iterator != catalogue.end(); ++iterator) 
  {
    // Compares type of catalogue particles to the inputted type
    if(typeid(*iterator->second) == typeid(type_input)) {iterator->second->print_particle_data();}
  }
  cout<<endl;
}

template<typename type_input> vector<shared_ptr<Particle>> Catalogue::get_particles_of_type()
{
  vector<shared_ptr<Particle>> vector_of_particles;
  for(auto iterator = catalogue.begin(); iterator != catalogue.end(); ++iterator) 
  {
    // Compares type of catalogue particles to the inputted type
    if(typeid(*iterator->second) == typeid(type_input)) {vector_of_particles.push_back(iterator->second);}
  }
  return vector_of_particles;
}

#endif