#include "mymodule.h"
#include <iostream>
#include <qi/log.hpp>
#include <alvalue/alvalue.h>

MyModule::MyModule(boost::shared_ptr<AL::ALBroker> broker,
                   const std::string& name)
  : AL::ALModule(broker, name), tts_(getParentBroker()), memoryProxy(getParentBroker())
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
  functionName("generateEvent", getName(), "Generate event");
  addParam("value", "The data associated with the event");
  BIND_METHOD(MyModule::generateEvent);

  functionName("callbackOverCycle", getName(), "Must interrupt cycle");
  BIND_METHOD(MyModule::callbackOverCycle);


  functionName("callback", getName(), "");
  BIND_METHOD(MyModule::callback);
}

MyModule::~MyModule()
{
  memoryProxy.unsubscribeToEvent("ExampleEvent", "MyModule");
  memoryProxy.unsubscribeToEvent("RightBumperPressed", "MyModule");
}

void MyModule::init()
{
  memoryProxy.subscribeToEvent("ExampleEvent", "MyModule", "callback");
  memoryProxy.subscribeToEvent("RightBumperPressed", "MyModule", "callbackOverCycle");
}

void MyModule::generateEvent(const float& value)
{
  memoryProxy.raiseEvent("ExampleEvent", value);
}

void MyModule::callbackOverCycle() {
  qiLogInfo("Event") << "Callback can interrupt internal cycle!!!" << std::endl;

  double ptr = memoryProxy.getData("RightBumperPressed");
  if(ptr > 0.5f) {
    return;
  }
  tts_.say("Interrupted!");

  // cycle in callback
  while(true) {
    qi::os::sleep(1);
  }
}

void MyModule::callback(){
  qiLogInfo("Event") << "raise event!" << std::endl;
  try
  {
    tts_.say("sentence to say");
    qiLogInfo("Event") << "raise event!" << std::endl;
  }
  catch(const AL::ALError&)
  {
    qiLogError("module.example") << "Could not get proxy to ALTextToSpeech" << std::endl;
  }

  // we go into internal cycle
  while(true) {
    qi::os::sleep(1);
  }
}
