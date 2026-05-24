#include "TempDerivative_NP.h"

registerMooseObject("thApp", TempDerivative_NP);

InputParameters
TempDerivative_NP::validParams()
{
  InputParameters params = TimeKernel::validParams();
  params.addRequiredParam<Real>("volume_heat_capacity", "volume heat capacity");
  params.addRequiredParam<Real>("ice_density", "ice density");
  params.addRequiredParam<Real>("water_density", "water density");
  params.addRequiredParam<Real>("porosity", "porosity");
  params.addRequiredParam<Real>("latent_heat_fusion", "latent heat of fusion");
  params.addRequiredParam<Real>("scale", "time scale");
  return params;
}

TempDerivative_NP::TempDerivative_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    TimeKernel(parameters),
    volume_heat_capacity(getParam<Real>("volume_heat_capacity")),
    ice_density(getParam<Real>("ice_density")),
    water_density(getParam<Real>("water_density")),
    porosity(getParam<Real>("porosity")),
    latent_heat_fusion(getParam<Real>("latent_heat_fusion")),
    scale(getParam<Real>("scale"))

{
}

Real
TempDerivative_NP::computeQpResidual()
{
  Real sw;
  Real dsw_dT;

  if (_u[_qp] <= -4.){
       sw = 0.4;
       dsw_dT = 0.;
  } else if (_u[_qp] >-4. && _u[_qp] <= 0.) {
       sw = 0.4 + 0.6/4. * (_u[_qp] + 4.);
       dsw_dT = 0.6/4;
  } else {
       sw = 1.0;
       dsw_dT = 0.;
  } 

  //std::cout << "T " << _u[_qp] << std::endl;
  //std::cout << "sw " << sw << std::endl;
  //std::cout << "dsw " << dsw_dT << std::endl;

  Real si = 1. - sw;

  Real ksi = porosity * ice_density / (sw + ice_density / water_density * si);
  //std::cout << "cef " << (volume_heat_capacity + latent_heat_fusion * ksi * dsw_dT) << std::endl;
  return scale * (volume_heat_capacity + latent_heat_fusion * ksi * dsw_dT) * _u_dot[_qp] * _test[_i][_qp]; 
}

Real
TempDerivative_NP::computeQpJacobian()
{
  Real sw;
  Real dsw_dT;

  if (_u[_qp] <= -4.){
       sw = 0.4;
       dsw_dT = 0.;
  } else if (_u[_qp] >-4. && _u[_qp] <= 0.) {
       sw = 0.4 + 0.6/4. * (_u[_qp] + 4.);
       dsw_dT = 0.6/4;
  } else {
       sw = 1.0;
       dsw_dT = 0.;
  } 


  Real si = 1. - sw;
  Real ksi = porosity * ice_density / (sw + ice_density / water_density * si);
  return scale * (volume_heat_capacity + latent_heat_fusion * ksi * dsw_dT) * _du_dot_du[_qp] * _phi[_j][_qp] * _test[_i][_qp]; 
}
