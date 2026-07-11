#include "TempDerivative_NP.h"
#include <utility>

registerMooseObject("thApp", TempDerivative_NP);

InputParameters
TempDerivative_NP::validParams()
{
  InputParameters params = TimeKernel::validParams();
  params.addRequiredParam<Real>("capacity", "volume heat capacity");
  params.addRequiredParam<Real>("density", "density");
  return params;
}

TempDerivative_NP::TempDerivative_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    TimeKernel(parameters),
    capacity(getParam<Real>("capacity")),
    density(getParam<Real>("density"))
{
}

std::pair<Real,Real> fourier(Real x);

Real
TempDerivative_NP::computeQpResidual()
{
  return (capacity * density) * _u_dot[_qp] * _test[_i][_qp]; 
}

Real
TempDerivative_NP::computeQpJacobian()
{
  return (capacity * density) * _du_dot_du[_qp] * _phi[_j][_qp] * _test[_i][_qp]; 
}
