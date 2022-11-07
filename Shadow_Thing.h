
#ifndef _SHADOW_THING_H_
#define _SHADOW_THING_H_

#include "Thing.h"

class Shadow_Thing: public Thing
{
 private:
 public:
  
  std::string host_url;
  std::string class_id;
  std::string object_id;

  Shadow_Thing(std::string, std::string, std::string);
  virtual Json::Value dump2JSON(); // print the content of the object
};

#endif // _SHADOW_THING_H_
