#include "mymodule.h"

#include <iostream>
#include <qi/log.hpp>


MyModule::MyModule(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name), tts_(getParentBroker())
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
  functionName("raiseEvent", getName(), "Raise event");
  BIND_METHOD(MyModule::raiseEvent);
}

MyModule::~MyModule()
{

}

void MyModule::init()
{
}

void MyModule::generateEvent()
{

}

void MyModule::callback(){
  try
  {
    /** Call the say method. */
    tts_.say("sentence to say");
    /** Note: on the desktop you won't hear anything, but you should see
    * some logs on the naoqi you are connected to. */
  }
  catch(const AL::ALError&)
  {
    qiLogError("module.example") << "Could not get proxy to ALTextToSpeech" << std::endl;
  }
}
