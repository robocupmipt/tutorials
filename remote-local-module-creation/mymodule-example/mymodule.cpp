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
  functionName("printHello", getName(), "Print hello to the world");
  BIND_METHOD(MyModule::printHello);

  /**
   * addParam(<attribut_name>, <attribut_descrption>);
   * This enables to document the parameters of the method.
   * It is not compulsory to write this line.
   */
  functionName("printWord", getName(), "Print a given word.");
  addParam("word", "The word to be print.");
  BIND_METHOD(MyModule::printWord);

  /**
   * setReturn(<return_name>, <return_description>);
   * This enables to document the return of the method.
   * It is not compulsory to write this line.
   */
  functionName("returnTrue", getName(), "Just return true");
  setReturn("boolean", "return true");
  BIND_METHOD(MyModule::returnTrue);

  functionName("sayWord", getName(), "Says the word");
  setReturn("boolean", "return true if robot says the word");
  BIND_METHOD(MyModule::sayWord);

  // If you had other methods, you could bind them here...
  /**
   * Bound methods can only take const ref arguments of basic types,
   * or AL::ALValue or return basic types or an AL::ALValue.
   */
}

MyModule::~MyModule()
{
  
}

void MyModule::init()
{
  /**
   * Init is called just after construction.
   * Do something or not
   */
  std::cout << returnTrue() << std::endl;
}


void MyModule::printHello()
{
  std::cout << "Hello!" << std::endl;
}

void MyModule::printWord(const std::string &word)
{
  std::cout << word << std::endl;
}

bool MyModule::returnTrue()
{
  return true;
}

bool MyModule::sayWord(const std::string& word){
  std::cout << "Saying the phrase in the console..." << std::endl;
  std::cout << word << std::endl;
  try
  {

    /** Call the say method. */
    tts_.say(word);
    /** Note: on the desktop you won't hear anything, but you should see
    * some logs on the naoqi you are connected to. */
  }
  catch(const AL::ALError&)
  {
    qiLogError("module.example") << "Could not get proxy to ALTextToSpeech" << std::endl;
  }
}
