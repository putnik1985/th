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
  Real capacity;
  Real density;
};
