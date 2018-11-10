#include "mymodule.h"
#include <boost/shared_ptr.hpp>
#include <alcommon/albroker.h>
#include <alcommon/albrokermanager.h>
#include <alcommon/altoolsmain.h>

extern "C"
{
  int _createModule(boost::shared_ptr<AL::ALBroker> broker)
  {
    // init broker with the main broker instance
    // from the parent executable
    AL::ALBrokerManager::setInstance(broker->fBrokerManager.lock());
    AL::ALBrokerManager::getInstance()->addBroker(broker);
    // create module instances
    AL::ALModule::createModule<MyModule>(broker, "MyModule");
    return 0;
  }

  int _closeModule(  )
  {
    return 0;
  }
} // extern "C"

#ifdef MYMODULE_IS_REMOTE
int main(int argc, char* argv[])
{
  // pointer to createModule
  TMainType sig = &_createModule;

  // call main
  return ALTools::mainFunction("MyModule", argc, argv, sig);
}
#endif
