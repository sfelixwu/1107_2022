
#include "Network.h"

IP_Address::IP_Address()
{
  this->addr = 0;  
}

IP_Address::IP_Address
(unsigned int arg_ip)
{
  this->addr = arg_ip;
}

std::string SDefault {"Default"};

std::string&
IP_Address::getIPaddressString()
{  
  return SDefault;
}

unsigned int
IP_Address::getIPaddressValue()
{
  return addr;
}

Json::Value
IP_Address::dump2JSON
()
{
  Json::Value result {};

  struct in_addr my_in;
  // my_in.s_addr = this->addr;
  // *** host versus network byte orders ***
  my_in.s_addr = htonl(this->addr);
  char *ip_ch = inet_ntoa(my_in);
  std::string ip_str { ip_ch };

  result["IPv4"] = ip_str;

#ifdef _ECS36B_DEBUG_
  std::cout << result.toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */
  return result;
}

bool 
IP_Address::JSON2dump
(Json::Value input_json)
{
  if ((input_json.isNull() == true) ||
      (input_json.isObject() != true))
    {
      return false;
    }

  if (((input_json["IPv4"]).isNull() == true) ||
      ((input_json["IPv4"]).isString() != true))
    {
      return false;
    }

  // we allow IP address to be modifiable (IP mobility supported)
  this->addr = inet_addr(((input_json["IPv4"]).asString()).c_str());

#ifdef _ECS36B_DEBUG_
  std::cout << (this->dump2JSON()).toStyledString() << std::endl;
#endif /* _ECS36B_DEBUG_ */

  return true; // if successful
}
