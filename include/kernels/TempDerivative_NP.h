#pragma once

#include "TimeKernel.h"

class TempDerivative_NP : public TimeKernel
{
public:
  TempDerivative_NP(const InputParameters & parameters);
  static InputParameters validParams();

protected:
  virtual Real computeQpResidual() override;
  virtual Real computeQpJacobian() override;

private:
  Real volume_heat_capacity;
  Real ice_density;
  Real water_density;
  Real porosity;
  Real latent_heat_fusion;
  Real scale;
};

