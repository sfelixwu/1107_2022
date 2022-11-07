

// ecs36b first program

#include <iostream>
#include "Shadow_Thing.h"
#include "Network.h"
#include "IOT_Thing.h"

using namespace std;

int
main()
{
  Thing *thing_ptr;
  
  // first object
  // Shadow_Thing st_1 { "http://10.42.0.1:8384", "Thing", "00000001" };
  Shadow_Thing st_1 { "http://127.0.0.1:8384", "Thing", "00000002" };

  // second object
  GPS_DD gps_Home_Woodland { 38.672215864622636, -121.72280111121437 };
  GPS_DD gps_TLC_UCDavis   { 38.53874868013882,  -121.7542091083306 };
  GPS_DD gps_IKEA_Sacramento { 38.58681641563053, -121.55296296578501};

  // demo on 10/27/2022 ecs36b for JSON2Object
  Json::Value xyz = gps_Home_Woodland.dump2JSON();
  GPS_DD yyy;
  bool status_j = yyy.JSON2Object(xyz);
  std::cout << (yyy.dump2JSON()).toStyledString() << std::endl;
  std::cout << (gps_Home_Woodland.dump2JSON()).toStyledString() << std::endl;
  
  Person John { "987654320", "John", gps_Home_Woodland };
  John.setLocation(gps_IKEA_Sacramento, (*getNowJvTime()));

  IP_Address meatball_IP { 2850883174 };
  IOT_Thing Irish_Coffee { John , meatball_IP };
  
  Irish_Coffee.model = "HUVUDROLL";
  Irish_Coffee.sequence_num = "123456-0000";
  Irish_Coffee.description = "frozen";
  Irish_Coffee.location = gps_Home_Woodland;
  Irish_Coffee.purchased = *getNowJvTime();
  Irish_Coffee.sold = *getNowJvTime();
  Irish_Coffee.owner = John;

  Json::Value result;

  thing_ptr = (Thing *) (&Irish_Coffee);
  result = thing_ptr->dump2JSON();
  cout << result.toStyledString() << endl;

  thing_ptr = (Thing *) (&st_1);
  result = thing_ptr->dump2JSON();
  cout << result.toStyledString() << endl;

  return 0;
}
