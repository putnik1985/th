//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "IntegratedBC.h"
class Radiation : public IntegratedBC
{
public:
  Radiation(const InputParameters & parameters);
  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;

private:
  Real Q;
  Real k;
  Real eps;
  Real sigma;
  Real Lf;
  Real dmCO2_dt;
  ///////////////const VariableValue & _some_var_val;
};
