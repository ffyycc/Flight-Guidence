#include "../cs225/catch/catch.hpp"

#include "../cs225/graph.h"

#include "../airlines.h"
#include "../airlineFlow.h"
#include "../airports.h"
#include "../planes.h"
#include "../routes.h"
#include "../utils.h"
#include "../pagerank.cpp"
#include <iostream>
#include <map>
#include <vector>

using namespace std;
using namespace utils;

TEST_CASE("check Pagerank with small dataset", "[valgrind][weight=1]") {
  AirlineFlow  *testalf = new AirlineFlow(true);
  Graph* g = testalf->getRouteGraph();
  Pagerank * pagerank1 = new Pagerank(*testalf, false);
  pagerank1->returnMatrix();


  Matrix *mat1 = new Matrix(8, 8);
  mat1->setEntry(0, 4, 2);
  mat1->setEntry(1, 5, 1);
  mat1->setEntry(2, 7, 1);
  mat1->setEntry(3, 7, 1);
  mat1->setEntry(4, 5, 1);
  mat1->setEntry(5, 1, 1);
  mat1->setEntry(5, 2, 1);
  mat1->setEntry(6, 0, 1);
  mat1->setEntry(6, 7, 1);
  mat1->setEntry(7, 3, 1);
  mat1->setEntry(7, 4, 1);
  mat1->setEntry(7, 6, 1);
  REQUIRE(*(pagerank1->returnMatrix()) == *mat1);
  
}
