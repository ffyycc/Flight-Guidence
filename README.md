# CS225 Final Project
## TeamNetID: tinghan2-yf9-yuhanlu2-yiruiz2

## Overview
This is the CS225 final project developed by Eric Zhou, Lucas Lu, Joe Ye, and Yucheng Feng. Our project implemented BFS and DFS to traverse all the available airports. Besides, we adopted Dijkstra's algorithm to find the shortest path between two airports. Finally, our project included PageRank algorithm, which could display the frequencies and popularity of airlines to different airports. For example, a popular airport would have a higher frequency than a small airport. 

## Problem to solve
In this contemporary society, airflight becomes an important transportation for people in daily life. However, sometimes people are confused about how to go from one location to another unknown location. Here, we have a project to help find the shortest route between two airports. Life becomes convenient!

## Data Source
Our data is from dataset inside OpenFlights. You can open the link [here](https://openflights.org/data.html). This is the general map and locations of our airports. [map here](https://openflights.org/demo/openflights-apdb-2048.png). In specific, we use the following information: Airport ID, Name, City, Country, IATA, ICAO, Latitude, Longitude, Altitude, Timezone.

Example entry here: 507, "London Heathrow Airport", "London", "United Kingdom", "EGLL", 51.4706, -0.461941, 83, 0, "E", "Europe/London", "airport", "OurAirports"

We also include those data to under the "data" folder, so you don't need to download from other sources. Besides, for the sake of testing, we have some smaller test data under the "testData" folder.

## Installation
No installation needed.

## Test
We include our tests in "tests" folder, and there are four tests "dsetTest.cpp", "loadTest.cpp", "pagerankTest.cpp", and utilTest.cpp". They test for disjoint sets, data loading, Page rank, and some utility functions and algorithm testing (Dijkstra and BFS/DFS).
Please run "make test" to see the outcome.
```cpp
make test
```
```cpp
./test
```

## Usage
We include some of our fundamental functions in "main.cpp" for testing and
displaying results. 
Run
```cpp
make
```
```cpp
./main
```
For more information about a specific function, please refer to the function documentations in each file. In "utils.cpp", we provided some of the utility functions required for reading files and algorithm implementation. "Airlines.cpp", "airports.cpp", "planes.cpp", and "routes.cpp" are for data loading; in "airlineFlow.cpp", we converted all these data into a graph. Our BFS and DFS traversals are also included in "airlineFlow.cpp". Dijkstra's algorithm and Pagerank are implemented in "Dijkstra.cpp" and "pagerank.cpp" respectively. We also implemented disjoint sets in "dset.hpp" for further insight into graph traversal.

## Contribution
Thanks to the contribution of cs225, We used graph files, PNG files, and make files from cs225 class. 

## Project Presentation
Please watch the below video for more information regarding to the project. https://youtu.be/AOmcHzuRITg# Flight-Guidence
# Flight-Guidence
