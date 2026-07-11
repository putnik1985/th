//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Diffusion_NP.h"
registerMooseObject("thApp", Diffusion_NP);

InputParameters
Diffusion_NP::validParams()
{
  InputParameters params = Kernel::validParams();
  params.addRequiredParam<Real>("kice", "ice thermal conduction");
  params.addRequiredParam<Real>("thermal_inertia", "thermal inertia");
  params.addRequiredParam<Real>("density", "density");
  params.addRequiredParam<Real>("capacity", "capacity");
  params.addRequiredParam<Real>("porosity", "porosity");
  params.addRequiredParam<Real>("volumetric_filling", "volumetric filling");
  return params;
}

Diffusion_NP::Diffusion_NP(const InputParameters & parameters)
  : // You must call the constructor of the base class first
    Kernel(parameters),
    kice(getParam<Real>("kice")),
    thermal_inertia(getParam<Real>("thermal_inertia")),
    density(getParam<Real>("density")),
    capacity(getParam<Real>("capacity")),
    n(getParam<Real>("porosity")),
    F(getParam<Real>("volumetric_filling"))
{
}

Real
Diffusion_NP::computeQpResidual()
{
  Real T = _u[_qp];
  Real lambda = conductivity(T);
  return _grad_test[_i][_qp] * (lambda * _grad_u[_qp]);
}

Real
Diffusion_NP::computeQpJacobian()
{
  Real T = _u[_qp];
  Real lambda = conductivity(T);
  return _grad_test[_i][_qp] * (lambda * _grad_phi[_j][_qp]);
}

Real
Diffusion_NP::conductivity(Real T){
  return 0.85 * n * kice * F + thermal_inertia * thermal_inertia / (density * capacity);
}
