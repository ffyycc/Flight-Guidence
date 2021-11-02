#include "../cs225/catch/catch.hpp"

#include "../airlines.h"
#include "../airports.h"
#include "../planes.h"
#include "../routes.h"
#include "../utils.h"
#include "../pagerank.h"
#include "../airlineFlow.h"
#include "../Dijkstra.h"
#include <iostream>

using namespace std;

AirlineFlow airlineFlowTest(true);
Dijkstra dijkstraTest(airlineFlowTest);
AirlineFlow airlineFlowActural(false);
Dijkstra dijkstraActural(airlineFlowActural);

//see testRoutesIMG.jpg
TEST_CASE("check shortest path on test routes", "shortestPath") {
  pair<int, vector<int>> res = dijkstraTest.shortestPath(2965, 2922);
  REQUIRE(res.second.size() == 5);
  REQUIRE(res.second[0] == 2965);       // Krasnodar Pashkovsky International Airport
  REQUIRE(res.second[1] == 2990);       // Kazan International Airport
  REQUIRE(res.second[2] == 2975);       // Koltsovo Airport
  REQUIRE(res.second[3] == 6969);       // Begishevo Airport
  REQUIRE(res.second[4] == 2922);       // Heydar Aliyev International Airport
}

TEST_CASE("check shortest path on actual routes - CMI to ORD", "shortestPath") {
  pair<int, vector<int>> res = dijkstraActural.shortestPath(4049, 3830);
  REQUIRE(res.second.size() == 2);
  REQUIRE(res.second[1] == 3830);       // Chicago O'Hare International Airport
}

TEST_CASE("check shortest path on actual routes - CAN to HKG", "shortestPath") {
  pair<int, vector<int>> res = dijkstraActural.shortestPath(3370, 3077);
  REQUIRE(res.second.size() == 2);
  REQUIRE(res.second[1] == 3077);       // Hong Kong International Airport
}

TEST_CASE("check shortest path on actual routes - CAN to ORD", "shortestPath") {
  pair<int, vector<int>> res = dijkstraActural.shortestPath(3370, 3830);
  REQUIRE(res.second.size() == 3);
  REQUIRE(res.second[1] == 3364);       // Beijing Capital International Airport"
  REQUIRE(res.second[2] == 3830);       // Chicago O'Hare International Airport
}
