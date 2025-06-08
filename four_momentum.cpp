#include"common.h"
#include"four_momentum.h"

FourMomentum operator+(const FourMomentum& vector_1, const FourMomentum& vector_2)
{
  double component_0{(vector_1.get_energy() + vector_2.get_energy())};
  double component_1{vector_1.get_x_momentum() + vector_2.get_x_momentum()};
  double component_2{vector_1.get_y_momentum() + vector_2.get_y_momentum()};
  double component_3{vector_1.get_z_momentum() + vector_2.get_z_momentum()};

  return FourMomentum{component_0, component_1, component_2, component_3};
}

FourMomentum operator-(const FourMomentum& vector_1, const FourMomentum& vector_2)
{
  double component_0{(vector_1.get_energy() - vector_2.get_energy())};
  double component_1{vector_1.get_x_momentum() - vector_2.get_x_momentum()};
  double component_2{vector_1.get_y_momentum() - vector_2.get_y_momentum()};
  double component_3{vector_1.get_z_momentum() - vector_2.get_z_momentum()};

  return FourMomentum{component_0, component_1, component_2, component_3};
}

double dotProduct(const FourMomentum& vector_1, const FourMomentum& vector_2)
{
  double product_0{(vector_1.get_energy()*vector_2.get_energy())};
  double product_1{vector_1.get_x_momentum()*vector_2.get_x_momentum()};
  double product_2{vector_1.get_y_momentum()*vector_2.get_y_momentum()};
  double product_3{vector_1.get_z_momentum()*vector_2.get_z_momentum()};

  return product_0 - (product_1 + product_2 + product_3);
}

double FourMomentum::get_3_momentum_magnitude()
{
  return std::sqrt(pow(this->four_momentum[1], 2) + pow(this->four_momentum[2], 2) + 
                   pow(this->four_momentum[3], 2));
}

double FourMomentum::get_invariant_mass()
{
  double squared_invariant_mass = pow(this->four_momentum[0], 2) - (pow(this->four_momentum[1], 2) + 
                                  pow(this->four_momentum[2], 2) + pow(this->four_momentum[3], 2));
  return std::sqrt(squared_invariant_mass);
}
 
double FourMomentum::validate_energy_input(const double& energy_input)
{
  try
  {
    if (energy_input < 0) {throw std::invalid_argument("Inputed energy must be positive.");}
  }
  catch(const std::invalid_argument& error)
  {
    std::cerr<<endl<<"Error: " <<error.what()<<endl;
    exit(EXIT_FAILURE);
  }
  return energy_input;
}

FourMomentum::FourMomentum(double energy_input, double x_momentum_input,
                           double y_momentum_input, double z_momentum_input) 
{
  double energy = validate_energy_input(energy_input);
  four_momentum = vector<double>{energy, x_momentum_input,
                                 y_momentum_input, z_momentum_input};
}

void FourMomentum::set_energy(const double& energy_input)
{
  double energy{validate_energy_input(energy_input)};
  four_momentum[0] = energy;
}

void FourMomentum::print_data()
{
  cout<<setprecision(3)<<"Momentum [P_x, P_y, P_z] (MeV) = ["<<four_momentum[1]<<
  ", "<<four_momentum[2]<<", "<<four_momentum[3]<<"]"<<endl;
}

FourMomentum::FourMomentum(const FourMomentum& second_momentum)
{
  four_momentum = second_momentum.four_momentum;
}

FourMomentum& FourMomentum::operator=(const FourMomentum& second_momentum)
{
  if(&second_momentum != this) {four_momentum =  second_momentum.four_momentum;}
  return *this;
}

FourMomentum::FourMomentum(FourMomentum&& second_momentum)
{
  four_momentum = second_momentum.four_momentum;
  second_momentum.four_momentum = vector<double>(4);
}

FourMomentum& FourMomentum::operator=(FourMomentum&& second_momentum)
{
  if(&second_momentum != this)
  {
    four_momentum = vector<double>(4);
    swap(four_momentum, second_momentum.four_momentum);
  }
  return *this; 
}