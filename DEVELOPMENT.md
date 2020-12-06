# Development Log
**CS225** final project development log.

## Week 1
- Should complete core components of the project:
	- Create a file parser to read in data files
	- Design and develop the general graph structure
- Write a makefile for the project
	- A simple makefile is preferred over a complex file to reduce possibility of errors during building.
- Decided on directory structure for project.
	- We will be using separate folders for each module, then put the main file in the root of the project directory.
	- Tests employing CATCH will be stored in their own folder in the root directory.
	- Modules include the graph structure, file parser, traversal algorithms, graphics classes, and image classes from MPs. 
- Decided to follow same comment style as that employed in CS225. (Doxygen style)
- Work division:
	- File Parser: Adam and Jason
	- Beginning of graph structure: Armando and Sebastian
	- Makefile: Everyone

## Week 2
### Design Log
- Determined best method for flight data and graph correlation:
	- Graph is simple and directed where airport vertices are labeled by unique open flights id.
	- Dictionary containing airport data keyed by open flights id allows for airport lookup from graph.
	- Dictionary containing open flights id keyed by IATA code allows for user input of origin and destination airports via friendly names (i.e. ORD, LAX, JFK, ...)
- Minimized number of edges in order improve algorithm runtimes:
	- Since edge weights are determined via geographical distance between airports, only one edge is required to encode a set of flights from one airport to another in the same direction.
	- The label on each edge is an index in a vector of flight vectors allowing for retrieval of flight information for any flight between two airports.
	- Constant lookup time from vector matrix allows for minimal runtime penalties for pertinent lookups of first airline and number of airlines servicing route.
### Work Log
- Restructured project directory to properly separate project components.
- Implemented file parser to take flight data from CSV file and import it into the project.
- Implemented all core graph functionality for air traffic.
- Wrote a Makefile to build all modules and link together both the main executable and the test executable.
	***(Unfinished)***
- 