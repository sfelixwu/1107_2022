
#ifndef _THING_H_
#define _THING_H_

// Thing.h

#include "ecs36b_Common.h"
#include "Person.h"
#include "GPS.h"
#include "JvTime.h"

class Thing
{
 private:
 protected:
 public:
  
  std::string model;
  std::string sequence_num;
  std::string description;
  Person      owner;
  JvTime      purchased;
  JvTime      sold;

  GPS_DD      location;
  
  Thing(void);
  Thing(Person arg_owner);
  virtual Json::Value dump2JSON(); // print the content of the object
};

#endif /* _THING_H_ */
