
// for Json::value
#include <json/json.h>
#include <json/reader.h>
#include <json/writer.h>
#include <json/value.h>
#include <string>

// for JsonRPCCPP
#include <iostream>
#include "hw5server.h"
#include <jsonrpccpp/server/connectors/httpserver.h>
#include "hw5client.h"
#include <jsonrpccpp/client/connectors/httpclient.h>
#include <stdio.h>

// ecs36b
#include "IOT_Thing.h"
#include "Person.h"
#include "Thing.h"
#include <time.h>
#include "Shadow_Thing.h"

using namespace jsonrpc;
using namespace std;

// std::map (key, value pairs)
std::map<std::string, Thing *> Thing_Map;

class Myhw5Server : public hw5Server
{
public:
  Myhw5Server(AbstractServerConnector &connector, serverVersion_t type);
  virtual Json::Value dump2JSON(const std::string& action, const std::string& arguments, const std::string& class_id, const std::string& host_url, const std::string& object_id);
};

Myhw5Server::Myhw5Server(AbstractServerConnector &connector, serverVersion_t type)
  : hw5Server(connector, type)
{
  std::cout << "Myhw5Server Object created" << std::endl;
}

// member functions

Json::Value
Myhw5Server::dump2JSON
(const std::string& action, const std::string& arguments,
 const std::string& class_id, const std::string& host_url,
 const std::string& object_id)
{
  // a pointer to Thing
  Thing *thing_ptr; // now a local variable

  Json::Value result;
  std::cout << action << " " << arguments << std::endl;
  std::string strJson;

  if (class_id != "Thing")
    {
      result["status"] = "failed";
      strJson = ( "class " + class_id + " unknown");
      result["reason"] = strJson;
    }
  else
    {
      if (Thing_Map.find(object_id) != Thing_Map.end())
	{
	  thing_ptr = Thing_Map[object_id];
	  result = thing_ptr->dump2JSON();
	  result["status"] = "successful";
	}
      else
	{
	  result["status"] = "failed";
	  strJson = ( "object " + object_id + " unknown");
	  result["reason"] = strJson;
	}
    }

  return result;
}

int main()
{
  GPS_DD gps_Home_Woodland { 38.672215864622636, -121.72280111121437 };
  GPS_DD gps_TLC_UCDavis   { 38.53874868013882,  -121.7542091083306 };
  GPS_DD gps_IKEA_Sacramento { 38.58681641563053, -121.55296296578501};

  Person Felix { "987654321", "Felix", gps_Home_Woodland };
  Felix.setLocation(gps_IKEA_Sacramento, (*getNowJvTime()));

  IP_Address meatball_IP { 2850883174 };
  IOT_Thing Swedish_Meatball { Felix , meatball_IP };
  
  Swedish_Meatball.model = "HUVUDROLL";
  Swedish_Meatball.sequence_num = "123456-0000";
  Swedish_Meatball.description = "frozen";
  Swedish_Meatball.location = gps_Home_Woodland;
  Swedish_Meatball.purchased = *getNowJvTime();
  Swedish_Meatball.sold = *getNowJvTime();
  Swedish_Meatball.owner = Felix;

  int rc;
  char name_buf[256];
  
  bzero(name_buf, 256);
  sprintf(name_buf, "./json_objects/%s_%s.json", "Thing", "000000001");
  Json::Value jv = Swedish_Meatball.dump2JSON();
  rc = myJSON2File(name_buf, &jv);
  if (rc != 0)
    {
      std::cout << "myJSON2File error " << rc << std::endl;
      exit(-1);
    }

  Thing_Map["00000001"] = (Thing *) (&Swedish_Meatball);
  for (const auto& [key, value] : Thing_Map)
    std::cout << '[' << key << "] = " << value << ";\n ";

#ifdef _GPS_STUFF_
  bzero(name_buf, 256);
  sprintf(name_buf, "./json_objects/%s_%s.json", "GPS", "000000001");
  Json::Value gps_jv = gps_IKEA_Sacramento.dump2JSON();
  rc = myJSON2File(name_buf, &gps_jv);
  if (rc != 0)
    {
      std::cout << "myJSON2File error " << rc << std::endl;
      exit(-1);
    }

  Json::Value gps_jv_2;
  rc = myFile2JSON(name_buf, &gps_jv_2);
  if (rc != 0)
    {
      std::cout << "myJSON2File error " << rc << std::endl;
      exit(-1);
    }
  GPS_DD new_one {};
  new_one.JSON2Object(gps_jv_2);
  std::cout << (new_one.dump2JSON()).toStyledString() << std::endl;

#endif /* _GPS_STUFF_ */
  
  HttpServer httpserver(8384);
  Myhw5Server s(httpserver,
		JSONRPC_SERVER_V1V2); // hybrid server (json-rpc 1.0 & 2.0)
  s.StartListening();
  std::cout << "Hit enter to stop the server" << endl;
  getchar();

  s.StopListening();
  return 0;
}
