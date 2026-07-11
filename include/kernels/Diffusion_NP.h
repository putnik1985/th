//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Kernel.h"

class Diffusion_NP : public Kernel
{
public:
  Diffusion_NP(const InputParameters & parameters);
  Real conductivity(Real);
  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Real kice;
  Real kdry;
  Real thermal_inertia;
  Real density;
  Real capacity;
  Real n;
  Real F;
};
