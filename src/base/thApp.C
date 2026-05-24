#include "thApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
thApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

thApp::thApp(const InputParameters & parameters) : MooseApp(parameters)
{
  thApp::registerAll(_factory, _action_factory, _syntax);
}

thApp::~thApp() {}

void
thApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAllObjects<thApp>(f, af, syntax);
  Registry::registerObjectsTo(f, {"thApp"});
  Registry::registerActionsTo(af, {"thApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
thApp::registerApps()
{
  registerApp(thApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
thApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  thApp::registerAll(f, af, s);
}
extern "C" void
thApp__registerApps()
{
  thApp::registerApps();
}
