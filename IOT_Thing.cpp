#include "IOT_Thing.h"

IOT_Thing::IOT_Thing
(void)
{
}

IOT_Thing::IOT_Thing
(Person arg_owner, IP_Address arg_connecting)
  : Thing { arg_owner }
{
  this->connected = arg_connecting;
  // ((Thing *) this)->Thing::Thing(arg_owner);
}

Json::Value IOT_Thing::dump2JSON
(void)
{
  Thing parent { (IOT_Thing) (*this) };
  Json::Value result = parent.dump2JSON();
  Json::Value jv_result;
  jv_result = (this->connected).dump2JSON();
  result["connected"] = jv_result;

  return result;
}

