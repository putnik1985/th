//* This file is part of the MOOSE framework
//* https://mooseframework.inl.gov
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "thTestApp.h"
#include "thApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

InputParameters
thTestApp::validParams()
{
  InputParameters params = thApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

thTestApp::thTestApp(const InputParameters & parameters) : MooseApp(parameters)
{
  thTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

thTestApp::~thTestApp() {}

void
thTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  thApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"thTestApp"});
    Registry::registerActionsTo(af, {"thTestApp"});
  }
}

void
thTestApp::registerApps()
{
  registerApp(thApp);
  registerApp(thTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
thTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  thTestApp::registerAll(f, af, s);
}
extern "C" void
thTestApp__registerApps()
{
  thTestApp::registerApps();
}
