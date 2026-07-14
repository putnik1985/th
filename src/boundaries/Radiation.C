//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "Radiation.h"

registerMooseObject("thApp", Radiation);

InputParameters
Radiation::validParams()
{
  InputParameters params = IntegratedBC::validParams();

  // Specify input parameters that we want users to be able to set:
  params.addRequiredParam<Real>("Q", "Q");
  params.addRequiredParam<Real>("k", "Q");
  params.addRequiredParam<Real>("eps", "Q");
  params.addRequiredParam<Real>("sigma", "Q");
  params.addRequiredParam<Real>("Lf", "Q");
  params.addRequiredParam<Real>("dmCO2_dt", "dmCO2_dt");
  /////////////////params.addRequiredCoupledVar("some_var", "Flux value at the boundary");
  return params;
}

Radiation::Radiation(const InputParameters & parameters)
  : IntegratedBC(parameters),
    // store the user-specified parameters from the input file...
    Q(getParam<Real>("Q")),        
    k(getParam<Real>("k")),        
    eps(getParam<Real>("eps")),        
    sigma(getParam<Real>("sigma")),        
    Lf(getParam<Real>("Lf")),        
    dmCO2_dt(getParam<Real>("dmCO2_dt"))        
    ///////////////////////_some_var_val(coupledValue("some_var")) // for the coupled variable
{
}

Real
Radiation::computeQpResidual()
{
  // For this Neumann BC grad(u)=alpha * v on the boundary.
  return -_test[_i][_qp] * (eps * sigma * pow(_u[_qp], 4.) - Lf * dmCO2_dt - Q) / k;
}
