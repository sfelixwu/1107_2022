
#ifndef _NETWORK_H_
#define _NETWORK_H_

// Network.h

#include "ecs36b_Common.h"

class IP_Address
{
 private:
  unsigned int addr;
 public:
  IP_Address();
  IP_Address(unsigned int);
  std::string& getIPaddressString();
  unsigned int getIPaddressValue();
  virtual Json::Value dump2JSON();
  virtual bool JSON2dump(Json::Value);
};

#endif  /* _NETWORK_H_ */
