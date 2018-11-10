#include "mymodule.h"

#include <iostream>
#include <qi/log.hpp>


MyModule::MyModule(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name)
{
  // Describe the module here. This will appear on the webpage
  setModuleDescription("My own custom module.");

  /**
   * Define callable methods with their descriptions:
   * This makes the method available to other cpp modules
   * and to python.
   * The name given will be the one visible from outside the module.
   * This method has no parameters or return value to describe
   * functionName(<method_name>, <class_name>, <method_description>);
   * BIND_METHOD(<method_reference>);
   */

  functionName("logAfterDelay", getName(), "Shows log after delay");
  setReturn("boolean", "return true if it's ok");
  BIND_METHOD(MyModule::logAfterDelay);
}

MyModule::~MyModule()
{

}

void MyModule::init()
{
}

bool MyModule::logAfterDelay(){
  /**
   * Show the log when function started
   * and then each billion of iterations of iternal cycle
   */
  qiLogInfo("printAfterDelay") << "start" << std::endl;
  unsigned int i = 0;
  while(true) {
    ++i;
    if(i % 1000000000 == 0) {
      qiLogInfo("printAfterDelay") << "iteration " << i << std::endl;
    }
  }

  //qiLogInfo("printAfterDelay") << "end" << std::endl;

  return true;
}
