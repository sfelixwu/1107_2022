
#ifndef _IOT_THING_H_
#define _IOT_THING_H_

// IOT_Thing.h
#include "ecs36b_Common.h"
#include "Thing.h"
#include "Network.h"

class IOT_Thing: public Thing
{
 private:
 protected:
 public:
  IP_Address connected;
  IOT_Thing(void);
  IOT_Thing(Person arg_owner, IP_Address arg_connecting);
  Json::Value dump2JSON(); // print the content of the object
};

#endif /* _IOT_THING_H_ */
