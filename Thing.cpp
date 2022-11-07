#include "Thing.h"

Thing::Thing
(void)
{
  this->model = "";
  this->sequence_num = "";
  this->description = "";
}

Thing::Thing
(Person arg_owner)
{
  this->model = "";
  this->sequence_num = "";
  this->description = "";
  this->owner = arg_owner;
}

#ifdef OLD
void Thing::dump
(void)
{
  std::cout << "[Thing] dump-begin" << std::endl;
  std::cout << "model          = " << this->model << std::endl;
  std::cout << "sequence_num   = " << this->sequence_num << std::endl;
  std::cout << "description    = " << this->description << std::endl;
  std::cout << "[Thing] dump-end" << std::endl;
  return;
}
#endif /* OLD */

Json::Value Thing::dump2JSON
(void)
{
  Json::Value result { };

  if (this->model != "")
    {
      result["model"] = this->model;
    }

  if (this->sequence_num != "")
    {
      result["sequence_num"] = this->sequence_num;
    }

  if (this->description != "")
    {
      result["description"] = this->description;
    }

  Json::Value jv_result;
  
  jv_result = (this->owner).dump2JSON();
  result["owner"] = jv_result;

  jv_result = (this->purchased).dump2JSON();
  result["purchased"] = jv_result;

  jv_result = (this->sold).dump2JSON();
  result["sold"] = jv_result;

  jv_result = (this->location).dump2JSON();
  result["location"] = jv_result;

  // std::cout << jv_result.toStyledString() << std::endl;

  return result;
}

