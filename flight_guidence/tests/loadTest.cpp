#include "../cs225/catch/catch.hpp"

#include "../airlines.h"
#include "../airports.h"
#include "../planes.h"
#include "../routes.h"
#include <iostream>
#include <map>
#include <vector>

using namespace std;

TEST_CASE("check the Airlines constructor and getAirlineByID.", "[valgrind][weight=1]") {
  Airlines airlines(true);
  REQUIRE(airlines.getAirlineByID(2)->name == "135 Airways");
  REQUIRE(airlines.getAirlineByID(2)->alias.size() == 0);
  REQUIRE(airlines.getAirlineByID(2)->IATA.size() == 0);
  REQUIRE(airlines.getAirlineByID(2)->ICAO == "GNL");
  REQUIRE(airlines.getAirlineByID(2)->callsign == "GENERAL");
  REQUIRE(airlines.getAirlineByID(2)->country == "United States");
  REQUIRE(airlines.getAirlineByID(2)->active == false);

}

TEST_CASE("check some random cases of getAirlineByID.", "[valgrind][weight=1]") {
  Airlines airlines(true);
  REQUIRE(airlines.getAirlineByID(563)->country == "Germany");
  REQUIRE(airlines.getAirlineByID(125)->IATA == "FG");
  REQUIRE(airlines.getAirlineByID(781)->ICAO == "CRP");
  REQUIRE(airlines.getAirlineByID(-1)->callsign.size() == 0);
}

TEST_CASE("check the Airports constructor and getAirportByID.", "[valgrind][weight=1]") {
  Airports airports(true);
  REQUIRE(airports.getAirportByID(1)->name == "Goroka Airport");
  REQUIRE(airports.getAirportByID(1)->city == "Goroka");
  REQUIRE(airports.getAirportByID(1)->country == "Papua New Guinea");
  REQUIRE(airports.getAirportByID(1)->IATA == "GKA");
  REQUIRE(airports.getAirportByID(1)->ICAO == "AYGA");
  REQUIRE(airports.getAirportByID(1)->latit == -6.081689834590001);
  REQUIRE(airports.getAirportByID(1)->longit == 145.391998291);
  REQUIRE(airports.getAirportByID(1)->alt == 5282);
}

TEST_CASE("check some random cases of getAirportByID.", "[valgrind][weight=1]") {
  Airports airports(true);
  REQUIRE(airports.getAirportByID(12076)->latit == 39.602194);
  REQUIRE(airports.getAirportByID(150)->longit == -105.262001038);
  REQUIRE(airports.getAirportByID(641)->name == "Harstad/Narvik Airport, Evenes");
  REQUIRE(airports.getAirportByID(6275)->IATA == "HGD");
}

TEST_CASE("check getAirportByIATA.", "[valgrind][weight=1]") {
  Airports airports(true);
  REQUIRE(airports.getAirportIDByIATA("MAG") == 2);
  REQUIRE(airports.getAirportIDByIATA("HGU") == 3);
}

TEST_CASE("check getPlaneByIATA.", "[valgrind][weight=1]") {
  Planes planes(true);
  REQUIRE(planes.getPlaneByIATA("ND2")->name == "Aerospatiale (Nord) 262");
}

TEST_CASE("check constructor of routes.cpp.", "[valgrind][weight=1]") {
  Routes routes(true);
  Routes::RoutesNode* begin = *(routes.begin()); 
  REQUIRE(begin->airline == "2B");
  REQUIRE(begin->airlineID == 410);
  REQUIRE(begin->airport1 == "AER");
  REQUIRE(begin->airportID1 == 2965);
  REQUIRE(begin->airport2 == "KZN");
  REQUIRE(begin->airportID2 == 2990);
  REQUIRE(begin->codeshare == false);
  REQUIRE(begin->stops == 0);
  //REQUIRE(begin->equipment == "CR2");
  
}
